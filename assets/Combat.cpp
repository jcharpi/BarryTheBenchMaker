#include <algorithm>
#include <conio.h>
#include <format>
#include <iostream>
#include <sstream>
#include <string>

#include "../include/Combat.h"
#include "../include/Random.h"

// region HUD

void RenderCombatHUD(const Player& player, const std::vector<Enemy>& enemies) {
	std::cout << "=== COMBAT ===\n";
	for (size_t i = 0; i < enemies.size(); i++) {
		std::string enemyBar;
		if (enemies[i].IsDead()) {
			enemyBar = "DEFEATED";
			std::cout << std::format("{}. {}  [{}]\n", i + 1, enemies[i].GetName(), enemyBar);
		} else {
			int filledLength = (enemies[i].GetCurrentHealth() * 10) / enemies[i].GetMaxHealth();
			enemyBar = std::string(filledLength, '#') + std::string(10 - filledLength, '-');
			std::cout << std::format("{}. {}  [{}]  {}/{}\n", i + 1, enemies[i].GetName(), enemyBar, enemies[i].GetCurrentHealth(), enemies[i].GetMaxHealth());
		}
	}

	int filledLength = (player.GetCurrentHealth() * 10) / player.GetMaxHealth();
	std::string playerBar = std::string(filledLength, '#') + std::string(10 - filledLength, '-');
	int cakeCount = player.GetCakeCount();

	std::cout << std::format("\nBarry  [{}]  {}/{}  | Gold: {} | Cakes: {} | Stomach: {}%\n", playerBar, player.GetCurrentHealth(), player.GetMaxHealth(), player.GetGold(), cakeCount, player.GetFullness());
}

// region Input

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
	return false;
}

// region Turn resolution

static void ResolvePlayerAction(
	const CombatCommand& command,
	Player& player,
	std::vector<Enemy>& enemies,
	std::uniform_real_distribution<float>& distribution)
{
	const float playerHitChance = player.GetSword()->GetHitChance();

	if (command.action == CombatAction::Attack) {
		Enemy& target = enemies[command.target];
		float hitChance = target.IsBlocking()
			? std::max(0.05f, playerHitChance - target.GetBlockChance())
			: playerHitChance;

		if (distribution(GetRandomEngine()) < hitChance) {
			int damage = player.GetSword()->GetDamage();
			target.TakeDamage(damage);
			std::cout << std::format("Barry hits {} for {} damage!\n", target.GetName(), damage);
		} else {
			std::cout << std::format("Barry swings at {} — misses.\n", target.GetName());
		}

		player.ReduceFullness();

	} else if (command.action == CombatAction::Block) {
		std::cout << std::format("Barry braces against {}.\n", enemies[command.target].GetName());

	} else if (command.action == CombatAction::Eat) {
		if (player.IsFull()) {
			std::cout << "Too full to eat right now.\n";
		} else if (player.Eat()) {
			std::cout << std::format("Barry eats a cake. {}/{} HP. Stomach: {}%\n", player.GetCurrentHealth(), player.GetMaxHealth(), player.GetFullness());
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
	std::uniform_real_distribution<float>& distribution)
{
	const int blockReduction = player.GetSword()->GetDamage() / 2;

	for (size_t i = 0; i < enemies.size(); i++) {
		if (enemies[i].IsDead()) continue;
		if (enemyActions[i] == EnemyAction::Block) {
			std::cout << std::format("{} braces.\n", enemies[i].GetName());
			continue;
		}

		float effectiveHitChance = enemies[i].GetHitChance();

		if (distribution(GetRandomEngine()) < effectiveHitChance) {
			int damage = enemies[i].GetDamage();
			bool blocked = command.action == CombatAction::Block && (int)i == command.target;
			if (blocked) {
				damage = std::max(0, damage - blockReduction);
			}
			if (damage > 0) {
				player.TakeDamage(damage);
				std::cout << std::format("{} hits Barry for {} damage!{}\n", enemies[i].GetName(), damage,
					blocked ? " (blocked)" : "");
			} else {
				std::cout << std::format("{} strikes, but Barry's guard absorbs it completely!\n", enemies[i].GetName());
			}
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

			std::cout << "\nBarry is victorious!\n";
			std::cout << "\n[Press any key to continue]";
			(void)_getch();
			system("cls");
			return CombatResult::Victory;
		}

		if (player.GetCurrentHealth() <= 0) {
			std::cout << "\nBarry has fallen...\n";
			std::cout << "\n[Press any key to continue]";
			(void)_getch();
			system("cls");
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
			std::cout << "\n(attack <#> / block <#> / eat)\n> ";
			std::getline(std::cin, input);

			if (!ParseCombatInput(input, command)) {
				std::cout << "...Not an option. Try: attack, block, eat.\n";
				continue;
			}

			// Attack and block require a valid, living target
			if (command.action == CombatAction::Attack || command.action == CombatAction::Block) {
				if (command.target < 0 || command.target >= (int)enemies.size()) {
					std::cout << std::format("Which one? (example: {} 1).\n",
						command.action == CombatAction::Attack ? "attack" : "block");
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
		std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
		ResolvePlayerAction(command, player, enemies, distribution);
		ResolveEnemyAttacks(command, player, enemies, enemyActions, distribution);

		std::cout << "\n";
	}
}
