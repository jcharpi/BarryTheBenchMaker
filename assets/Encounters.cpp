#include "../include/Encounter.h"
#include "../include/Combat.h"
#include "../include/Dialogue.h"
#include "../include/interfaces/Sellable.h"
#include <iostream>

Sellable bearPelt(ItemId::BearPelt, "Bear Pelt", 50);
Sellable goblinEar(ItemId::GoblinEar, "Goblin Ear", 15);
Sellable goblinCrown(ItemId::GoblinCrown, "Goblin Crown", 200);

Encounter BearEncounter() {
	return {
		"data/preBear.json",
		"data/postBear.json",
		{ Enemy("Forest Bear", 120, 20, 0.65f, 0.20f, { { &bearPelt, 0.75f, 1 } }) }
	};
}

Encounter GoblinEncounter() {
	return {
		"data/preGoblin.json",
		"data/postGoblin.json",
		{
			Enemy("Goblin", 40, 12, 0.55f, 0.15f, { { &goblinEar, 0.50f, 2 } }),
			Enemy("Goblin", 40, 12, 0.55f, 0.15f, { { &goblinEar, 0.50f, 2 } }),
			Enemy("Goblin", 40, 12, 0.55f, 0.15f, { { &goblinEar, 0.50f, 2 } }),
			Enemy("Goblin", 40, 12, 0.55f, 0.15f, { { &goblinEar, 0.50f, 2 } }),
			Enemy("Goblin", 40, 12, 0.55f, 0.15f, { { &goblinEar, 0.50f, 2 } }),
		}
	};
}

Encounter GoblinKingEncounter() {
	return {
		"data/preGoblinKing.json",
		"data/postGoblinKing.json",
		{ Enemy("Goblin King", 200, 30, 0.70f, 0.40f, { { &goblinCrown, 1.0f, 1 } }) }
	};
}

static CombatResult RunBear(Player& player, int& storyProgress) {
	Encounter bearEncounter = BearEncounter();
	PlayDialogue(LoadDialogue(bearEncounter.preCutscene));
	CombatResult result = RunCombat(player, bearEncounter.enemies);
	
	if (result == CombatResult::Victory) {
		PlayDialogue(LoadDialogue(bearEncounter.postCutscene));
		storyProgress = 1;
	} else {
		player.SetCurrentHealth(player.GetMaxHealth() / 2);
		player.LosePercentGold(25);
		std::cout << "\nBack in my workshop... Guess I'll have to prepare a bit more before starting off.\n";
	}
	return result;
}

static CombatResult RunGoblins(Player& player, int& storyProgress) {
	Encounter goblinsEncounter = GoblinEncounter();
	PlayDialogue(LoadDialogue(goblinsEncounter.preCutscene));
	CombatResult result = RunCombat(player, goblinsEncounter.enemies);
	
	if (result == CombatResult::Victory) {
		PlayDialogue(LoadDialogue(goblinsEncounter.postCutscene));
		storyProgress = 2;
	} else {
		player.SetCurrentHealth(player.GetMaxHealth() / 2);
		player.LoseAllCake();
		storyProgress = 1;
		std::cout << "\nUgh... back in Kelsa. I'm a bit worse for wear, and I feel a few cakes lighter.\n";
	}

	return result;
}


static CombatResult RunGoblinKing(Player& player, int& storyProgress) {
	Encounter goblinKingEncounter = GoblinKingEncounter();
	PlayDialogue(LoadDialogue(goblinKingEncounter.preCutscene));
	CombatResult result = RunCombat(player, goblinKingEncounter.enemies);

	if (result == CombatResult::Victory) {
		PlayDialogue(LoadDialogue(goblinKingEncounter.postCutscene));
		player.GetSword()->SetGoblinBlade();
		storyProgress = 3;
	} else {
		player.SetCurrentHealth(1);
		player.LosePercentCake(50);
		storyProgress = 1;
		std::cout << "\nUgh... back in Kelsa. I'm a bit worse for wear, and I feel a few cakes lighter.\n";
	}

	return result;
}

void RunEncounter(Player& player, int& storyProgress) {
	if (storyProgress == 0) RunBear(player, storyProgress);
	else if (storyProgress == 1) RunGoblins(player, storyProgress);
	else if (storyProgress == 2) RunGoblinKing(player, storyProgress);
}
