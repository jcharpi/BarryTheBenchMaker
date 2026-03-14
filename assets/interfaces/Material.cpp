#include "../../include/interfaces/Material.h"

Material::Material(ItemId id, std::string name, int buyAmount, int sellAmount) :
	Sellable(id, name, sellAmount), buyAmount(buyAmount) {
}

int Material::GetBuyAmount() const {
	return buyAmount;
}

void Material::SetBuyAmount(int newBuyAmount) {
	buyAmount = newBuyAmount;
}
