#include "../../include/interfaces/Sellable.h"

Sellable::Sellable(ItemId id, std::string name, int sellAmount) :
	Item(id, name), sellAmount(sellAmount) {
}

int Sellable::GetSellAmount() const {
	return sellAmount;
}

void Sellable::SetSellAmount(int newSellAmount) {
	sellAmount = newSellAmount;
}
