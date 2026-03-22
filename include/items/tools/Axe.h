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
	int GetUpgradeCost() const override;
	void SetTimeToChop(int newTimeToChop);
	bool Upgrade() override;
};
