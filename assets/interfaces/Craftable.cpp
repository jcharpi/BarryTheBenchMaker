#include "../../include/interfaces/Craftable.h"
#include <stdexcept>

Craftable::Craftable(ItemId id, std::string name, int sellAmount,
	int timeToCraft, const std::unordered_map<ItemId, int>& itemsRequired) :
	Sellable(id, name, sellAmount), timeToCraft(timeToCraft) {

	SetItemsRequired(itemsRequired);
}

int Craftable::GetTimeToCraft() const {
	return timeToCraft;
}

const std::unordered_map<ItemId, int>& Craftable::GetItemsRequired() const {
	return itemsRequired;
}

void Craftable::SetItemsRequired(const std::unordered_map<ItemId, int>& newItemsRequired) {
	for (const auto& [id, count] : newItemsRequired) {
		if (count <= 0) throw std::invalid_argument("SetItemsRequired: Required item count must be greater than 0.");
	}
	itemsRequired = newItemsRequired;
}
