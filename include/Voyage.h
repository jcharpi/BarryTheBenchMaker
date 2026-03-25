#pragma once

enum class VoyageResult {
	Arrived,
	Sunk
};

VoyageResult RunVoyage(int shipHealth);
