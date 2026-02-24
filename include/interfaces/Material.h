#pragma once
#include <string>
#include "Item.h"

class Material : public Item {
private:
	int buyAmount;
	int sellAmount;

public:
	Material(ItemId id,
		std::string name,
		int buyAmount,
		int sellAmount);

	int GetBuyAmount() const;
	void SetBuyAmount(int newBuyAmount);

	int GetSellAmount() const;
	void SetSellAmount(int newSellAmount);
};
