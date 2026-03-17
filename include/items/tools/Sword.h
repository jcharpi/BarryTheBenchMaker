#pragma once
#include "../../interfaces/Tool.h"

class Sword : public Tool {
private:
	int damage;

	static int GetDamageForTier(int tier);
	static float GetHitChanceForTier(int tier);
	static std::string GetNameForTier(int tier);

public:
	Sword();

	int GetDamage() const;
	float GetHitChance() const;
	int GetUpgradeCost() const override;
	void SetDamage(int newDamage);
	bool Upgrade() override;
};
