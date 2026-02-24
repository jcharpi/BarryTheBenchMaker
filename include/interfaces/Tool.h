#pragma once
#include "Item.h"

class Tool : public Item {
private:
	int tier;

public:
	Tool(ItemId id, std::string name, int tier);

	int GetTier() const;
	void SetTier(int newTier);
};
