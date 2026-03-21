#pragma once
#include <string>
#include <vector>
#include "Combat.h"
#include "Enemy.h"
#include "Player.h"
#include "interfaces/Sellable.h"

extern Sellable bearPelt;
extern Sellable goblinEar;
extern Sellable goblinCrown;

struct Encounter {
	std::string preCutscene;
	std::string postCutscene;
	std::vector<Enemy> enemies;
};

Encounter BearEncounter();
Encounter GoblinEncounter();
Encounter GoblinKingEncounter();

void RunEncounter(Player& player, int& storyProgress);
