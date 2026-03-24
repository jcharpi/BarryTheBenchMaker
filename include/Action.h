#pragma once
#include <string>
#include <vector>
#include "StoryPhase.h"

enum class Action {
	Buy,
	Chop,
	Continue, // continues to next encounter
	Craft,	// shown when owned items overlap any recipe's ingredients
	Eat,	  // shown when player has Cake
	Inv,
	Quit,
	Sell,	 // shown when player owns any sellable item
	Unknown,
	Upgrade,
};

struct ParsedCommand {
	Action action = Action::Unknown;
	int quantity = 1;
	std::string target;
};

struct World;

ParsedCommand ParseInput(const std::string& input);
std::vector<Action> GetAvailableActions(const World& world);
std::string ActionToString(Action action);
std::string FormatPrompt(const std::vector<Action>& available);
void HandleAction(const ParsedCommand& command, World& world, const std::vector<Action>& availableActions);
void PrintSettingText(StoryPhase phase);
