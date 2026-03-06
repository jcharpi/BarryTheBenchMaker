#pragma once
#include <unordered_map>
#include "interfaces/Item.h"
#include "interfaces/Craftable.h"
#include "interfaces/Material.h"
#include "interfaces/Tool.h"
#include "items/Cake.h"
#include "items/tools/Axe.h"
#include "items/tools/Sword.h"

class Wood;

class Player {
private:
	int currentHealth;
	int maxHealth;
	int gold;
	Sword* sword;
	Axe* axe;
	std::unordered_map<ItemId, int> itemsOwned;
	std::unordered_map<ItemId, Item*> itemLookup;

public:
	Player(int maxHealth, int startingGold, Sword* sword, Axe* axe);

	int GetCurrentHealth() const;
	int GetMaxHealth() const;
	int GetGold() const;
	
	Sword* GetSword() const;
	Axe* GetAxe() const;
	
	const std::unordered_map<ItemId, int>& GetItemsOwned() const;
	void PrintInventory() const;

	void AddItem(Item* item, int amount);
	int GetItemCount(const Item* item) const;

	bool chopWood(Wood* wood);
	bool craft(Craftable* item);
	int sell(Item* item);
	bool eatCake();

	bool upgradeSword();
	bool upgradeAxe();
};
