#include <random>
#include <algorithm>
#include "../include/Enemy.h"

static std::mt19937 rng(std::random_device{}());

Enemy::Enemy(
	std::string name,
	int maxHp,
	int damage,
	float hitChance,
	float blockChance,
	std::vector<EnemyDrop> drops
) : name(name), maxHp(maxHp), damage(damage), hitChance(hitChance), blockChance(blockChance), drops(drops) {
	currentHp = maxHp;
	isBlocking = false;
	hitPenalty = 0.0f;
}

const std::string& Enemy::GetName() const {
	return name;
}

int Enemy::GetCurrentHp() const {
	return currentHp;
}

int Enemy::GetMaxHp() const {
	return maxHp;
}

int Enemy::GetDamage() const {
	return damage;
}

float Enemy::GetHitChance() {
	float effectiveHitChance = std::max(0.0f, hitChance - hitPenalty);
	hitPenalty = 0.0f; // Reset hitPenalty after applying it to the hit chance.
	return effectiveHitChance;
}

bool Enemy::IsBlocking() const {
	return isBlocking;
}

bool Enemy::IsDead() const {
	return currentHp <= 0;
}

void Enemy::TakeDamage(int amount) {
	currentHp = std::max(0, currentHp - amount);
}

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

void Enemy::SetHitPenalty(float penalty) {
	hitPenalty = penalty;
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
