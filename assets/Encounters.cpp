#include "../include/Encounter.h"
#include "../include/Combat.h"
#include "../include/Dialogue.h"
#include "../include/interfaces/Sellable.h"

static Sellable bearPelt(ItemId::BearPelt, "Bear Pelt", 50);
static Sellable goblinEar(ItemId::GoblinEar, "Goblin Ear", 15);
static Sellable goblinCrown(ItemId::GoblinCrown, "Goblin Crown", 200);

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

void RunEncounter(Player& player, int& storyProgress) {
	Encounter encounter;
	if (storyProgress == 0) encounter = BearEncounter();
	else if (storyProgress == 1) encounter = GoblinEncounter();
	else if (storyProgress == 2) encounter = GoblinKingEncounter();

	PlayDialogue(LoadDialogue(encounter.preCutscene));
	CombatResult result = RunCombat(player, encounter.enemies);

	if (result == CombatResult::Victory) {
		PlayDialogue(LoadDialogue(encounter.postCutscene));
		storyProgress++;
	}
}
