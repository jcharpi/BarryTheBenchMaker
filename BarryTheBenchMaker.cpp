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

int main()
{
    std::cout << "A good night's sleep! I feel well rested. Time to make some benches!\n";
    std::cout << "I need to gather some wood first. I can chop trees with my axe.\n";

    Sword sword;
    Axe axe;
    Material wood(ItemId::Wood, "Wood", 15, 5);
    Cake cake(10, 5, 25);   // buy: 10g, sell: 5g, heals: 25 HP
    Craftable benchLeg(ItemId::BenchLeg,   "Bench Leg",  8,   10, {{ItemId::Wood, 2}});
    Craftable benchSeat(ItemId::BenchSeat, "Bench Seat", 90,  25, {{ItemId::Wood, 12}});
    Craftable bench(ItemId::Bench,         "Bench",      200, 35, {{ItemId::BenchLeg, 4}, {ItemId::BenchSeat, 1}});

    std::vector<Material*> shopItems    = { &cake };
    std::vector<Craftable*> craftables  = { &benchLeg, &benchSeat, &bench };
    std::vector<Item*> sellableItems    = { &wood, &cake, &benchLeg, &benchSeat, &bench };

    Player player(100, 0, &sword, &axe);

    std::string input;

    while (true) {
        std::vector<Action> available = GetAvailableActions(player, craftables, sellableItems);
        std::cout << std::format("\nTime to make some benches... or uh, I guess I could also: {}\n> ", PrintPrompt(available));
        std::getline(std::cin, input);

        ParsedCommand cmd = ParseInput(input);

        if (cmd.action == Action::Quit) break;

        if (cmd.action == Action::Unknown) {
            std::cout << "Hmm, not sure what that means. Try: chop 1, sell 1 wood, buy 2 cake, craft 1 benchleg\n";
            continue;
        }

        if (!IsActionAvailable(cmd.action, available)) {
            std::cout << "Ha! If only... unfortunately, seems like that's not an option for me right now.\n";
            std::cout << std::format("Available right now: {}\n", PrintPrompt(available));
            continue;
        }

        if (cmd.action == Action::Inv) {
            player.PrintInventory();
            continue;
        }

        if (cmd.action == Action::Sell) {
            if (cmd.target.empty()) {
                std::cout << "What would you like to sell?\n";
                for (Item* item : sellableItems) {
                    if (player.GetItemCount(item) == 0) continue;
                    int sellPrice = 0;
                    if (auto* m = dynamic_cast<Material*>(item)) sellPrice = m->GetSellAmount();
                    else if (auto* c = dynamic_cast<Craftable*>(item)) sellPrice = c->GetSellAmount();
                    if (sellPrice > 0) {
                        std::cout << std::format("  {} (x{}) — {} gold each\n",
                            item->GetName(), player.GetItemCount(item), sellPrice);
                    }
                }
                std::cout << "(e.g., sell 1 wood  OR  sell 3 wood)\n";
                continue;
            }

            Item* toSell = nullptr;
            for (Item* item : sellableItems) {
                if (NormalizeName(item->GetName()) == cmd.target) { toSell = item; break; }
            }

            if (toSell == nullptr) {
                std::cout << std::format("I don't have any \"{}\" to sell.\n", cmd.target);
                continue;
            }

            int goldEarned = player.sell(toSell, cmd.quantity);
            if (goldEarned == 0) {
                std::cout << std::format("Couldn't sell {}.\n", toSell->GetName());
            } else {
                std::cout << std::format("Sold {}x {} for {} gold! (Total gold: {})\n",
                    cmd.quantity, toSell->GetName(), goldEarned, player.GetGold());
            }
            continue;
        }

        if (cmd.action == Action::Buy) {
            if (cmd.target.empty()) {
                std::cout << "Welcome to the shop! Here's what's available:\n";
                for (Material* item : shopItems) {
                    std::cout << std::format("  {} — {} gold\n", item->GetName(), item->GetBuyAmount());
                }
                std::cout << std::format("(e.g., buy 1 cake  OR  buy 2 cake)  [You have: {} gold]\n", player.GetGold());
                continue;
            }

            Material* toBuy = FindShopItem(shopItems, cmd.target);
            if (toBuy == nullptr) {
                std::cout << std::format("I don't sell \"{}\" here.\n", cmd.target);
                continue;
            }

            bool success = player.buy(toBuy, cmd.quantity);
            if (!success) {
                std::cout << std::format("Can't afford {}x {} — need {} gold but only have {}.\n",
                    cmd.quantity, toBuy->GetName(), toBuy->GetBuyAmount() * cmd.quantity, player.GetGold());
            } else {
                std::cout << std::format("Bought {}x {} for {} gold! (Remaining gold: {})\n",
                    cmd.quantity, toBuy->GetName(), toBuy->GetBuyAmount() * cmd.quantity, player.GetGold());
            }
            continue;
        }

        // Repeatable actions: executed once per unit of quantity
        for (int i = 0; i < cmd.quantity; i++) {
            if (cmd.action == Action::Chop) {
                if (!player.chop(&wood)) {
                    std::cout << "Couldn't chop.\n";
                    break;
                }
                std::cout << "Chopped! (" << i + 1 << "/" << cmd.quantity << ")\n";
            }

            else if (cmd.action == Action::Eat) {
                std::cout << std::format("I'm sitting pretty at {}/{} health...\n", player.GetCurrentHealth(), player.GetMaxHealth());
                if (!player.eat()) {
                    std::cout << "I'd love to eat some cake... but I'll have to buy some first!\n";
                    break;
                }
                std::cout << std::format("Ah that's better! Now I'm resting at {}/{} health...\n", player.GetCurrentHealth(), player.GetMaxHealth());
            }

            else if (cmd.action == Action::Craft) {
                if (cmd.target.empty()) {
                    std::cout << "What would you like to craft?\n";
                    for (Craftable* item : craftables) {
                        std::string req;
                        for (const auto& [reqId, reqCount] : item->GetItemsRequired()) {
                            std::string reqName = "item";
                            for (Item* wi : sellableItems) {
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

                if (!player.craft(toCraft)) {
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
