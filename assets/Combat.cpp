#include "../../include/Combat.h"
#include <iostream>
#include <format>
#include <string>
#include <random>

// ---------------------------------------------------------------------------
// RenderCombatHUD
// ---------------------------------------------------------------------------
// Called once per round before prompting the player.
// Should print something like:
//
//   === COMBAT ===
//   1. Forest Bear  [########--]  80/120
//
//   Barry  [######----]  60/100  | Gold: 42 | Cakes: 2
//
// Tips:
//   - Build the HP bar with a loop: fill '#' for filled portion, '-' for remainder.
//   - Bar width = 10 chars. filled = (currentHp * 10) / maxHp.
//   - Use std::format for clean number formatting.
//   - Dead enemies: skip the bar and just print "[DEAD]".

void RenderCombatHUD(const Player& player, const std::vector<Enemy>& enemies) {
	// TODO: Print "=== COMBAT ===" header.

	// TODO: Loop through enemies with an index (use a regular for loop, not range-based,
	// so you have the index number for targeting).
	// Print: "{i+1}. {name}  [{bar}]  {currentHp}/{maxHp}"
	// If IsDead(), print: "{i+1}. {name}  [DEAD]"

	// TODO: Print a blank line, then the player row:
	// "Barry  [{bar}]  {currentHp}/{maxHealth}  | Gold: {gold} | Cakes: {cakeCount}"
	// Player::GetItemCount() takes an Item* — you'll need a Cake instance, or
	// expose a cake count getter. Think about the cleanest way to get this number.
}

// ---------------------------------------------------------------------------
// ParseCombatInput
// ---------------------------------------------------------------------------
// Turns a raw string into a CombatCommand.
// "attack" or "attack 3" → Attack (target 0-indexed or -1)
// "block"                → Block
// "parry" or "parry 2"  → Parry
// "eat"                  → Eat
// Research: "C++ istringstream parse tokens" — same pattern as Action.cpp's ParseInput.

bool ParseCombatInput(const std::string& input, CombatCommand& out) {
	// TODO: Read the first word to determine action.
	// If it's "attack" or "parry", try to read a second word as an int for the target.
	// Target from user is 1-based ("attack 1" means enemies[0]) — store as 0-based internally.
	// Return false if first word doesn't match any action.
	return false;
}

// ---------------------------------------------------------------------------
// RunCombat — The Main Loop
// ---------------------------------------------------------------------------
// Structure (one iteration = one full round):
//   1. Check win condition: all enemies dead → Victory
//   2. Check lose condition: player HP <= 0 → Defeat
//   3. ResetTurnState() on all living enemies
//   4. RenderCombatHUD()
//   5. Prompt player, call ParseCombatInput() — loop until valid input
//   6. Each living enemy calls ChooseAction()
//   7. Resolve the turn (see resolution matrix below)
//   8. Print round summary, loop back to step 1

// Resolution matrix (player action vs enemy action):
//
//   Player \ Enemy  |  Attack                          |  Block
//   ----------------+----------------------------------+----------------------------------
//   Attack          | Player hits at base hitChance    | Player hits at (hitChance - enemy blockChance), min 5%
//   Block           | Enemy hits at half hit chance    | Nothing happens
//   Parry           | Enemy attack negated + enemy     | Barry stumbles — enemy guaranteed
//                   | gets -20% hit next turn          | hit next turn (enemy hitChance = 1.0)
//   Eat             | Heal 25 HP, enemy hits normally  | Heal 25 HP, nothing else

// Hitting: roll float [0.0, 1.0). If roll < effectiveHitChance, it's a hit.
// On a hit, deal the attacker's damage to the defender.

CombatResult RunCombat(Player& player, std::vector<Enemy>& enemies) {
	while (true) {

		// TODO: Step 1 — count living enemies. If 0, break to Victory.

		// TODO: Step 2 — if player HP <= 0, break to Defeat.

		// TODO: Step 3 — call ResetTurnState() on every living enemy.

		// TODO: Step 4 — RenderCombatHUD().

		// TODO: Step 5 — input loop.
		// Print "> " prompt, read a line, parse it. If invalid, print hint and loop.
		// For Attack/Parry, validate the target index is in range and the enemy isn't dead.

		// TODO: Step 6 — enemy actions.
		// Call ChooseAction() on each living enemy. Store results (you'll need them in step 7).
		// If ChooseAction() returns Block, set that enemy's isBlocking flag.
		// (You may want to expose a SetBlocking() setter on Enemy, or handle it here.)

		// TODO: Step 7 — resolve the turn using the matrix above.
		// Hint: resolve player's action against each enemy separately for multi-enemy later.
		// For Phase 2 (1 enemy), just resolve against enemies[0].

		// TODO: Print round summary — who hit who, for how much, any misses.
	}

	// Victory path
	// TODO: Roll drops for all enemies (RollDrops()), print what dropped,
	// add dropped items to player inventory as Sellables.
	// Research: player.AddItem() expects an Item* and a count.

	// Defeat path
	// TODO: player.LoseGold() with 25% of current gold.
	// HP penalty: set player HP to some reduced value (encounter-specific — hardcode for now).
	// Print defeat flavor text.

	return CombatResult::Victory; // placeholder — replace with actual return based on outcome
}
