// BarryTheBenchMaker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "include/Player.h"
#include "include/items/tools/Sword.h"
#include "include/items/tools/Axe.h"
#include "include/items/materials/Wood.h"

int main()
{
    std::cout << "A good night's sleep! I feel well rested. Time to make some benches!\n";
	std::cout << "I need to gather some wood first. I can chop trees with my axe.\n";

	Sword sword;
	Axe axe;
	Wood wood;
	Player player(100, 0, &sword, &axe);

	std::string input;
	
	while (true) {
		std::cout << "\nCommand(chop/inv/quit): ";
		std::getline(std::cin, input);

		if (input == "quit") break;
		if (input == "chop") {
			player.chopWood(&wood);
			std::cout << "Chopped some wood... what's that give me? " << player.GetItemCount(&wood) << " piece(s)!\n";
		}
		else if (input == "inv") {
			player.PrintInventory();
		}
		else {
			std::cout << "Unknown command.\n";
		}
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
