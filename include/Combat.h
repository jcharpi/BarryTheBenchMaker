#pragma once
#include <vector>
#include "Player.h"
#include "Enemy.h"

enum class CombatAction {
	Attack,
	Block,
	Eat,
	Parry
};

enum class CombatResult {
	Defeat,
	Victory
};

struct CombatCommand {
	CombatAction action;
	int target; // -1 means no target (Block, Eat)
};

bool ParseCombatInput(const std::string& input, CombatCommand& result);
void RenderCombatHUD(const Player& player, const std::vector<Enemy>& enemies);

CombatResult RunCombat(Player& player, std::vector<Enemy>& enemies);
