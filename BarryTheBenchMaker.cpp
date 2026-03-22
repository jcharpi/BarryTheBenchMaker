#include <algorithm>
#include <chrono>
#include <format>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

#include "include/Action.h"
#include "include/Dialogue.h"
#include "include/Encounter.h"
#include "include/Player.h"
#include "include/interfaces/Craftable.h"
#include "include/interfaces/Material.h"
#include "include/interfaces/Sellable.h"
#include "include/items/Cake.h"
#include "include/items/tools/Axe.h"
#include "include/items/tools/Sword.h"

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    while (true) {
        Sword sword;
        Axe axe;
        Material wood(ItemId::Wood, "Wood", 1, 1);
        Cake cake(1, 1, 1);
        Craftable benchLeg (ItemId::BenchLeg,  "Bench Leg",  1, 1, {{ItemId::Wood, 1}});
        Craftable benchSeat(ItemId::BenchSeat, "Bench Seat", 1, 1, {{ItemId::Wood, 1}});
        Craftable bench    (ItemId::Bench,     "Bench",      1, 1, {{ItemId::BenchLeg, 1}, {ItemId::BenchSeat, 1}});

        int storyProgress = 0;

        std::vector<Material*> buyables    = { &cake };
        std::vector<Craftable*> craftables  = { &benchLeg, &benchSeat, &bench };
        std::vector<Sellable*> sellables    = { &wood, &cake, &benchLeg, &benchSeat, &bench, &bearPelt, &goblinEar, &goblinCrown };

    Player player(1, 1, &sword, &axe);

        PlayDialogue(LoadDialogue("data/opening.json"));
        std::cout << "Ashpeak. The goblin tunnels.\n";
        std::cout << "...Going to need supplies. Cake for the road. A better blade, maybe.\n";
        std::cout << "All of that costs gold.\n";
        std::cout << "Gold means benches. Quick ones, nothing like the Settle. No time for that now.\n";

        auto startTime = std::chrono::steady_clock::now();
        bool gameCompleted = false;
        std::string input;

        while (true) {
            std::vector<Action> availableActions = GetAvailableActions(player, craftables, sellables);
            std::cout << std::format("\nWhat next? {}\n> ", PrintPrompt(availableActions));
            std::getline(std::cin, input);
            system("cls");
            std::cout << "\n";

            ParsedCommand command = ParseInput(input);

            if (command.action == Action::Quit) break;

            HandleAction(command, player, storyProgress, availableActions, &wood, buyables, craftables, sellables);

            if (storyProgress == 5) {
                gameCompleted = true;
                break;
            }
        }

        if (gameCompleted) {
            auto endTime = std::chrono::steady_clock::now();
            double totalSeconds = std::chrono::duration<double>(endTime - startTime).count();
            int hours = (int)totalSeconds / 3600;
            int minutes = ((int)totalSeconds % 3600) / 60;
            int seconds = (int)totalSeconds % 60;
            std::cout << std::format("\nTotal play time: {}h {}m {}s\n", hours, minutes, seconds);

            std::cout << "\nPlay again? (yes / no)\n> ";
            std::string choice;
            std::getline(std::cin, choice);
            std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
            if (choice == "yes" || choice == "y") {
                system("cls");
                continue;
            } else {
                break;
            }
        } else {
            std::cout << "\nSee you next time, Barry.\n";
            break;
        }
    }

    return 0;
}
