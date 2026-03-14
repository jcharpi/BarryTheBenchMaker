#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>

#include "include/Action.h"
#include "include/Player.h"
#include "include/interfaces/Material.h"
#include "include/interfaces/Craftable.h"
#include "include/interfaces/Sellable.h"
#include "include/items/tools/Sword.h"
#include "include/items/tools/Axe.h"
#include "include/items/Cake.h"

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

int main()
{
    std::cout << "A good night's sleep! I feel well rested. Time to make some benches!\n";
    std::cout << "I need to gather some wood first. I can chop trees with my axe.\n";

    Sword sword;
    Axe axe;
    Material wood(ItemId::Wood, Name: "Wood", buyAmount: 15, sellAmount: 5);
    Cake cake(buyAmount: 10, sellAmount: 5, healAmount: 25);
    Craftable benchLeg(ItemId::BenchLeg,   Name: "Bench Leg",  buyAmount: 8,   sellAmount: 10, ItemsRequired: {{ItemId::Wood, 2}});
    Craftable benchSeat(ItemId::BenchSeat, Name: "Bench Seat", buyAmount: 90,  sellAmount: 25, ItemsRequired: {{ItemId::Wood, 12}});
    Craftable bench(ItemId::Bench,         Name: "Bench",      buyAmount: 200, sellAmount: 35, ItemsRequired: {{ItemId::BenchLeg, 4}, {ItemId::BenchSeat, 1}});

    std::vector<Material*> buyables    = { &cake };
    std::vector<Craftable*> craftables  = { &benchLeg, &benchSeat, &bench };
    std::vector<Sellable*> sellables    = { &wood, &cake, &benchLeg, &benchSeat, &bench };

    Player player(currentHealth: 100, startingGold: 0, sword: &sword, axe: &axe);

    std::string input;

    while (true) {
        std::vector<Action> availableActions = GetAvailableActions(player, craftables, sellables);
        std::cout << std::format("\nTime to make some benches... or uh, I guess I could also: {}\n> ", PrintPrompt(availableActions));
        std::getline(std::cin, input);

        ParsedCommand command = ParseInput(input);

        if (command.action == Action::Quit) break;

        if (command.action == Action::Unknown) {
            std::cout << "Hmm, not sure what that means. Try: chop 1, sell 1 wood, buy 2 cake, craft 1 benchleg\n";
            continue;
        }

        if (command.action == Action::Inv) {
            player.PrintInventory();
            continue;
        }

        if (!IsActionAvailable(command.action, availableActions)) {
            std::cout << "Ha! If only... unfortunately, seems like that's not an option for me right now.\n";
            std::cout << std::format("Available right now: {}\n", PrintPrompt(availableActions));
            continue;
        }

        if (command.action == Action::Sell) {
            if (command.target.empty()) {
                std::cout << "What would you like to sell?\n";
                for (Sellable* sellable : sellables) {
                    if (player.GetItemCount(sellable) == 0) continue;
                    std::cout << std::format("  {} (x{}) — {} gold each\n",
                        sellable->GetName(), player.GetItemCount(sellable), sellable->GetSellAmount());
                }
                std::cout << "(e.g., sell 1 wood  OR  sell 3 wood)\n";
                continue;
            }

            Sellable* itemToSell = nullptr;
            for (Sellable* sellable : sellables) {
                if (NormalizeName(sellable->GetName()) == command.target) { itemToSell = sellable; break; }
            }

            if (itemToSell == nullptr) {
                std::cout << std::format("I don't have any \"{}\" to sell.\n", command.target);
                continue;
            }

            const int goldEarned = player.sell(itemToSell, command.quantity);
            if (goldEarned == 0) {
                std::cout << std::format("Couldn't sell {}.\n", itemToSell->GetName());
            } else {
                std::cout << std::format("Sold {}x {} for {} gold! (Total gold: {})\n",
                    command.quantity, itemToSell->GetName(), goldEarned, player.GetGold());
            }
            continue;
        }

        if (command.action == Action::Buy) {
            if (command.target.empty()) {
                std::cout << "Welcome to the shop! Here's what's available:\n";
                for (Material* item : buyables) {
                    std::cout << std::format("  {} — {} gold\n", item->GetName(), item->GetBuyAmount());
                }
                std::cout << std::format("(e.g., buy 1 cake  OR  buy 2 cake)  [You have: {} gold]\n", player.GetGold());
                continue;
            }

            Material* itemToBuy = FindMaterial(buyables, command.target);
            if (itemToBuy == nullptr) {
                std::cout << std::format("I don't sell \"{}\" here.\n", command.target);
                continue;
            }

            bool success = player.buy(itemToBuy, command.quantity);
            if (!success) {
                std::cout << std::format("Can't afford {}x {} — need {} gold but only have {}.\n",
                    command.quantity, itemToBuy->GetName(), itemToBuy->GetBuyAmount() * command.quantity, player.GetGold());
            } else {
                std::cout << std::format("Bought {}x {} for {} gold! (Remaining gold: {})\n",
                    command.quantity, itemToBuy->GetName(), itemToBuy->GetBuyAmount() * command.quantity, player.GetGold());
            }
            continue;
        }

        if (command.action == Action::Craft && command.target.empty()) {
            std::cout << "What would you like to craft?\n";
            for (Craftable* craftable : craftables) {
                std::string requirementsList;
                for (const auto& [requiredId, requiredCount] : craftable->GetItemsRequired()) {
                    // Look up the ingredient name by ID from the world item list
                    std::string requiredName = "item";
                    for (Sellable* sellable : sellables) {
                        if (sellable->GetId() == requiredId) { requiredName = sellable->GetName(); break; }
                    }
                    if (!requirementsList.empty()) requirementsList += ", ";
                    requirementsList += std::format("{} {}", requiredCount, requiredName);
                }
                std::cout << std::format("  {} (requires: {}) — sells for {} gold  [{}]\n",
                    craftable->GetName(), requirementsList, craftable->GetSellAmount(), NormalizeName(craftable->GetName()));
            }
            std::cout << "(e.g., craft 1 benchleg)\n";
            continue;
        }

        // Repeatable actions: executed once per unit of quantity
        for (int i = 0; i < command.quantity; i++) {
            if (command.action == Action::Chop) {
                if (!player.chop(&wood)) {
                    std::cout << "Couldn't chop.\n";
                    break;
                }
                std::cout << "Chopped! (" << i + 1 << "/" << command.quantity << ")\n";
            }

            else if (command.action == Action::Eat) {
                std::cout << std::format("I'm sitting pretty at {}/{} health...\n", player.GetCurrentHealth(), player.GetMaxHealth());
                if (!player.eat()) {
                    std::cout << "I'd love to eat some cake... but I'll have to buy some first!\n";
                    break;
                }
                std::cout << std::format("Ah that's better! Now I'm resting at {}/{} health...\n", player.GetCurrentHealth(), player.GetMaxHealth());
            }

            else if (command.action == Action::Craft) {
                Craftable* toCraft = FindCraftable(craftables, command.target);
                if (toCraft == nullptr) {
                    std::cout << std::format("I don't know how to craft \"{}\".\n", command.target);
                    break;
                }

                if (!player.craft(toCraft)) {
                    std::cout << std::format("Not enough materials to craft {}.\n", toCraft->GetName());
                    break;
                }

                std::cout << std::format("Crafting {}...\n", toCraft->GetName());
                std::this_thread::sleep_for(std::chrono::seconds(toCraft->GetTimeToCraft()));
                std::cout << std::format("Done! {} crafted. ({}/{})\n", toCraft->GetName(), i + 1, command.quantity);
            }
        }
    }

    std::cout << "\nSee you next time, Barry.\n";
    return 0;
}
