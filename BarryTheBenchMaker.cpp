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

static bool IsActionAvailable(Action action, const std::vector<Action>& available) {
    return std::find(available.begin(), available.end(), action) != available.end();
}

static Material* FindShopItem(const std::vector<Material*>& shopItems, const std::string& target) {
    for (Material* item : shopItems) {
        if (NormalizeName(item->GetName()) == target) return item;
    }
    return nullptr;
}

static Craftable* FindCraftable(const std::vector<Craftable*>& craftables, const std::string& target) {
    for (Craftable* item : craftables) {
        if (NormalizeName(item->GetName()) == target) return item;
    }
    return nullptr;
}

// ============================================================
// main  — the game loop
// ============================================================
int main()
{
    std::cout << "A good night's sleep! I feel well rested. Time to make some benches!\n";
    std::cout << "I need to gather some wood first. I can chop trees with my axe.\n";

    // Set up items — these are the "world" objects Barry interacts with.
    // They live here in main so their lifetime matches the whole game.
    Sword sword;
    Axe axe;
    Material wood(ItemId::Wood, "Wood", 15, 5);
    Cake cake(10, 5, 25);   // buy: 10 gold, sell: 5 gold, heals: 25 HP
    Craftable benchLeg(ItemId::BenchLeg,  "Bench Leg",  8,   10, {{ItemId::Wood, 2}});
    Craftable benchSeat(ItemId::BenchSeat, "Bench Seat", 90,  25, {{ItemId::Wood, 12}});
    Craftable bench(ItemId::Bench,      "Bench",      200, 35, {{ItemId::BenchLeg, 4}, {ItemId::BenchSeat, 1}});

    // Shop inventory — items available to purchase
    std::vector<Material*> shopItems = { &cake };

    // Craftable items
    std::vector<Craftable*> craftables = { &benchLeg, &benchSeat, &bench };

    // Item lookup for sell — maps ItemId to Item* for all world items
    // We pass this to the sell handler to resolve target names
    std::vector<Item*> allSellableItems = { &wood, &cake, &benchLeg, &benchSeat, &bench };

    Player player(100, 0, &sword, &axe);

    // --------------------------------------------------------
    // THE GAME LOOP
    // This runs forever until the player types "quit".
    // Each iteration:
    //   1. Print the prompt (what can Barry do right now?)
    //   2. Read a line of input
    //   3. Parse it into an action + quantity + optional target
    //   4. Check if the action is available
    //   5. Execute it (quantity times for repeatable actions)
    // --------------------------------------------------------
    std::string input;

    while (true) {
        std::vector<Action> available = GetAvailableActions(player);
        std::cout << std::format("\nTime to make some benches... or uh, I guess I could also: {}\n> ", PrintPrompt(available));
        std::getline(std::cin, input);

        ParsedCommand cmd = ParseInput(input);

        if (cmd.action == Action::Quit) {
            break;
        }

        if (cmd.action == Action::Unknown) {
            std::cout << "Hmm, not sure what that means. Try: chop 1, sell 1 wood, sell 3 wood, buy 2 cake, craft 1 benchleg\n";
            continue;
        }

        if (!IsActionAvailable(cmd.action, available)) {
            std::cout << "Ha! If only... unfortunately, seems like that's not an option for me right now.\n";
            std::cout << std::format("Available right now: {}\n", PrintPrompt(available));
            continue;
        }

        for (int i = 0; i < cmd.quantity; i++) {
            if (cmd.action == Action::Chop) {
                bool success = player.chop(&wood);
                if (!success) {
                    std::cout << "Couldn't chop.\n";
                    break;
                }

                std::cout << "Chopped! (" << i + 1 << "/" << cmd.quantity << ")\n";
            }

            else if (cmd.action == Action::Inv) {
                player.PrintInventory();
                break;
            }

            else if (cmd.action == Action::Eat) {
                std::cout << std::format("I'm sitting pretty at {}/{} health...\n", player.GetCurrentHealth(), player.GetMaxHealth());

                bool success = player.eat();
                if (!success) {
                    std::cout << "I'd love to eat some cake... but I'll have to buy some first!\n";
                    break;
                }

                std::cout << std::format("Ah that's better! Now I'm resting at {}/{} health...\n", player.GetCurrentHealth(), player.GetMaxHealth());
            }

            else if (cmd.action == Action::Sell) {
                if (cmd.target.empty()) {
                    // Show sellable items from player's inventory
                    std::cout << "What would you like to sell?\n";
                    bool hasSellable = false;
                    for (Item* item : allSellableItems) {
                        if (player.GetItemCount(item) == 0) continue;
                        int sellPrice = 0;
                        if (auto* m = dynamic_cast<Material*>(item)) sellPrice = m->GetSellAmount();
                        else if (auto* c = dynamic_cast<Craftable*>(item)) sellPrice = c->GetSellAmount();
                        if (sellPrice > 0) {
                            std::cout << std::format("  {} (x{}) — {} gold each\n",
                                item->GetName(), player.GetItemCount(item), sellPrice);
                            hasSellable = true;
                        }
                    }
                    if (!hasSellable) {
                        std::cout << "  Nothing to sell right now.\n";
                    }
                    std::cout << "(e.g., sell 1 wood  OR  sell 3 wood)\n";
                    break;
                }

                // Find the item by target name
                Item* toSell = nullptr;
                for (Item* item : allSellableItems) {
                    if (NormalizeName(item->GetName()) == cmd.target) { toSell = item; break; }
                }

                if (toSell == nullptr) {
                    std::cout << std::format("I don't have any \"{}\" to sell.\n", cmd.target);
                    break;
                }

                int goldEarned = player.sell(toSell);
                if (goldEarned == 0) {
                    std::cout << std::format("Couldn't sell {}.\n", toSell->GetName());
                    break;
                }
                std::cout << std::format("Sold 1 {} for {} gold! (Total gold: {})\n",
                    toSell->GetName(), goldEarned, player.GetGold());
            }

            else if (cmd.action == Action::Buy) {
                if (cmd.target.empty()) {
                    // Show shop listing
                    std::cout << "Welcome to the shop! Here's what's available:\n";
                    for (Material* item : shopItems) {
                        std::cout << std::format("  {} — {} gold\n", item->GetName(), item->GetBuyAmount());
                    }
                    std::cout << std::format("(e.g., buy 1 cake  OR  buy 2 cake)  [You have: {} gold]\n", player.GetGold());
                    break;
                }

                Material* toBuy = FindShopItem(shopItems, cmd.target);
                if (toBuy == nullptr) {
                    std::cout << std::format("I don't sell \"{}\" here.\n", cmd.target);
                    break;
                }

                bool success = player.buy(toBuy, cmd.quantity);
                if (!success) {
                    std::cout << std::format("Can't afford {}x {} — need {} gold but only have {}.\n",
                        cmd.quantity, toBuy->GetName(), toBuy->GetBuyAmount() * cmd.quantity, player.GetGold());
                    break;
                }
                std::cout << std::format("Bought {}x {} for {} gold! (Remaining gold: {})\n",
                    cmd.quantity, toBuy->GetName(), toBuy->GetBuyAmount() * cmd.quantity, player.GetGold());
            }

            else if (cmd.action == Action::Craft) {
                if (cmd.target.empty()) {
                    // Show craftable items listing
                    std::cout << "What would you like to craft?\n";
                    for (Craftable* item : craftables) {
                        std::string req = "";
                        for (const auto& [reqId, reqCount] : item->GetItemsRequired()) {
                            // Map ItemId back to a readable name via allSellableItems
                            std::string reqName = "item";
                            for (Item* wi : allSellableItems) {
                                if (wi->GetId() == reqId) { reqName = wi->GetName(); break; }
                            }
                            if (!req.empty()) req += ", ";
                            req += std::format("{} {}", reqCount, reqName);
                        }
                        std::cout << std::format("  {} (requires: {}) — sells for {} gold  [{}]\n",
                            item->GetName(), req, item->GetSellAmount(), NormalizeName(item->GetName()));
                    }
                    std::cout << "(e.g., craft 1 benchleg)\n";
                    break;
                }

                Craftable* toCraft = FindCraftable(craftables, cmd.target);
                if (toCraft == nullptr) {
                    std::cout << std::format("I don't know how to craft \"{}\".\n", cmd.target);
                    break;
                }

                bool success = player.craft(toCraft);
                if (!success) {
                    std::cout << std::format("Not enough materials to craft {}.\n", toCraft->GetName());
                    break;
                }

                std::cout << std::format("Crafting {}...\n", toCraft->GetName());
                std::this_thread::sleep_for(std::chrono::seconds(toCraft->GetTimeToCraft()));
                std::cout << std::format("Done! {} crafted. ({}/{})\n", toCraft->GetName(), i + 1, cmd.quantity);
            }
        }
    }

    std::cout << "\nSee you next time, Barry.\n";
    return 0;
}
