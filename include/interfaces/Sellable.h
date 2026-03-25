#pragma once
#include "Item.h"

class Sellable : public Item {
private:
	int sellAmount;

public:
	Sellable(ItemId id, std::string name, int sellAmount);

	int GetSellAmount() const;
};
