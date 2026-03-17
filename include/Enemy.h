#pragma once
#include <string>
#include <vector>
#include "interfaces/Item.h"

struct EnemyDrop {
	ItemId itemId;
	std::string itemName;
	int sellValue;
	float dropChance;
};

enum class EnemyAction {
	Attack,
	Block
};

class Enemy {
private:
	std::string name;

	int currentHp;
	int maxHp;

	int damage;
	float hitChance;
	float blockChance;

	bool isBlocking;
	float hitPenalty;

	std::vector<EnemyDrop> drops;

public:
	Enemy(
		std::string name,
		int maxHp,
		int damage,
		float hitChance,
		float blockChance,
		std::vector<EnemyDrop> drops
	);

	const std::string& GetName() const;
	int GetCurrentHp() const;
	int GetMaxHp() const;
	int GetDamage() const;
	float GetHitChance(); // not const — consumes hitPenalty as a side effect

	bool IsBlocking() const;
	bool IsDead() const;

	void TakeDamage(int amount);
	EnemyAction ChooseAction(); // not const — sets isBlocking as a side effect
	void SetHitPenalty(float penalty);
	void ResetTurnState();
	std::vector<EnemyDrop> RollDrops() const;
};
