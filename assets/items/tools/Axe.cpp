#include "../../../include/items/tools/Axe.h"

int Axe::GetTimeToChopForTier(int tier) {
	switch (tier) {
	default:
	case 1:
		return 4;
	case 2:
		return 2;
	case 3:
		return 1;
	}
}

std::string Axe::GetNameForTier(int tier) {
	switch (tier) {
	default:
	case 1:
		return "Rusty Axe";
	case 2:
		return "Functional Axe";
	case 3:
		return "Sharp Axe";
	}
}

Axe::Axe() : Tool(ItemId::Axe, GetNameForTier(GetTier()), 1), timeToChop(GetTimeToChopForTier(GetTier())) {}

int Axe::GetTimeToChop() const {
	return timeToChop;
}

void Axe::SetTimeToChop(int newTimeToChop) {
	timeToChop = newTimeToChop;
}

int Axe::GetUpgradeCost() const {
	switch (GetTier()) {
	case 1: return 50;
	case 2: return 100;
	default: return 0;
	}
}

bool Axe::Upgrade() {
	const int currentTier = GetTier();
	if (currentTier >= 3) {
		return false;
	}

	const int newTier = currentTier + 1;
	SetTier(newTier);
	SetTimeToChop(GetTimeToChopForTier(newTier));
	SetName(GetNameForTier(newTier));
	return true;
}
