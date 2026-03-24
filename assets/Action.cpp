#include <algorithm>
#include <chrono>
#include <format>
#include <iostream>
#include <sstream>
#include <thread>
#include <unordered_map>
#include <vector>

#include "../include/Action.h"
#include "../include/Encounter.h"
#include "../include/World.h"
#include "../include/Voyage.h"

// region Helpers

static std::string NormalizeName(std::string name) {
	name.erase(std::remove(name.begin(), name.end(), ' '), name.end());
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);
	return name;
}

static Material* FindMaterial(const std::vector<Material*>& materials, const std::string& target) {
	for (Material* material : materials) {
		if (NormalizeName(material->GetName()) == target) return material;
	}
	return nullptr;
}

static Craftable* FindCraftable(const std::vector<Craftable*>& craftables, const std::string& target) {
	for (Craftable* craftable : craftables) {
		if (NormalizeName(craftable->GetName()) == target) return craftable;
	}
	return nullptr;
}

// region Setting text

void PrintSettingText(StoryPhase phase) {
	switch (phase) {
	case StoryPhase::Forest:
		std::cout << "Ashpeak. The goblin tunnels.\n";
		std::cout << "...Going to need supplies. Cake for the road. A better blade, maybe.\n";
		std::cout << "All of that costs gold.\n";
		std::cout << "Gold means benches. Quick ones, nothing like the Settle. No time for that now.\n";
		break;
	case StoryPhase::Kelsa:
		std::cout << "Kelsa. Past the forest, past the bear.\n";
		std::cout << "The market had everything — gear, supplies, a blacksmith who knew his craft.\n";
		std::cout << "The tunnels of Ashpeak loomed above the town. Somewhere up there, goblins had his bench.\n";
		std::cout << "Time to prepare.\n";
		break;
	case StoryPhase::Ship:
		std::cout << "The goblin king was dead. The bench wasn't in Ashpeak.\n";
		std::cout << "Lord Crane had it. Crane's Reach, across the open water.\n";
		std::cout << "Going to need gold for a ship. Whatever it takes.\n";
		break;
	default:
		break;
	}
}

// region Action handlers

static void HandleUpgrade(World& world, const ParsedCommand& command) {
	Player& player = world.player;

	std::unordered_map<std::string, Tool*> tools = {
		{ "axe", player.GetAxe() },
		{ "sword", player.GetSword() }
	};

	if (command.target.empty()) {
		std::cout << "Hmm, let's see what I can upgrade.\n";
		for (const auto& [name, tool] : tools) {
			if (tool == nullptr || tool->GetUpgradeCost() <= 0) continue;
			if (name == "sword" && tool->GetTier() >= 2 && world.phase < StoryPhase::Kelsa) continue;
			std::cout << std::format("  {} ({} gold)  [type: upgrade {}]\n", tool->GetName(), tool->GetUpgradeCost(), name);
		}
		return;
	}

	auto toolEntry = tools.find(command.target);
	if (toolEntry == tools.end()) {
		std::cout << std::format("Don't know how to upgrade \"{}\". Try: upgrade sword, upgrade axe.\n", command.target);
		return;
	}

	Tool* tool = toolEntry->second;

	if (command.target == "sword" && tool->GetTier() >= 2 && world.phase < StoryPhase::Kelsa) {
		std::cout << "Not here. I'll need to find a proper blacksmith first.\n";
		return;
	}
	const int cost = tool->GetUpgradeCost();

	if (cost == 0) {
		std::cout << tool->GetName() << " is as good as I can get it.\n";
	} else if (player.GetGold() < cost) {
		std::cout << std::format("The blacksmith wants {} gold, but I only have {}.\n", cost, player.GetGold());
	} else {
		tool->Upgrade();
		player.LoseGold(cost);
		std::cout << std::format("Upgraded to {}! Remaining gold: {}\n", tool->GetName(), player.GetGold());
	}
}

static void HandleSell(World& world, const ParsedCommand& command) {
	Player& player = world.player;

	if (command.target.empty()) {
		std::cout << "What to sell, then?\n";
		for (Sellable* sellable : world.sellables) {
			if (player.GetItemCount(sellable) == 0) continue;
			std::cout << std::format("  {} (x{}) — {} gold each  [type: sell {}]\n",
				sellable->GetName(), player.GetItemCount(sellable), sellable->GetSellAmount(), NormalizeName(sellable->GetName()));
		}
		std::cout << "(e.g., sell 1 wood  OR  sell 3 wood)\n";
		return;
	}

	Sellable* itemToSell = nullptr;
	for (Sellable* sellable : world.sellables) {
		if (NormalizeName(sellable->GetName()) == command.target) {
			itemToSell = sellable;
			break;
		}
	}

	if (itemToSell == nullptr) {
		std::cout << std::format("I don't have any \"{}\" to sell.\n", command.target);
		return;
	}

	const int goldEarned = player.Sell(itemToSell, command.quantity);
	if (goldEarned == 0) {
		std::cout << std::format("Couldn't sell {}.\n", itemToSell->GetName());
	} else {
		std::cout << std::format("Sold {}x {} for {} gold! (Total gold: {})\n",
			command.quantity, itemToSell->GetName(), goldEarned, player.GetGold());
	}
}

static void HandleBuy(World& world, const ParsedCommand& command) {
	Player& player = world.player;

	if (command.target.empty()) {
		std::cout << "Let's see what they have.\n";
		for (Material* buyable : world.buyables) {
			std::cout << std::format("  {} — {} gold\n", buyable->GetName(), buyable->GetBuyAmount());
		}
		if (world.phase == StoryPhase::Ship) {
			std::cout << std::format("  Ship — spends ALL your gold ({}) [type: buy ship]\n", player.GetGold());
		}
		std::cout << std::format("(e.g., buy 1 cake  OR  buy 2 cake)  [You have: {} gold]\n", player.GetGold());
		return;
	}

	if (command.target == "ship" && world.phase == StoryPhase::Ship) {
		int goldToSpend = player.GetGold();
		if (goldToSpend <= 0) {
			std::cout << "No gold, no ship. Going to need to earn some first.\n";
			return;
		}

		player.LoseGold(goldToSpend);
		std::cout << std::format("Spent {} gold on a ship. Crane's Reach, the bench maker is on his way.\n", goldToSpend);

		VoyageResult result = RunVoyage(goldToSpend);

		if (result == VoyageResult::Arrived) {
			RunCrane(world);
		} else {
			player.SetCurrentHealth(1);
		}

		return;
	}

	Material* itemToBuy = FindMaterial(world.buyables, command.target);
	if (itemToBuy == nullptr) {
		std::cout << std::format("I don't sell \"{}\" here.\n", command.target);
		return;
	}

	bool success = player.Buy(itemToBuy, command.quantity);
	if (!success) {
		std::cout << std::format("Not enough gold. Need {}, only have {}.\n",
			itemToBuy->GetBuyAmount() * command.quantity, player.GetGold());
	} else {
		std::cout << std::format("Bought {}x {} for {} gold! (Remaining gold: {})\n",
			command.quantity, itemToBuy->GetName(), itemToBuy->GetBuyAmount() * command.quantity, player.GetGold());
	}
}

static void HandleCraftListing(const World& world) {
	std::cout << "What would you like to craft?\n";
	for (Craftable* craftable : world.craftables) {
		std::string requirementsList;
		for (const auto& [requiredId, requiredCount] : craftable->GetItemsRequired()) {
			std::string requiredName = "item";
			for (Sellable* sellable : world.sellables) {
				if (sellable->GetId() == requiredId) {
					requiredName = sellable->GetName();
					break;
				}
			}
			if (!requirementsList.empty()) requirementsList += ", ";
			requirementsList += std::format("{} {}", requiredCount, requiredName);
		}
		std::cout << std::format("  {} (requires: {}) — sells for {} gold  [{}]\n",
			craftable->GetName(), requirementsList, craftable->GetSellAmount(), NormalizeName(craftable->GetName()));
	}
	std::cout << "(e.g., craft 1 benchleg)\n";
}

// region Parsing

ParsedCommand ParseInput(const std::string& input) {
	ParsedCommand result;

	std::string action;
	std::istringstream stream(input);
	stream >> action;
	std::transform(action.begin(), action.end(), action.begin(), ::tolower);

	if (action == "buy") result.action = Action::Buy;
	else if (action == "chop") result.action = Action::Chop;
	else if (action == "continue") result.action = Action::Continue;
	else if (action == "craft") result.action = Action::Craft;
	else if (action == "eat") result.action = Action::Eat;
	else if (action == "inv") result.action = Action::Inv;
	else if (action == "quit") result.action = Action::Quit;
	else if (action == "sell") result.action = Action::Sell;
	else if (action == "upgrade") result.action = Action::Upgrade;
	else result.action = Action::Unknown;

	if (result.action == Action::Inv || result.action == Action::Quit) return result;

	std::string quantityString;
	if (!(stream >> quantityString)) return result;

	try {
		result.quantity = std::max(1, std::stoi(quantityString));
	} catch (...) {
		result.target = quantityString;
		std::transform(result.target.begin(), result.target.end(), result.target.begin(), ::tolower);
		return result;
	}

	stream >> result.target;
	std::transform(result.target.begin(), result.target.end(), result.target.begin(), ::tolower);

	return result;
}

std::vector<Action> GetAvailableActions(const World& world) {
	std::vector<Action> available;
	const Player& player = world.player;
	const auto& itemsOwned = player.GetItemsOwned();

	available.push_back(Action::Buy);
	available.push_back(Action::Chop);
	available.push_back(Action::Continue);

	if (std::any_of(world.craftables.begin(), world.craftables.end(), [&itemsOwned](const Craftable* craftable) {
		for (const auto& [requiredItemId, requiredCount] : craftable->GetItemsRequired())
			if (itemsOwned.count(requiredItemId)) return true;
		return false;
	})) available.push_back(Action::Craft);

	if (itemsOwned.count(ItemId::Cake)) available.push_back(Action::Eat);

	available.push_back(Action::Inv);
	available.push_back(Action::Quit);

	if (std::any_of(world.sellables.begin(), world.sellables.end(), [&itemsOwned](const Sellable* sellable) {
		return itemsOwned.count(sellable->GetId());
	})) available.push_back(Action::Sell);

	const bool canUpgradeAxe = player.GetAxe() != nullptr &&
		player.GetGold() >= player.GetAxe()->GetUpgradeCost() &&
		player.GetAxe()->GetUpgradeCost() > 0;
	const bool canUpgradeSword = player.GetSword() != nullptr &&
		player.GetGold() >= player.GetSword()->GetUpgradeCost() &&
		player.GetSword()->GetUpgradeCost() > 0 &&
		(player.GetSword()->GetTier() < 2 || world.phase >= StoryPhase::Kelsa);
	if (canUpgradeAxe || canUpgradeSword) available.push_back(Action::Upgrade);

	std::sort(available.begin(), available.end());

	return available;
}

std::string ActionToString(Action action) {
	switch (action) {
	case Action::Buy: return "buy";
	case Action::Chop: return "chop";
	case Action::Continue: return "continue";
	case Action::Craft: return "craft";
	case Action::Eat: return "eat";
	case Action::Inv: return "inv";
	case Action::Quit: return "quit";
	case Action::Sell: return "sell";
	case Action::Upgrade: return "upgrade";
	default: return "???";
	}
}

std::string FormatPrompt(const std::vector<Action>& available) {
	std::string result = "( ";
	for (int i = 0; i < (int)available.size(); i++) {
		if (i > 0) result += " / ";
		result += ActionToString(available[i]);
	}
	result += " )";
	return result;
}

void HandleAction(
	const ParsedCommand& command,
	World& world,
	const std::vector<Action>& availableActions)
{
	Player& player = world.player;

	if (command.action == Action::Continue) {
		if (world.phase < StoryPhase::Ship) {
			RunEncounter(world);
		}
		else if (world.phase == StoryPhase::Ship) {
			std::cout << "Crane's Reach is across open water. I need to buy a ship first. I'll use every bit of gold I have to make this journey. Whatever it takes. [type: buy ship]\n";
		}
		else {
			std::cout << "Time to watch the sunrise and enjoy my bench.\n";
		}

		return;
	}

	if (command.action == Action::Unknown) {
		std::cout << "...Not sure what that means. Try: chop, sell, buy, craft, eat, inv, quit.\n";
		return;
	}

	if (command.action == Action::Upgrade) {
		HandleUpgrade(world, command);
		return;
	}

	if (command.action == Action::Inv) {
		player.PrintInventory();
		return;
	}

	if (std::find(availableActions.begin(), availableActions.end(), command.action) == availableActions.end()) {
		std::cout << "Can't do that right now.\n";
		std::cout << std::format("Available right now: {}\n", FormatPrompt(availableActions));
		return;
	}

	if (command.action == Action::Sell) {
		HandleSell(world, command);
		return;
	}

	if (command.action == Action::Buy) {
		HandleBuy(world, command);
		return;
	}

	if (command.action == Action::Craft && command.target.empty()) {
		HandleCraftListing(world);
		return;
	}

	for (int i = 0; i < command.quantity; i++) {
		if (command.action == Action::Chop) {
			if (!player.Chop(&world.wood)) {
				std::cout << "Couldn't chop.\n";
				break;
			}
			std::cout << "Chopped! (" << i + 1 << "/" << command.quantity << ")\n";
		}

		else if (command.action == Action::Eat) {
			std::cout << std::format("{}/{} health.\n", player.GetCurrentHealth(), player.GetMaxHealth());
			if (!player.Eat()) {
				std::cout << "No cake. Going to have to buy some.\n";
				break;
			}
			std::cout << std::format("...Better. {}/{} health.\n", player.GetCurrentHealth(), player.GetMaxHealth());
		}

		else if (command.action == Action::Craft) {
			Craftable* itemToCraft = FindCraftable(world.craftables, command.target);
			if (itemToCraft == nullptr) {
				std::cout << std::format("I don't know how to craft \"{}\".\n", command.target);
				break;
			}

			std::cout << std::format("Crafting {}...\n", itemToCraft->GetName());
			std::this_thread::sleep_for(std::chrono::seconds(itemToCraft->GetTimeToCraft()));
			if (!player.Craft(itemToCraft)) {
				std::cout << std::format("Not enough materials to craft {}.\n", itemToCraft->GetName());
				break;
			}
			std::cout << std::format("Done! {} crafted. ({}/{})\n", itemToCraft->GetName(), i + 1, command.quantity);
		}
	}
}
