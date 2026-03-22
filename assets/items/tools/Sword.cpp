#include "../../../include/items/tools/Sword.h"

int Sword::GetDamageForTier(int tier) {
	switch (tier) {
	default:
	case 1:
		return 1;
	case 2:
		return 1;
	case 3:
		return 1;
	case 4:
		return 1;
	}
}

float Sword::GetHitChanceForTier(int tier) {
	switch (tier) {
	default:
	case 1:
		return 0.70f;
	case 2:
		return 0.75f;
	case 3:
		return 0.80f;
	case 4:
		return 0.85f;
	}
}

std::string Sword::GetNameForTier(int tier) {
	switch (tier) {
	default:
	case 1:
		return "Dull Sword";
	case 2:
		return "Serviceable Sword";
	case 3:
		return "Reliable Sword";
	case 4:
		return "Goblin Cleaver";
	}
}

Sword::Sword() : Tool(ItemId::Sword, GetNameForTier(GetTier()), 1), damage(GetDamageForTier(GetTier())) {}

int Sword::GetDamage() const {
	return damage;
}

float Sword::GetHitChance() const {
	return GetHitChanceForTier(GetTier());
}

void Sword::SetDamage(int newDamage) {
	damage = newDamage;
}

void Sword::SetGoblinBlade() {
	SetTier(4);
	SetDamage(GetDamageForTier(4));
	SetName(GetNameForTier(4));
}

int Sword::GetUpgradeCost() const {
	switch (GetTier()) {
	case 1: return 1;
	case 2: return 1;
	default: return 0;
	}
}

bool Sword::Upgrade() {
	const int currentTier = GetTier();
	if (currentTier >= 3) {
		return false;
	}

	const int newTier = currentTier + 1;
	SetTier(newTier);
	SetDamage(GetDamageForTier(newTier));
	SetName(GetNameForTier(newTier));
	return true;
}
