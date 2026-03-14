#include "../include/Action.h"
#include "../include/Player.h"
#include "../include/interfaces/Craftable.h"
#include "../include/interfaces/Item.h"
#include <sstream>
#include <algorithm>
#include <vector>

ParsedCommand ParseInput(const std::string& input) {
    ParsedCommand result;

    std::string command;
    std::istringstream stream(input);
    stream >> command;
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);

    if (command == "buy") result.action = Action::Buy;
    else if (command == "chop") result.action = Action::Chop;
    else if (command == "craft") result.action = Action::Craft;
    else if (command == "eat") result.action = Action::Eat;
    else if (command == "inv") result.action = Action::Inv;
    else if (command == "quit") result.action = Action::Quit;
    else if (command == "sell") result.action = Action::Sell;
    else result.action = Action::Unknown;

    // inv and quit take no arguments
    if (result.action == Action::Inv || result.action == Action::Quit) {
        return result;
    }

    std::string quantityString;
    if (!(stream >> quantityString)) {
        result.action = Action::Unknown;
        return result;
    }
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

std::vector<Action> GetAvailableActions(const Player& player, const std::vector<Craftable*>& craftables, const std::vector<Item*>& sellableItems) {
    std::vector<Action> available;

    const auto& owned = player.GetItemsOwned();

    // Can craft if any owned item is an ingredient in at least one recipe
    bool hasCraftIngredient = std::any_of(craftables.begin(), craftables.end(), [&owned](const Craftable* craftable) {
        for (const auto& [requiredId, count] : craftable->GetItemsRequired()) {
            if (owned.count(requiredId)) return true;
        }
        return false;
    });

    bool hasSellable = std::any_of(sellableItems.begin(), sellableItems.end(), [&owned](const Item* item) {
        return owned.count(item->GetId()) > 0;
    });

    available.push_back(Action::Buy);
    available.push_back(Action::Chop);
    if (hasCraftIngredient) available.push_back(Action::Craft);
    if (owned.count(ItemId::Cake)) available.push_back(Action::Eat);
    available.push_back(Action::Inv);
    available.push_back(Action::Quit);
    if (hasSellable) available.push_back(Action::Sell);

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
