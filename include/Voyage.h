#pragma once
#include "Player.h"

enum class VoyageResult {
	Arrived,
	Sunk
};

VoyageResult RunVoyage(int shipHealth);
