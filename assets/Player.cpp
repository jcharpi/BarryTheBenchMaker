#include "../include/Player.h"
#include "../include/items/materials/Wood.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>

Player::Player(int maxHealth, int startingGold, Sword* sword, Axe* axe) :
	currentHealth(maxHealth),
	maxHealth(maxHealth),
	gold(startingGold),
	sword(sword),
	axe(axe) {
	if (sword != nullptr) {
		itemsOwned[sword->GetId()] = 1;
		itemLookup[sword->GetId()] = sword;
	}

	if (axe != nullptr) {
		itemsOwned[axe->GetId()] = 1;
		itemLookup[axe->GetId()] = axe;
	}
}

int Player::GetCurrentHealth() const {
	return currentHealth;
}

int Player::GetMaxHealth() const {
	return maxHealth;
}

int Player::GetGold() const {
	return gold;
}

Sword* Player::GetSword() const {
	return sword;
}

Axe* Player::GetAxe() const {
	return axe;
}

const std::unordered_map<ItemId, int>& Player::GetItemsOwned() const {
	return itemsOwned;
}

void Player::PrintInventory() const {
	if (itemsOwned.empty()) {
		std::cout << "Inventory is empty! Get choppin' some wood!\n";
		return;
	}

	std::cout << "Inventory\n";
	for (const auto& [itemId, count] : itemsOwned) {
		std::string name = "Unknown";
		auto item = itemLookup.find(itemId);
		if (item != itemLookup.end() && item->second != nullptr) {
			name = item->second->GetName();
		}
		std::cout << "- " << name << ": " << count << "\n";
	}
}

void Player::AddItem(Item* item, int amount) {
	if (item == nullptr || amount <= 0) {
		return;
	}

	itemsOwned[item->GetId()] += amount;
	itemLookup[item->GetId()] = item;
}

int Player::GetItemCount(const Item* item) const {
	if (item == nullptr) {
		return 0;
	}

	const auto ownedItemEntry = itemsOwned.find(item->GetId());
	if (ownedItemEntry == itemsOwned.end()) {
		return 0;
	}

	return ownedItemEntry->second;
}

bool Player::chopWood(Wood* wood) {
	if (axe == nullptr || wood == nullptr) {
		return false;
	}

	const int timeToChop = std::max(1, axe->GetTimeToChop());
	std::this_thread::sleep_for(std::chrono::seconds(timeToChop));
	itemsOwned[wood->GetId()] += 1;
	itemLookup[wood->GetId()] = wood;
	return true;
}

bool Player::craft(Craftable* item) {
	if (item == nullptr) {
		return false;
	}

	const auto& requirements = item->GetItemsRequired();

	for (const auto& requirement : requirements) {
		const ItemId requiredItemId = requirement.first;
		const int requiredCount = requirement.second;

		const auto ownedItemEntry = itemsOwned.find(requiredItemId);
		if (ownedItemEntry == itemsOwned.end() || ownedItemEntry->second < requiredCount) {
			return false;
		}
	}

	for (const auto& requirement : requirements) {
		const ItemId requiredItemId = requirement.first;
		const int requiredCount = requirement.second;

		auto requiredItemInventoryEntry = itemsOwned.find(requiredItemId);
		if (requiredItemInventoryEntry == itemsOwned.end()) {
			continue;
		}

		requiredItemInventoryEntry->second -= requiredCount;
		if (requiredItemInventoryEntry->second <= 0) {
			itemsOwned.erase(requiredItemInventoryEntry);
		}
	}

	itemsOwned[item->GetId()] += 1;
	itemLookup[item->GetId()] = item;
	return true;
}

int Player::sell(Item* item) {
	if (item == nullptr) {
		return 0;
	}

	if (dynamic_cast<Tool*>(item) != nullptr) {
		return 0;
	}

	auto ownedItemEntry = itemsOwned.find(item->GetId());
	if (ownedItemEntry == itemsOwned.end() || ownedItemEntry->second <= 0) {
		return 0;
	}

	int sellAmount = 0;
	if (auto* material = dynamic_cast<Material*>(item); material != nullptr) {
		sellAmount = material->GetSellAmount();
	}
	else if (auto* craftable = dynamic_cast<Craftable*>(item); craftable != nullptr) {
		sellAmount = craftable->GetSellAmount();
	}

	if (sellAmount <= 0) {
		return 0;
	}

	ownedItemEntry->second -= 1;
	if (ownedItemEntry->second == 0) {
		itemsOwned.erase(ownedItemEntry);
	}

	gold += sellAmount;
	return sellAmount;
}

bool Player::eatCake() {
	auto ownedCakeEntry = itemsOwned.find(ItemId::Cake);
	if (ownedCakeEntry == itemsOwned.end() || ownedCakeEntry->second <= 0) {
		return false;
	}

	auto cakeLookupEntry = itemLookup.find(ItemId::Cake);
	if (cakeLookupEntry == itemLookup.end()) {
		return false;
	}

	auto* cake = dynamic_cast<Cake*>(cakeLookupEntry->second);
	if (cake == nullptr) {
		return false;
	}

	currentHealth = std::min(maxHealth, currentHealth + cake->GetHealAmount());
	ownedCakeEntry->second -= 1;
	if (ownedCakeEntry->second <= 0) {
		itemsOwned.erase(ownedCakeEntry);
	}
	return true;
}

bool Player::upgradeSword() {
	if (sword == nullptr) {
		return false;
	}

	return sword->Upgrade();
}

bool Player::upgradeAxe() {
	if (axe == nullptr) {
		return false;
	}

	return axe->Upgrade();
}
