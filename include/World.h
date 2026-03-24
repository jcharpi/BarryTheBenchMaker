#pragma once
#include <vector>
#include "Player.h"
#include "StoryPhase.h"
#include "interfaces/Craftable.h"
#include "interfaces/Material.h"
#include "interfaces/Sellable.h"
#include "items/Cake.h"
#include "items/tools/Axe.h"
#include "items/tools/Sword.h"

struct World {
	// Tools
	Sword sword;
	Axe axe;

	// Items
	Material wood;
	Cake cake;
	Craftable benchLeg;
	Craftable benchSeat;
	Craftable bench;

	// Enemy drops
	Sellable bearPelt;
	Sellable goblinEar;
	Sellable goblinCrown;

	// Item lists
	std::vector<Material*> buyables;
	std::vector<Craftable*> craftables;
	std::vector<Sellable*> sellables;

	// Player
	Player player;

	// Story
	StoryPhase phase;

	World();
};
