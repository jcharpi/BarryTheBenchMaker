#include <algorithm>
#include <random>

#include "../include/Enemy.h"

static std::mt19937 rng(std::random_device{}());

Enemy::Enemy(
	std::string name,
	int maxHp,
	int damage,
	float hitChance,
	float blockChance,
	std::vector<EnemyDrop> drops
) : blockChance(blockChance), damage(damage), drops(drops), hitChance(hitChance), hitPenalty(0.0f), isBlocking(false), maxHp(maxHp), name(name) {
	currentHp = maxHp;
}

// Getters

float Enemy::GetBlockChance() const {
	return blockChance;
}

int Enemy::GetCurrentHp() const {
	return currentHp;
}

int Enemy::GetDamage() const {
	return damage;
}

float Enemy::GetHitChance() {
	float effectiveHitChance = std::max(0.0f, hitChance - hitPenalty);
	hitPenalty = 0.0f;
	return effectiveHitChance;
}

int Enemy::GetMaxHp() const {
	return maxHp;
}

const std::string& Enemy::GetName() const {
	return name;
}

// State

bool Enemy::IsBlocking() const {
	return isBlocking;
}

bool Enemy::IsDead() const {
	return currentHp <= 0;
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
	std::uniform_real_distribution<float> dist(0.0f, 1.0f);
	float roll = dist(rng);

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

	std::uniform_real_distribution<float> dist(0.0f, 1.0f);

	for (const EnemyDrop& drop : drops) {
		if (drop.dropChance <= 0.0f || drop.dropChance > 1.0f) continue;

		float roll = dist(rng);
		if (roll < drop.dropChance) {
			result.push_back(drop);
		}
	}

	return result;
}

void Enemy::TakeDamage(int amount) {
	currentHp = std::max(0, currentHp - amount);
}
