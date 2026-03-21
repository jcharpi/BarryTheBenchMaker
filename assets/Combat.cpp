#include <algorithm>
#include <format>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

#include "../include/Combat.h"

static std::mt19937 rng(std::random_device{}());

// HUD

void RenderCombatHUD(const Player& player, const std::vector<Enemy>& enemies) {
	std::cout << "=== COMBAT ===\n";
	for (size_t i = 0; i < enemies.size(); i++) {
		std::string enemyBar;
		if (enemies[i].IsDead()) {
			enemyBar = "DEAD";
			std::cout << std::format("{}. {}  [{}]\n", i + 1, enemies[i].GetName(), enemyBar);
		} else {
			int filledLength = (enemies[i].GetCurrentHp() * 10) / enemies[i].GetMaxHp();
			enemyBar = std::string(filledLength, '#') + std::string(10 - filledLength, '-');
			std::cout << std::format("{}. {}  [{}]  {}/{}\n", i + 1, enemies[i].GetName(), enemyBar, enemies[i].GetCurrentHp(), enemies[i].GetMaxHp());
		}
	}

	int filledLength = (player.GetCurrentHealth() * 10) / player.GetMaxHealth();
	std::string playerBar = std::string(filledLength, '#') + std::string(10 - filledLength, '-');
	int cakeCount = player.GetCakeCount();

	std::cout << std::format("\nBarry  [{}]  {}/{}  | Gold: {} | Cakes: {}\n", playerBar, player.GetCurrentHealth(), player.GetMaxHealth(), player.GetGold(), cakeCount);
}

// Input

bool ParseCombatInput(const std::string& input, CombatCommand& result) {
	std::string action;
	std::istringstream stream(input);
	int target = 0;
	stream >> action;
	std::transform(action.begin(), action.end(), action.begin(), ::tolower);
	stream >> target;
	result.target = target - 1; // 0 → -1 (no target), 1 → 0, 2 → 1, etc.

	if (action == "attack") {
		result.action = CombatAction::Attack;
		return true;
	}
	if (action == "block") {
		result.action = CombatAction::Block;
		return true;
	}
	if (action == "eat") {
		result.action = CombatAction::Eat;
		return true;
	}
	if (action == "parry") {
		result.action = CombatAction::Parry;
		return true;
	}

	return false;
}

// Turn resolution helpers

static void ResolvePlayerAction(
	const CombatCommand& command,
	Player& player,
	std::vector<Enemy>& enemies,
	const std::vector<EnemyAction>& enemyActions,
	std::uniform_real_distribution<float>& dist)
{
	const float playerHitChance = player.GetSword()->GetHitChance();

	if (command.action == CombatAction::Attack) {
		Enemy& target = enemies[command.target];
		float hitChance = target.IsBlocking()
			? std::max(0.05f, playerHitChance - target.GetBlockChance())
			: playerHitChance;

		if (dist(rng) < hitChance) {
			int damage = player.GetSword()->GetDamage();
			target.TakeDamage(damage);
			std::cout << std::format("Barry hits {} for {} damage!\n", target.GetName(), damage);
		} else {
			std::cout << std::format("Barry swings at {} — misses.\n", target.GetName());
		}

	} else if (command.action == CombatAction::Block) {
		std::cout << "Barry braces.\n";

	} else if (command.action == CombatAction::Parry) {
		Enemy& target = enemies[command.target];
		EnemyAction targetAction = enemyActions[command.target];

		if (targetAction == EnemyAction::Attack) {
			// Parry success — negate the attack, weaken the enemy next turn
			target.SetHitPenalty(0.2f);
			std::cout << std::format("Barry parries {}! The attack is deflected — they're off-balance.\n", target.GetName());
		} else {
			// Parry stumble — enemy blocked, Barry is wide open next turn.
			// A penalty of -1.0f makes effectiveHitChance = hitChance + 1.0f,
			// which always exceeds 1.0f, so the hit roll always succeeds.
			const float GUARANTEED_HIT_PENALTY = -1.0f;
			target.SetHitPenalty(GUARANTEED_HIT_PENALTY);
			std::cout << std::format("Barry lunges — {} was blocking. Barry stumbles and is left wide open.\n", target.GetName());
		}

	} else if (command.action == CombatAction::Eat) {
		if (player.Eat()) {
			std::cout << std::format("Barry eats a cake. {}/{} HP.\n", player.GetCurrentHealth(), player.GetMaxHealth());
		} else {
			std::cout << "No cake left.\n";
		}
	}
}

static void ResolveEnemyAttacks(
	const CombatCommand& command,
	Player& player,
	std::vector<Enemy>& enemies,
	const std::vector<EnemyAction>& enemyActions,
	std::uniform_real_distribution<float>& dist)
{
	for (size_t i = 0; i < enemies.size(); i++) {
		if (enemies[i].IsDead()) continue;
		if (enemyActions[i] == EnemyAction::Block) {
			std::cout << std::format("{} braces.\n", enemies[i].GetName());
			continue;
		}

		// Skip this enemy's attack if it was successfully parried
		if (command.action == CombatAction::Parry && (int)i == command.target && enemyActions[i] == EnemyAction::Attack) continue;

		float effectiveHitChance = enemies[i].GetHitChance();
		if (command.action == CombatAction::Block) effectiveHitChance /= 2.0f;

		if (dist(rng) < effectiveHitChance) {
			int damage = enemies[i].GetDamage();
			player.TakeDamage(damage);
			std::cout << std::format("{} hits Barry for {} damage!\n", enemies[i].GetName(), damage);
		} else {
			std::cout << std::format("{} swings at Barry — misses.\n", enemies[i].GetName());
		}
	}
}

CombatResult RunCombat(Player& player, std::vector<Enemy>& enemies) {
	while (true) {
		if (std::all_of(enemies.begin(), enemies.end(), [](const Enemy& enemy) { return enemy.IsDead(); })) {
				for (Enemy& enemy : enemies) {
				std::vector<EnemyDrop> drops = enemy.RollDrops();
				for (const EnemyDrop& drop : drops) {
					player.AddItem(drop.item, drop.quantity);
					std::cout << std::format("{} dropped {}x {}.\n", enemy.GetName(), drop.quantity, drop.item->GetName());
				}
			}

			std::cout << "\nBarry is victorious! Hopefully this is the last of them...\n";
			return CombatResult::Victory;
		}

		if (player.GetCurrentHealth() <= 0) {
			player.SetCurrentHealth(player.GetMaxHealth() / 2);
			player.LosePercentGold(25);
			std::cout << "\nBarry collapses to the ground... but he's not out yet. He lost some gold, but at least he can keep fighting.\n";
			return CombatResult::Defeat;
		}

		for (Enemy& enemy : enemies) {
			if (!enemy.IsDead()) {
				enemy.ResetTurnState();
			}
		}

		RenderCombatHUD(player, enemies);

		// Player input loop
		CombatCommand command;
		std::string input;
		while (true) {
			std::cout << "\n(attack / block / parry / eat)\n> ";
			std::getline(std::cin, input);

			if (!ParseCombatInput(input, command)) {
				std::cout << "...Not an option. Try: attack, block, parry, eat.\n";
				continue;
			}

			// Attack and Parry require a valid, living target
			if (command.action == CombatAction::Attack || command.action == CombatAction::Parry) {
				if (command.target < 0 || command.target >= (int)enemies.size()) {
					std::cout << std::format("Which one? Pick a number (example: attack 1, parry 2).\n", enemies.size());
					continue;
				}
				if (enemies[command.target].IsDead()) {
					std::cout << "Already down.\n";
					continue;
				}
			}

			break;
		}

		// Enemy decisions
		std::vector<EnemyAction> enemyActions;
		for (Enemy& enemy : enemies) {
			if (!enemy.IsDead()) {
				enemyActions.push_back(enemy.ChooseAction());
			} else {
				enemyActions.push_back(EnemyAction::Attack); // placeholder for dead slots
			}
		}

		// Resolve the round
		std::uniform_real_distribution<float> dist(0.0f, 1.0f);
		ResolvePlayerAction(command, player, enemies, enemyActions, dist);
		ResolveEnemyAttacks(command, player, enemies, enemyActions, dist);
	}
}
