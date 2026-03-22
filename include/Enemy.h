#pragma once
#include <string>
#include <vector>
#include "interfaces/Sellable.h"

struct EnemyDrop {
	Sellable* item;
	float dropChance;
	int quantity;
};

enum class EnemyAction {
	Attack,
	Block
};

class Enemy {
private:
	float blockChance;
	int currentHealth;
	int damage;
	std::vector<EnemyDrop> drops;
	float hitChance;
	float hitPenalty;
	bool isBlocking;
	int maxHealth;
	std::string name;

public:
	Enemy(
		std::string name,
		int maxHp,
		int damage,
		float hitChance,
		float blockChance,
		std::vector<EnemyDrop> drops
	);

	// Getters
	float GetBlockChance() const;
	int GetCurrentHealth() const;
	int GetDamage() const;
	float GetHitChance(); // not const — consumes hitPenalty as a side effect
	int GetMaxHealth() const;
	const std::string& GetName() const;

	// State
	bool IsBlocking() const;
	bool IsDead() const;

	// Setters
	void SetHitPenalty(float penalty);
	void SetIsBlocking(bool blocking);

	// Actions
	EnemyAction ChooseAction(); // not const — sets isBlocking as a side effect
	void ResetTurnState();
	std::vector<EnemyDrop> RollDrops() const;
	void TakeDamage(int amount);
};
