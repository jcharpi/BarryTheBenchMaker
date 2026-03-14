#pragma once
#include "Item.h"

// Base class for any item that can be sold. Provides sell price storage and access.
class Sellable : public Item {
private:
	int sellAmount;

public:
	Sellable(ItemId id, std::string name, int sellAmount);
	virtual ~Sellable() = default;

	int GetSellAmount() const;
	void SetSellAmount(int newSellAmount);
};
