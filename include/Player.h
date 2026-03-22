#pragma once
#include <unordered_map>
#include "interfaces/Craftable.h"
#include "interfaces/Item.h"
#include "interfaces/Material.h"
#include "interfaces/Sellable.h"
#include "interfaces/Tool.h"
#include "items/Cake.h"
#include "items/tools/Axe.h"
#include "items/tools/Sword.h"

class Player {
private:
	Axe* axe;
	int currentHealth;
	int gold;
	std::unordered_map<ItemId, Item*> itemLookup;
	std::unordered_map<ItemId, int> itemsOwned;
	int maxHealth;
	Sword* sword;

public:
	Player(int maxHealth, int startingGold, Sword* sword, Axe* axe);

	// Getters
	Axe* GetAxe() const;
	int GetCakeCount() const;
	int GetCurrentHealth() const;
	int GetGold() const;
	int GetItemCount(const Item* item) const;
	const std::unordered_map<ItemId, int>& GetItemsOwned() const;
	int GetMaxHealth() const;
	Sword* GetSword() const;

	// Inventory
	void AddItem(Item* item, int amount);
	bool Buy(Item* item, int quantity);
	bool Chop(Material* wood);
	bool Craft(Craftable* item);
	bool Eat();
	void PrintInventory() const;
	int Sell(Sellable* item, int quantity);

	// Combat
	void LoseAllCake();
	void LoseGold(int amount);
	void LosePercentCake(int percent);
	void LosePercentGold(int percent);
	void SetCurrentHealth(int health);
	void TakeDamage(int amount);
	bool UpgradeAxe();
	bool UpgradeSword();
};
