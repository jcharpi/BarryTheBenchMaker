#pragma once
#include <string>
#include <unordered_map>
#include "Item.h"

class Craftable : public Item {
private:
	int sellAmount;
	int timeToCraft;
	std::unordered_map<ItemId, int> itemsRequired;

public:
	Craftable(ItemId id,
		std::string name,
		int sellAmount,
		int timeToCraft,
		const std::unordered_map<ItemId, int>& itemsRequired);

	int GetSellAmount() const;
	void SetSellAmount(int newSellAmount);

	int GetTimeToCraft() const;
	void SetTimeToCraft(int newTimeToCraft);

	const std::unordered_map<ItemId, int>& GetItemsRequired() const;
	void SetItemsRequired(const std::unordered_map<ItemId, int>& newItemsRequired);
};
