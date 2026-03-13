#pragma once
#include <string>
#include <vector>

enum class Action {
    Buy,    // Available if player has gold
    Chop,   // Always available — Barry always has his axe
    Craft,  // Available if player has materials for any recipe
    Eat,    // Available if player has at least one Cake
    Inv,    // Always available — just displays inventory
    Quit,   // Always available
    Sell,   // Available if inventory has any sellable items
    Unknown // Returned when input doesn't match any command
};

struct ParsedCommand {
    Action action = Action::Unknown;
    int quantity = 1;
    std::string target = "";
};

ParsedCommand ParseInput(const std::string& rawInput);
class Player;
std::vector<Action> GetAvailableActions(const Player& player);
std::string ActionToString(Action action);
