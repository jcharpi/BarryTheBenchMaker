#pragma once
#include <unordered_map>
#include "Sellable.h"

class Craftable : public Sellable {
private:
	int timeToCraft;
	std::unordered_map<ItemId, int> itemsRequired;

public:
	Craftable(ItemId id, std::string name, int sellAmount, int timeToCraft,
		const std::unordered_map<ItemId, int>& itemsRequired);

	int GetTimeToCraft() const;
	const std::unordered_map<ItemId, int>& GetItemsRequired() const;
	void SetItemsRequired(const std::unordered_map<ItemId, int>& newItemsRequired);
};
