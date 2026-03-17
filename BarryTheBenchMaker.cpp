#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <windows.h>

#include "include/Action.h"
#include "include/Dialogue.h"
#include "include/Player.h"
#include "include/interfaces/Craftable.h"
#include "include/interfaces/Material.h"
#include "include/interfaces/Sellable.h"
#include "include/items/Cake.h"
#include "include/items/tools/Axe.h"
#include "include/items/tools/Sword.h"

// Helpers

static std::string NormalizeName(std::string name) {
    name.erase(std::remove(name.begin(), name.end(), ' '), name.end());
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);
    return name;
}

static std::string PrintPrompt(const std::vector<Action>& available) {
    std::string result = "( ";
    for (int i = 0; i < (int)available.size(); i++) {
        if (i > 0) result += " / ";
        result += ActionToString(available[i]);
    }
    result += " )";
    return result;
}

// Equivalent to Python's "if action in available"
static bool IsActionAvailable(Action action, const std::vector<Action>& available) {
    return std::find(available.begin(), available.end(), action) != available.end();
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

// Action handlers — extracted from the main loop for readability.
// Each handler prints its own output and returns. The caller continues.

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
        player.LoseGold(cost);
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

// Main

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    PlayDialogue(LoadDialogue("data/opening.json"));
    std::cout << "Ashpeak. The goblin tunnels.\n";
    std::cout << "...Going to need supplies. Cake for the road. A better blade, maybe.\n";
    std::cout << "All of that costs gold.\n";
    std::cout << "Gold means benches. Quick ones, nothing like the Settle. No time for that now.\n";

    Sword sword;
    Axe axe;
    Material wood(ItemId::Wood, "Wood", 1, 1);
    Cake cake(1, 1, 1);
    Craftable benchLeg (ItemId::BenchLeg,  "Bench Leg",  1, 1, {{ItemId::Wood, 1}});
    Craftable benchSeat(ItemId::BenchSeat, "Bench Seat", 1, 1, {{ItemId::Wood, 1}});
    Craftable bench    (ItemId::Bench,     "Bench",      1, 1, {{ItemId::BenchLeg, 1}, {ItemId::BenchSeat, 1}});

    std::vector<Material*> buyables    = { &cake };
    std::vector<Craftable*> craftables  = { &benchLeg, &benchSeat, &bench };
    std::vector<Sellable*> sellables    = { &wood, &cake, &benchLeg, &benchSeat, &bench };

    Player player(1, 1, &sword, &axe);

    std::string input;

    while (true) {
        std::vector<Action> availableActions = GetAvailableActions(player, craftables, sellables);
        std::cout << std::format("\nWhat next? {}\n> ", PrintPrompt(availableActions));
        std::getline(std::cin, input);
        system("cls");
        std::cout << "\n";

        ParsedCommand command = ParseInput(input);

        if (command.action == Action::Quit) break;

        // TODO: Handle Action::Continue
        if (command.action == Action::Continue) {
            std::cout << "Nothing to continue yet.\n";
            continue;
        }

        if (command.action == Action::Upgrade) {
            HandleUpgrade(player, command);
            continue;
        }

        if (command.action == Action::Unknown) {
            std::cout << "...Not sure what that means. Try: chop, sell, buy, craft, eat, inv, quit.\n";
            continue;
        }

        if (command.action == Action::Inv) {
            player.PrintInventory();
            continue;
        }

        if (!IsActionAvailable(command.action, availableActions)) {
            std::cout << "Can't do that right now.\n";
            std::cout << std::format("Available right now: {}\n", PrintPrompt(availableActions));
            continue;
        }

        if (command.action == Action::Sell) {
            HandleSell(player, command, sellables);
            continue;
        }

        if (command.action == Action::Buy) {
            HandleBuy(player, command, buyables);
            continue;
        }

        if (command.action == Action::Craft && command.target.empty()) {
            HandleCraftListing(craftables, sellables);
            continue;
        }

        // Repeatable actions: executed once per unit of quantity
        for (int i = 0; i < command.quantity; i++) {
            if (command.action == Action::Chop) {
                if (!player.Chop(&wood)) {
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

    std::cout << "\nSee you next time, Barry.\n";
    return 0;
}
