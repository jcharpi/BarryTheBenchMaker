#pragma once
#include "Player.h"

enum class VoyageResult {
	Arrived,
	Sunk
};

VoyageResult RunVoyage(Player& player, int shipHealth);
