#pragma once
#include <string>
#include <vector>

enum class Action {
    Buy,
    Chop,
    Continue,// continues to next encounter
    Craft,   // shown when owned items overlap any recipe's ingredients
    Eat,     // shown when player has Cake
    Inv,
    Quit,
    Sell,    // shown when player owns any sellable item
    Unknown,
    Upgrade,
};

struct ParsedCommand {
    Action action = Action::Unknown;
    int quantity = 1;
    std::string target;
};

class Craftable;
class Player;
class Sellable;

ParsedCommand ParseInput(const std::string& input);
std::vector<Action> GetAvailableActions(const Player& player, const std::vector<Craftable*>& craftables, const std::vector<Sellable*>& sellables);
std::string ActionToString(Action action);
