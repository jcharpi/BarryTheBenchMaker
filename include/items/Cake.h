#pragma once
#include "../interfaces/Material.h"

class Cake : public Material {
private:
	int healAmount;

public:
	Cake(int buyAmount, int sellAmount, int healAmount);

	int GetHealAmount() const;
};
