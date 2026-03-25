#pragma once
#include <string>
#include <vector>
#include "Enemy.h"

struct World;

struct Encounter {
	std::string preCutscene;
	std::string postCutscene;
	std::vector<Enemy> enemies;
};

void RunEncounter(World& world);
void RunCrane(World& world);
