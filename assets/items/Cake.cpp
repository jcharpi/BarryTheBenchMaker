#include "../../include/items/Cake.h"

Cake::Cake(int buyAmount, int sellAmount, int healAmount) :
	Material(ItemId::Cake, "Cake", buyAmount, sellAmount), healAmount(healAmount) {
}

int Cake::GetHealAmount() const {
	return healAmount;
}
