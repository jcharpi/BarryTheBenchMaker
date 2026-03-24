#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>

#include "../include/Player.h"
#include "../include/interfaces/Sellable.h"

Player::Player(int maxHealth, int startingGold, Sword* sword, Axe* axe) :
	axe(axe),
	currentHealth(maxHealth),
	gold(startingGold),
	maxHealth(maxHealth),
	sword(sword) {
	if (sword != nullptr) {
		itemsOwned[sword->GetId()] = 1;
		itemLookup[sword->GetId()] = sword;
	}

	if (axe != nullptr) {
		itemsOwned[axe->GetId()] = 1;
		itemLookup[axe->GetId()] = axe;
	}
}

// Getters

Axe* Player::GetAxe() const {
	return axe;
}

int Player::GetCakeCount() const {
	return itemsOwned.count(ItemId::Cake) ? itemsOwned.at(ItemId::Cake) : 0;
}

int Player::GetCurrentHealth() const {
	return currentHealth;
}

int Player::GetGold() const {
	return gold;
}

int Player::GetItemCount(const Item* item) const {
	if (item == nullptr) return 0;

	const auto itemOwned = itemsOwned.find(item->GetId());
	if (itemOwned == itemsOwned.end()) return 0;

	return itemOwned->second;
}

const std::unordered_map<ItemId, int>& Player::GetItemsOwned() const {
	return itemsOwned;
}

int Player::GetMaxHealth() const {
	return maxHealth;
}

Sword* Player::GetSword() const {
	return sword;
}

// Inventory

void Player::AddItem(Item* item, int amount) {
	if (item == nullptr || amount <= 0) return;

	itemsOwned[item->GetId()] += amount;
	itemLookup[item->GetId()] = item;
}

bool Player::Buy(Item* item, int quantity) {
	if (item == nullptr || quantity <= 0) return false;

	auto* material = dynamic_cast<Material*>(item);
	if (material == nullptr) return false;

	const int totalCost = material->GetBuyAmount() * quantity;
	if (gold < totalCost) return false;

	gold -= totalCost;
	AddItem(item, quantity);
	return true;
}

bool Player::Chop(Material* wood) {
	if (axe == nullptr || wood == nullptr) return false;

	const int timeToChop = std::max(1, axe->GetTimeToChop());
	std::this_thread::sleep_for(std::chrono::seconds(timeToChop));
	itemsOwned[wood->GetId()] += 1;
	itemLookup[wood->GetId()] = wood;
	return true;
}

bool Player::Craft(Craftable* item) {
	if (item == nullptr) return false;

	const auto& requirements = item->GetItemsRequired();

	// Validate all required ingredients exist before consuming any
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

bool Player::Eat() {
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

void Player::PrintInventory() const {
	std::cout << std::format("{}/{} HP, {} gold\n", currentHealth, maxHealth, gold);
	if (itemsOwned.empty()) {
		std::cout << "Nothing here yet.\n";
		return;
	}
	for (const auto& [itemId, count] : itemsOwned) {
		std::string name = "Unknown";
		auto itemEntry = itemLookup.find(itemId);
		if (itemEntry != itemLookup.end()) name = itemEntry->second->GetName();
		std::cout << "- " << name << ": " << count << "\n";
	}
}

int Player::Sell(Sellable* item, int quantity) {
	if (item == nullptr || quantity <= 0) return 0;

	auto itemOwned = itemsOwned.find(item->GetId());
	if (itemOwned == itemsOwned.end() || itemOwned->second < quantity) return 0;

	itemOwned->second -= quantity;
	if (itemOwned->second == 0) itemsOwned.erase(itemOwned);

	const int totalEarned = item->GetSellAmount() * quantity;
	gold += totalEarned;
	return totalEarned;
}

// Combat

void Player::LoseAllCake() {
	itemsOwned.erase(ItemId::Cake);
}

void Player::LoseGold(int amount) {
	gold = std::max(0, gold - amount);
}

void Player::LosePercentCake(int percent) {
	auto cakeEntry = itemsOwned.find(ItemId::Cake);
	if (cakeEntry == itemsOwned.end()) return;

	int lost = (cakeEntry->second * percent) / 100;
	cakeEntry->second -= lost;
	if (cakeEntry->second <= 0) itemsOwned.erase(cakeEntry);
}

void Player::LosePercentGold(int percent) {
	gold = std::max(0, gold - ((gold * percent) / 100));
}

void Player::SetCurrentHealth(int health) {
	currentHealth = std::clamp(health, 0, maxHealth);
}

void Player::TakeDamage(int amount) {
	currentHealth = std::max(0, currentHealth - amount);
}

bool Player::UpgradeAxe() {
	if (axe == nullptr) return false;
	return axe->Upgrade();
}

bool Player::UpgradeSword() {
	if (sword == nullptr) return false;
	return sword->Upgrade();
}
