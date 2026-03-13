#include "../include/Action.h"
#include "../include/Player.h"
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

    // Format is always: action quantity [target]
    std::string qtyStr;
    if (!(stream >> qtyStr)) {
        result.action = Action::Unknown;
        return result;
    }
    try {
        result.quantity = std::max(1, std::stoi(qtyStr));
    } catch (...) {
        result.action = Action::Unknown;
        return result;
    }
    stream >> result.target;
    std::transform(result.target.begin(), result.target.end(), result.target.begin(), ::tolower);

    return result;
}

std::vector<Action> GetAvailableActions(const Player& player) {
    std::vector<Action> available;

    const auto& owned = player.GetItemsOwned();

    bool hasMaterial = std::any_of(owned.begin(), owned.end(), [](const auto& p) {
        return p.first != ItemId::Sword && p.first != ItemId::Axe && p.first != ItemId::Cake;
    });
    bool hasSellable = std::any_of(owned.begin(), owned.end(), [](const auto& p) {
        return p.first != ItemId::Sword && p.first != ItemId::Axe;
    });

    available.push_back(Action::Buy);
    available.push_back(Action::Chop);
    if (hasMaterial) {
        available.push_back(Action::Craft);
    }
    if (owned.count(ItemId::Cake) > 0) {
        available.push_back(Action::Eat);
    }
    available.push_back(Action::Inv);
    available.push_back(Action::Quit);
    if (hasSellable) {
        available.push_back(Action::Sell);
    }
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
