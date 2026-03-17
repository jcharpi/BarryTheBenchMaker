#pragma once
#include <vector>
#include "Player.h"
#include "Enemy.h"

// What the player can do on their turn.
// Note: Attack and Block share names with EnemyAction but are separate enums —
// they live in different scopes so there's no conflict.
enum class CombatAction {
	Attack,
	Block,
	Parry,
	Eat
};

// What RunCombat hands back to the caller (the main game loop).
enum class CombatResult {
	Victory,
	Defeat
};

// Draws the full combat HUD each frame:
//   - Numbered enemy list with HP bars (dead enemies show [DEAD])
//   - Player HP bar + gold + cake count
// Call this at the top of each round, after clearing the screen.
void RenderCombatHUD(const Player& player, const std::vector<Enemy>& enemies);

// Parses a raw input string into a CombatAction + optional target index.
// e.g. "attack 2" → { CombatAction::Attack, 2 }
//      "block"    → { CombatAction::Block,  -1 }
// Returns false if the input is unrecognized.
// Separate from the main Action parser — combat has its own input vocabulary.
struct CombatCommand {
	CombatAction action;
	int target;   // -1 means no target (Block, Parry with no index, Eat)
};
bool ParseCombatInput(const std::string& input, CombatCommand& out);

// The main combat loop. Runs until the player wins or dies.
// Modifies player HP/gold directly (via TakeDamage / LoseGold).
// On Victory: rolls enemy drops, adds them to player inventory, returns Victory.
// On Defeat:  applies 25% gold penalty, applies HP penalty, returns Defeat.
// Designed to handle 1 enemy (Phase 2) and scale to many (Phase 3) — hence vector.
CombatResult RunCombat(Player& player, std::vector<Enemy>& enemies);
