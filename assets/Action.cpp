#include "../include/Action.h"
#include "../include/Player.h"
#include "../include/interfaces/Craftable.h"
#include "../include/interfaces/Sellable.h"
#include <sstream>
#include <algorithm>
#include <vector>

ParsedCommand ParseInput(const std::string& input) {
    ParsedCommand result;

    std::string action;
    std::istringstream stream(input);
    stream >> action;
    std::transform(action.begin(), action.end(), action.begin(), ::tolower);

    if (action == "buy") result.action = Action::Buy;
    else if (action == "chop") result.action = Action::Chop;
    else if (action == "craft") result.action = Action::Craft;
    else if (action == "eat") result.action = Action::Eat;
    else if (action == "inv") result.action = Action::Inv;
    else if (action == "quit") result.action = Action::Quit;
    else if (action == "sell") result.action = Action::Sell;
    else result.action = Action::Unknown;

    // inv and quit take no arguments
    if (result.action == Action::Inv || result.action == Action::Quit) return result;

    std::string quantityString;
    if (!(stream >> quantityString)) {
        result.action = Action::Unknown;
        return result;
    }

    // Bound quantity to be positive
    try {
        result.quantity = std::max(1, std::stoi(quantityString));
    } catch (...) {
        result.action = Action::Unknown;
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

    // Action enum is defined alphabetically, so integer sort = alphabetical order
    std::sort(available.begin(), available.end());

    return available;
}

std::string ActionToString(Action action) {
    switch (action) {
        case Action::Buy: return "buy";
        case Action::Chop: return "chop";
        case Action::Craft: return "craft";
        case Action::Eat: return "eat";
        case Action::Inv: return "inv";
        case Action::Quit: return "quit";
        case Action::Sell: return "sell";
        default: return "???";
	}
}
