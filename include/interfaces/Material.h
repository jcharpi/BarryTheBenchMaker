#pragma once
#include "Sellable.h"

class Material : public Sellable {
private:
	int buyAmount;

public:
	Material(ItemId id, std::string name, int buyAmount, int sellAmount);

	int GetBuyAmount() const;
};
