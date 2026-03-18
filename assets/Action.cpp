#include <algorithm>
#include <chrono>
#include <format>
#include <iostream>
#include <sstream>
#include <thread>
#include <unordered_map>
#include <vector>

#include "../include/Action.h"
#include "../include/Player.h"
#include "../include/interfaces/Craftable.h"
#include "../include/interfaces/Material.h"
#include "../include/interfaces/Sellable.h"
#include "../include/interfaces/Tool.h"

// Static helpers

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

// Action handlers

static void HandleUpgrade(Player& player, const ParsedCommand& command) {
    std::unordered_map<std::string, Tool*> tools = {
        { "axe",   player.GetAxe()   },
        { "sword", player.GetSword() }
    };

    if (command.target.empty()) {
        std::cout << "Hmm, let's see what I can upgrade.\n";
        for (const auto& [name, tool] : tools) {
            if (tool != nullptr && tool->GetUpgradeCost() > 0)
                std::cout << std::format("  {} ({} gold)\n", tool->GetName(), tool->GetUpgradeCost());
        }
        return;
    }

    auto toolEntry = tools.find(command.target);
    if (toolEntry == tools.end()) {
        std::cout << std::format("Don't know how to upgrade \"{}\".\n", command.target);
        return;
    }

    Tool* tool = toolEntry->second;
    const int cost = tool->GetUpgradeCost();

    if (cost == 0) {
        std::cout << tool->GetName() << " is as good as I can get it.\n";
    } else if (player.GetGold() < cost) {
        std::cout << std::format("The blacksmith wants {} gold, but I only have {}.\n", cost, player.GetGold());
    } else {
        tool->Upgrade();
        player.LoseIntGold(cost);
        std::cout << std::format("Upgraded to {}! Remaining gold: {}\n", tool->GetName(), player.GetGold());
    }
}

static void HandleSell(Player& player, const ParsedCommand& command, const std::vector<Sellable*>& sellables) {
    if (command.target.empty()) {
        std::cout << "What to sell, then?\n";
        for (Sellable* sellable : sellables) {
            if (player.GetItemCount(sellable) == 0) continue;
            std::cout << std::format("  {} (x{}) — {} gold each\n",
                sellable->GetName(), player.GetItemCount(sellable), sellable->GetSellAmount());
        }
        std::cout << "(e.g., sell 1 wood  OR  sell 3 wood)\n";
        return;
    }

    Sellable* itemToSell = nullptr;
    for (Sellable* sellable : sellables) {
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

static void HandleBuy(Player& player, const ParsedCommand& command, const std::vector<Material*>& buyables) {
    if (command.target.empty()) {
        std::cout << "Let's see what they have.\n";
        for (Material* buyable : buyables) {
            std::cout << std::format("  {} — {} gold\n", buyable->GetName(), buyable->GetBuyAmount());
        }
        std::cout << std::format("(e.g., buy 1 cake  OR  buy 2 cake)  [You have: {} gold]\n", player.GetGold());
        return;
    }

    Material* itemToBuy = FindMaterial(buyables, command.target);
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

static void HandleCraftListing(const std::vector<Craftable*>& craftables, const std::vector<Sellable*>& sellables) {
    std::cout << "What would you like to craft?\n";
    for (Craftable* craftable : craftables) {
        std::string requirementsList;
        for (const auto& [requiredId, requiredCount] : craftable->GetItemsRequired()) {
            // Look up the ingredient name by ID from the world item list
            std::string requiredName = "item";
            for (Sellable* ingredientItem : sellables) {
                if (ingredientItem->GetId() == requiredId) {
                    requiredName = ingredientItem->GetName();
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

// Parsing

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

    // inv and quit take no arguments
    if (result.action == Action::Inv || result.action == Action::Quit) return result;

    std::string quantityString;
    if (!(stream >> quantityString)) return result;

    // Bound quantity to be positive
    try {
        result.quantity = std::max(1, std::stoi(quantityString));
    } catch (...) {
        // No quantity; treat it as the target with default quantity
        result.target = quantityString;
        std::transform(result.target.begin(), result.target.end(), result.target.begin(), ::tolower);
        return result;
    }

    stream >> result.target;
    std::transform(result.target.begin(), result.target.end(), result.target.begin(), ::tolower);

    return result;
}

std::vector<Action> GetAvailableActions(const Player& player, const std::vector<Craftable*>& craftables, const std::vector<Sellable*>& sellables) {
    std::vector<Action> available;
    const auto& itemsOwned = player.GetItemsOwned();

    available.push_back(Action::Buy);
    available.push_back(Action::Chop);
    available.push_back(Action::Continue);

    // Can craft if any owned item appears in at least one recipe
    if (std::any_of(craftables.begin(), craftables.end(), [&itemsOwned](const Craftable* craftable) {
        for (const auto& [requiredItemId, requiredCount] : craftable->GetItemsRequired())
            if (itemsOwned.count(requiredItemId)) return true;
        return false;
    })) available.push_back(Action::Craft);

    if (itemsOwned.count(ItemId::Cake)) available.push_back(Action::Eat);

    available.push_back(Action::Inv);
    available.push_back(Action::Quit);

    // Can sell if any owned item is in the sellables list
    if (std::any_of(sellables.begin(), sellables.end(), [&itemsOwned](const Sellable* sellable) {
        return itemsOwned.count(sellable->GetId());
    })) available.push_back(Action::Sell);

	const bool canUpgradeAxe = player.GetAxe() != nullptr &&
        player.GetGold() >= player.GetAxe()->GetUpgradeCost() &&
        player.GetAxe()->GetUpgradeCost() > 0;
	const bool canUpgradeSword = player.GetSword() != nullptr &&
        player.GetGold() >= player.GetSword()->GetUpgradeCost() &&
		player.GetSword()->GetUpgradeCost() > 0;
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

std::string PrintPrompt(const std::vector<Action>& available) {
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
    Player& player,
    const std::vector<Action>& availableActions,
    Material* wood,
    const std::vector<Material*>& buyables,
    const std::vector<Craftable*>& craftables,
    const std::vector<Sellable*>& sellables)
{
    if (command.action == Action::Continue) {
        std::cout << "Nothing to continue yet.\n";
        return;
    }

    if (command.action == Action::Unknown) {
        std::cout << "...Not sure what that means. Try: chop, sell, buy, craft, eat, inv, quit.\n";
        return;
    }

    if (command.action == Action::Upgrade) {
        HandleUpgrade(player, command);
        return;
    }

    if (command.action == Action::Inv) {
        player.PrintInventory();
        return;
    }

    if (std::find(availableActions.begin(), availableActions.end(), command.action) == availableActions.end()) {
        std::cout << "Can't do that right now.\n";
        std::cout << std::format("Available right now: {}\n", PrintPrompt(availableActions));
        return;
    }

    if (command.action == Action::Sell) {
        HandleSell(player, command, sellables);
        return;
    }

    if (command.action == Action::Buy) {
        HandleBuy(player, command, buyables);
        return;
    }

    if (command.action == Action::Craft && command.target.empty()) {
        HandleCraftListing(craftables, sellables);
        return;
    }

    // Repeatable actions: executed once per unit of quantity
    for (int i = 0; i < command.quantity; i++) {
        if (command.action == Action::Chop) {
            if (!player.Chop(wood)) {
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
            Craftable* itemToCraft = FindCraftable(craftables, command.target);
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
