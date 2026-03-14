#include "../include/Action.h"
#include "../include/Player.h"
#include "../include/interfaces/Craftable.h"
#include "../include/interfaces/Item.h"
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
    if (result.action == Action::Inv || result.action == Action::Quit) {
        return result;
    }

    std::string quantity;
    if (!(stream >> quantity)) {
        result.action = Action::Unknown;
        return result;
    }

    // Bound quantity to be positive
    try {
        result.quantity = std::max(1, std::stoi(quantity));
    } catch (...) {
        result.action = Action::Unknown;
        return result;
    }

    stream >> result.target;
    std::transform(result.target.begin(), result.target.end(), result.target.begin(), ::tolower);

    return result;
}

std::vector<Action> GetAvailableActions(const Player& player, const std::vector<Craftable*>& craftables, const std::vector<Item*>& sellables) {
    std::vector<Action> availableActions;
    const auto& itemsOwned = player.GetItemsOwned();

    // Can craft if any owned item is an ingredient in at least one recipe
    bool hasIngredient = std::any_of(craftables.begin(), craftables.end(), [&itemsOwned](const Craftable* craftable) {
        for (const auto& [requiredItemId, requiredCount] : craftable->GetItemsRequired()) {
            if (itemsOwned.count(requiredItemId)) return true;
        }
        return false;
    });

    bool hasSellable = std::any_of(sellables.begin(), sellables.end(), [&itemsOwned](const Item* item) {
        return itemsOwned.count(item->GetId()) > 0;
    });

    availableActions.push_back(Action::Buy);
    availableActions.push_back(Action::Chop);
    if (hasIngredient) availableActions.push_back(Action::Craft);
    if (itemsOwned.count(ItemId::Cake)) availableActions.push_back(Action::Eat);
    availableActions.push_back(Action::Inv);
    availableActions.push_back(Action::Quit);
    if (hasSellable) availableActions.push_back(Action::Sell);

    return availableActions;
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
