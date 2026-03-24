#include <algorithm>
#include <chrono>
#include <format>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

#include "include/Action.h"
#include "include/Dialogue.h"
#include "include/World.h"

int main()
{
	SetConsoleOutputCP(CP_UTF8);

	while (true) {
		World world;

		PlayDialogue(LoadDialogue("data/opening.json"));
		PrintSettingText(world.phase);

		auto startTime = std::chrono::steady_clock::now();
		bool gameCompleted = false;
		std::string input;

		while (true) {
			std::vector<Action> availableActions = GetAvailableActions(world);
			std::cout << std::format("\nWhat next? {}\n> ", FormatPrompt(availableActions));
			std::getline(std::cin, input);
			system("cls");
			std::cout << "\n";

			ParsedCommand command = ParseInput(input);

			if (command.action == Action::Quit) break;

			StoryPhase previousPhase = world.phase;
			HandleAction(command, world, availableActions);

			if (world.phase != previousPhase) {
				PrintSettingText(world.phase);
			}

			if (world.phase == StoryPhase::Complete) {
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
