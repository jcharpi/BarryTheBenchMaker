#include <algorithm>
#include <sstream>
#include <vector>

#include "../include/Action.h"
#include "../include/Player.h"
#include "../include/interfaces/Craftable.h"
#include "../include/interfaces/Sellable.h"

ParsedCommand ParseInput(const std::string& input) {
    ParsedCommand result;

    std::string action;
    std::istringstream stream(input);
    stream >> action;
    std::transform(action.begin(), action.end(), action.begin(), ::tolower);

    if (action == "buy") result.action = Action::Buy;
    else if (action == "chop") result.action = Action::Chop;
	else if (action == "continue") result.action = Action::Continue;
    else if (action == "craft") result.action = Action::Craft;
    else if (action == "eat") result.action = Action::Eat;
    else if (action == "inv") result.action = Action::Inv;
    else if (action == "quit") result.action = Action::Quit;
    else if (action == "sell") result.action = Action::Sell;
	else if (action == "upgrade") result.action = Action::Upgrade;
    else result.action = Action::Unknown;

    // inv and quit take no arguments
    if (result.action == Action::Inv || result.action == Action::Quit) return result;

    std::string quantityString;
    if (!(stream >> quantityString)) return result;

    // Bound quantity to be positive
    try {
        result.quantity = std::max(1, std::stoi(quantityString));
    } catch (...) {
        // No quantity; treat it as the target with default quantity
        result.target = quantityString;
        std::transform(result.target.begin(), result.target.end(), result.target.begin(), ::tolower);
        return result;
    }

    stream >> result.target;
    std::transform(result.target.begin(), result.target.end(), result.target.begin(), ::tolower);

    return result;
}

std::vector<Action> GetAvailableActions(const Player& player, const std::vector<Craftable*>& craftables, const std::vector<Sellable*>& sellables) {
    std::vector<Action> available;
    const auto& itemsOwned = player.GetItemsOwned();

    available.push_back(Action::Buy);
    available.push_back(Action::Chop);
    available.push_back(Action::Continue);

    // Can craft if any owned item appears in at least one recipe
    if (std::any_of(craftables.begin(), craftables.end(), [&itemsOwned](const Craftable* craftable) {
        for (const auto& [requiredItemId, requiredCount] : craftable->GetItemsRequired())
            if (itemsOwned.count(requiredItemId)) return true;
        return false;
    })) available.push_back(Action::Craft);

    if (itemsOwned.count(ItemId::Cake)) available.push_back(Action::Eat);

    available.push_back(Action::Inv);
    available.push_back(Action::Quit);

    // Can sell if any owned item is in the sellables list
    if (std::any_of(sellables.begin(), sellables.end(), [&itemsOwned](const Sellable* sellable) {
        return itemsOwned.count(sellable->GetId());
    })) available.push_back(Action::Sell);

	const bool canUpgradeAxe = player.GetAxe() != nullptr && 
        player.GetGold() >= player.GetAxe()->GetUpgradeCost() && 
        player.GetAxe()->GetUpgradeCost() > 0;
	const bool canUpgradeSword = player.GetSword() != nullptr && 
        player.GetGold() >= player.GetSword()->GetUpgradeCost() && 
		player.GetSword()->GetUpgradeCost() > 0;
    if (canUpgradeAxe || canUpgradeSword) available.push_back(Action::Upgrade);

    std::sort(available.begin(), available.end());

    return available;
}

std::string ActionToString(Action action) {
    switch (action) {
        case Action::Buy: return "buy";
        case Action::Chop: return "chop";
		case Action::Continue: return "continue";
        case Action::Craft: return "craft";
        case Action::Eat: return "eat";
        case Action::Inv: return "inv";
        case Action::Quit: return "quit";
        case Action::Sell: return "sell";
		case Action::Upgrade: return "upgrade";
        default: return "???";
	}
}
