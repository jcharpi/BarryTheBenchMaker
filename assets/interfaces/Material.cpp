#include "../../include/interfaces/Material.h"

Material::Material(ItemId id, std::string name,
	int buyAmount, int sellAmount) :
	Item(id, name), buyAmount(buyAmount), sellAmount(sellAmount) {
}

int Material::GetBuyAmount() const {
	return buyAmount;
}

void Material::SetBuyAmount(int newBuyAmount) {
	buyAmount = newBuyAmount;
}

int Material::GetSellAmount() const {
	return sellAmount;
}

void Material::SetSellAmount(int newSellAmount) {
	sellAmount = newSellAmount;
}
