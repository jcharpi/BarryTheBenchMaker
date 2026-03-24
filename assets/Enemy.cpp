#include <algorithm>

#include "../include/Enemy.h"
#include "../include/Random.h"

Enemy::Enemy(
	std::string name,
	int maxHealth,
	int damage,
	float hitChance,
	float blockChance,
	std::vector<EnemyDrop> drops
) : blockChance(blockChance), currentHealth(maxHealth), damage(damage), drops(drops), hitChance(hitChance), hitPenalty(0.0f), isBlocking(false), maxHealth(maxHealth), name(name) {
}

// Getters

float Enemy::GetBlockChance() const {
	return blockChance;
}

int Enemy::GetCurrentHealth() const {
	return currentHealth;
}

int Enemy::GetDamage() const {
	return damage;
}

float Enemy::GetHitChance() {
	float effectiveHitChance = std::max(0.0f, hitChance - hitPenalty);
	hitPenalty = 0.0f;
	return effectiveHitChance;
}

int Enemy::GetMaxHealth() const {
	return maxHealth;
}

const std::string& Enemy::GetName() const {
	return name;
}

// State

bool Enemy::IsBlocking() const {
	return isBlocking;
}

bool Enemy::IsDead() const {
	return currentHealth <= 0;
}

// Setters

void Enemy::SetHitPenalty(float penalty) {
	hitPenalty = penalty;
}

void Enemy::SetIsBlocking(bool blocking) {
	isBlocking = blocking;
}

// Actions

EnemyAction Enemy::ChooseAction() {
	std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
	float roll = distribution(GetRandomEngine());

	if (roll < blockChance) {
		isBlocking = true;
		return EnemyAction::Block;
	} else {
		return EnemyAction::Attack;
	}
}

void Enemy::ResetTurnState() {
	isBlocking = false;
}

std::vector<EnemyDrop> Enemy::RollDrops() const {
	std::vector<EnemyDrop> result;

	std::uniform_real_distribution<float> distribution(0.0f, 1.0f);

	for (const EnemyDrop& drop : drops) {
		if (drop.dropChance <= 0.0f || drop.dropChance > 1.0f) continue;

		float roll = distribution(GetRandomEngine());
		if (roll < drop.dropChance) {
			result.push_back(drop);
		}
	}

	return result;
}

void Enemy::TakeDamage(int amount) {
	currentHealth = std::max(0, currentHealth - amount);
}
