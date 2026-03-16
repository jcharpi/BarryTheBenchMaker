#include "../include/Player.h"
#include "../include/interfaces/Sellable.h"
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
		std::cout << "Nothing here yet.\n";
		return;
	}

	std::cout << "Inventory\n";
	for (const auto& [itemId, count] : itemsOwned) {
		std::string name = "Unknown";
		auto item = itemLookup.find(itemId);
		if (item != itemLookup.end()) name = item->second->GetName();
		std::cout << "- " << name << ": " << count << "\n";
	}
}

void Player::AddItem(Item* item, int amount) {
	if (item == nullptr || amount <= 0) return;

	itemsOwned[item->GetId()] += amount;
	itemLookup[item->GetId()] = item;
}

int Player::GetItemCount(const Item* item) const {
	if (item == nullptr) return 0;

	const auto itemOwned = itemsOwned.find(item->GetId());
	if (itemOwned == itemsOwned.end()) return 0;

	return itemOwned->second;
}

bool Player::chop(Material* wood) {
	if (axe == nullptr || wood == nullptr) return false;

	const int timeToChop = std::max(1, axe->GetTimeToChop());
	std::this_thread::sleep_for(std::chrono::seconds(timeToChop));
	itemsOwned[wood->GetId()] += 1;
	itemLookup[wood->GetId()] = wood;
	return true;
}

bool Player::craft(Craftable* item) {
	if (item == nullptr) return false;

	const auto& requirements = item->GetItemsRequired();

	// Validate we have all required ingredients before consuming any
	for (const auto& [requiredItemId, requiredCount] : requirements) {
		const auto itemOwned = itemsOwned.find(requiredItemId);
		if (itemOwned == itemsOwned.end() || itemOwned->second < requiredCount) return false;
	}

	for (const auto& [requiredItemId, requiredCount] : requirements) {
		auto itemOwned = itemsOwned.find(requiredItemId);
		itemOwned->second -= requiredCount;
		if (itemOwned->second == 0) itemsOwned.erase(itemOwned);
	}

	itemsOwned[item->GetId()] += 1;
	itemLookup[item->GetId()] = item;
	return true;
}

int Player::sell(Sellable* item, int quantity) {
	if (item == nullptr || quantity <= 0) return 0;

	auto itemOwned = itemsOwned.find(item->GetId());
	if (itemOwned == itemsOwned.end() || itemOwned->second < quantity) return 0;

	itemOwned->second -= quantity;
	if (itemOwned->second == 0) itemsOwned.erase(itemOwned);

	const int totalEarned = item->GetSellAmount() * quantity;
	gold += totalEarned;
	return totalEarned;
}

bool Player::buy(Item* item, int quantity) {
	if (item == nullptr || quantity <= 0) return false;

	auto* material = dynamic_cast<Material*>(item);
	if (material == nullptr) return false;

	const int totalCost = material->GetBuyAmount() * quantity;
	if (gold < totalCost) return false;

	gold -= totalCost;
	AddItem(item, quantity);
	return true;
}

bool Player::eat() {
	auto ownedCakeEntry = itemsOwned.find(ItemId::Cake);
	if (ownedCakeEntry == itemsOwned.end()) return false;

	auto cakeLookupEntry = itemLookup.find(ItemId::Cake);
	if (cakeLookupEntry == itemLookup.end()) return false;

	auto* cake = dynamic_cast<Cake*>(cakeLookupEntry->second);
	if (cake == nullptr) return false;

	currentHealth = std::min(maxHealth, currentHealth + cake->GetHealAmount());
	ownedCakeEntry->second -= 1;
	if (ownedCakeEntry->second == 0) itemsOwned.erase(ownedCakeEntry);
	return true;
}

bool Player::upgradeSword() {
	if (sword == nullptr) return false;
	return sword->Upgrade();
}

bool Player::upgradeAxe() {
	if (axe == nullptr) return false;
	return axe->Upgrade();
}

void Player::TakeDamage(int amount) {
	currentHealth = std::max(0, currentHealth - amount);
}

void Player::SetCurrentHealth(int health) {
	currentHealth = std::clamp(health, 0, maxHealth);
}

void Player::LoseGold(int amount = 1) {
	if (amount < 0) {
		gold = std::max(0, gold - gold / 4);
	} else {
		gold = std::max(0, gold - amount);
	}
}
