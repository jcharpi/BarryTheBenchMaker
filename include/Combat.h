#pragma once
#include <vector>
#include "Player.h"
#include "Enemy.h"

enum class CombatAction {
	Attack,
	Block,
	Parry,
	Eat
};

enum class CombatResult {
	Victory,
	Defeat
};

void RenderCombatHUD(const Player& player, const std::vector<Enemy>& enemies);

struct CombatCommand {
	CombatAction action;
	int target;   // -1 means no target (Block, Parry with no index, Eat)
};

bool ParseCombatInput(const std::string& input, CombatCommand& out);

CombatResult RunCombat(Player& player, std::vector<Enemy>& enemies);
