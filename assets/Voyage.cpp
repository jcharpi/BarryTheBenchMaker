#include <conio.h>
#include <format>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "../include/Dialogue.h"
#include "../include/Voyage.h"

// region Event definitions
struct VoyageEvent {
	std::string name;
	std::vector<std::string> descriptions;
	int minDamage;
	int maxDamage;
};

static const std::vector<VoyageEvent> events = {
	{ "Storm", {
		"A wave hit the port side like a fist. Planks screamed.",
		"Lightning struck the water twenty yards off the bow. Close enough to taste the air.",
		"The wind changed direction without warning. The mast groaned under the sudden strain.",
		"Rain came in sideways, hard enough to sting. Visibility dropped to nothing.",
		"A swell lifted the ship and dropped it into the trough. Something cracked below deck.",
	}, 8, 25 },
	{ "Leak", {
		"Water seeped through a join in the hull. Slow at first, then not slow at all.",
		"A plank below the waterline had worked itself loose. The bilge was rising.",
		"Barry heard dripping from somewhere he couldn't reach. Never a good sign.",
	}, 5, 15 },
	{ "Debris", {
		"A floating log slammed into the hull. The impact rattled Barry's teeth.",
		"Something scraped along the underside of the ship. Rock or wreckage, hard to say.",
		"Driftwood caught in the rudder. Barry heard the wood splitting before he felt the drag.",
		"The ship clipped a submerged rock. The jolt sent supplies sliding across the deck.",
	}, 10, 20 },
	{ "Sea Creature", {
		"Something large moved beneath the hull. A shadow wider than the ship.",
		"A tentacle broke the surface off starboard. It tested the hull, then pulled away. It left marks.",
		"The water went still. Then the ship lurched sideways as something rammed it from below.",
		"Barnacle-crusted teeth raked the hull. Whatever it was, it was tasting the wood.",
	}, 15, 35 },
	{ "Rogue Wave", {
		"The horizon tilted. A wall of water rose ahead, taller than the mast.",
		"A wave came from nowhere. The ship climbed it, hung at the crest, and dropped.",
	}, 20, 40 },
};
// endregion

static void PrintVoyageStatus(int shipHealth, int maxShipHealth) {
	float percent = (float)shipHealth / (float)maxShipHealth * 100.0f;
	std::string condition;
	if (percent > 75.0f) condition = "Seaworthy";
	else if (percent > 50.0f) condition = "Battered";
	else if (percent > 25.0f) condition = "Taking on water";
	else condition = "Breaking apart";

	std::cout << std::format("\n  [ Ship: {}/{} — {} ]\n", shipHealth, maxShipHealth, condition);
}

VoyageResult RunVoyage(int shipHealth) {
	PlayDialogue(LoadDialogue("data/preShip.json"));

	const int maxShipHealth = shipHealth;

	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> eventCountDist(5, 10);
	const int totalEvents = eventCountDist(rng);

	std::cout << "\nThe chandler looked at the gold and nodded.\n";
	std::cout << "\nBarry set sail for Crane's Reach.\n";
	PrintVoyageStatus(shipHealth, maxShipHealth);
	std::cout << "\n[Press any key to set sail]";
	(void)_getch();

	for (int i = 0; i < totalEvents && shipHealth > 0; i++) {
		system("cls");

		std::uniform_int_distribution<int> eventDist(0, (int)events.size() - 1);
		const auto& event = events[eventDist(rng)];

		std::uniform_int_distribution<int> descDist(0, (int)event.descriptions.size() - 1);
		const std::string& description = event.descriptions[descDist(rng)];

		// Roll damage
		std::uniform_int_distribution<int> damageDist(event.minDamage, event.maxDamage);
		int damage = damageDist(rng);

		std::cout << std::format("\n--- {} ({}/{}) ---\n", event.name, i + 1, totalEvents);
		std::cout << "\n" << description << "\n";
		std::cout << std::format("\n  -{} hull damage\n", damage);

		shipHealth -= damage;

		if (shipHealth <= 0) {
			shipHealth = 0;
			std::cout << "\n  The ship is breaking apart!\n";
		}

		PrintVoyageStatus(shipHealth, maxShipHealth);
		std::cout << "\n[Press any key to continue]";
		(void)_getch();
	}

	system("cls");

	if (shipHealth > 0) {
		PlayDialogue(LoadDialogue("data/postShip.json"));
		return VoyageResult::Arrived;
	} else {
		std::cout << "\nThe hull split with a sound like a tree falling. Water poured through the breach faster than any man could bail.\n";
		std::cout << "\nBarry grabbed what he could and went over the side. The cold hit him like a wall.\n";
		std::cout << "He swam until his arms burned, then swam further.\n";
		std::cout << "\nHe washed up on the Greyna shore sometime before dawn, half-drowned and fully broke.\n";
		std::cout << "\n...Going to need another ship.\n";
		std::cout << "\n[Press any key to continue]";
		(void)_getch();
		system("cls");
		return VoyageResult::Sunk;
	}
}
