#include "../../include/interfaces/Tool.h"

Tool::Tool(ItemId id, std::string name, int tier) : Item(id, name), tier(tier) {}

int Tool::GetTier() const {
	return tier;
}

void Tool::SetTier(int newTier) {
	tier = newTier;
}
