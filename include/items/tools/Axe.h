#pragma once
#include "../../interfaces/Tool.h"

class Axe : public Tool {
private:
	int timeToChop;

	static int GetTimeToChopForTier(int tier);
	static std::string GetNameForTier(int tier);

public:
	Axe();

	int GetTimeToChop() const;
	void SetTimeToChop(int newTimeToChop);
	int GetUpgradeCost() const override;
	bool Upgrade();
};
