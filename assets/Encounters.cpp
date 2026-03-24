#include <algorithm>
#include <iostream>

#include "../include/Combat.h"
#include "../include/Dialogue.h"
#include "../include/Encounter.h"
#include "../include/World.h"

static Encounter BearEncounter(World& world) {
	return {
		"data/preBear.json",
		"data/postBear.json",
		{ Enemy("Forest Bear", 120, 20, 0.65f, 0.20f, { { &world.bearPelt, 0.75f, 1 } }) }
	};
}

static Encounter GoblinEncounter(World& world) {
	return {
		"data/preGoblin.json",
		"data/postGoblin.json",
		{
			Enemy("Goblin Brute",	55, 15, 0.50f, 0.25f, { { &world.goblinEar, 0.50f, 2 } }),
			Enemy("Goblin Tunneler", 35, 10, 0.55f, 0.15f, { { &world.goblinEar, 0.50f, 2 } }),
			Enemy("Goblin Miner",	40, 12, 0.50f, 0.20f, { { &world.goblinEar, 0.50f, 2 } }),
			Enemy("Goblin Scrapper", 25,  8, 0.70f, 0.10f, { { &world.goblinEar, 0.50f, 2 } }),
			Enemy("Goblin Runt",	 20,  6, 0.45f, 0.05f, { { &world.goblinEar, 0.50f, 2 } }),
		}
	};
}

static Encounter GoblinKingEncounter(World& world) {
	return {
		"data/preGoblinKing.json",
		"data/postGoblinKing.json",
		{ Enemy("Goblin King", 200, 30, 0.70f, 0.40f, { { &world.goblinCrown, 1.0f, 1 } }) }
	};
}

static Encounter CraneEncounter() {
	return {
		"data/preCrane.json",
		"data/postCrane.json",
		{
			Enemy("Lord Crane", 160, 25, 0.65f, 0.30f, {}),
			Enemy("Crane's Guard", 70, 15, 0.55f, 0.20f, {}),
			Enemy("Crane's Guard", 70, 15, 0.55f, 0.20f, {}),
		}
	};
}

static void RunBear(World& world) {
	Encounter encounter = BearEncounter(world);
	PlayDialogue(LoadDialogue(encounter.preCutscene));
	CombatResult result = RunCombat(world.player, encounter.enemies);

	if (result == CombatResult::Victory) {
		PlayDialogue(LoadDialogue(encounter.postCutscene));
		world.phase = StoryPhase::Kelsa;
	} else {
		world.player.SetCurrentHealth(std::max(1, world.player.GetMaxHealth() / 2));
		world.player.LosePercentGold(25);
		std::cout << "\nBack in my workshop... Guess I'll have to prepare a bit more before starting off.\n";
	}
}

static void RunGoblinKing(World& world) {
	Encounter encounter = GoblinKingEncounter(world);
	PlayDialogue(LoadDialogue(encounter.preCutscene));
	CombatResult result = RunCombat(world.player, encounter.enemies);

	if (result == CombatResult::Victory) {
		PlayDialogue(LoadDialogue(encounter.postCutscene));
		world.player.GetSword()->SetGoblinBlade();
		world.player.SetCurrentHealth(world.player.GetMaxHealth());
		world.phase = StoryPhase::Ship;
	} else {
		world.player.SetCurrentHealth(1);
		world.player.LosePercentCake(50);
		world.phase = StoryPhase::Kelsa;
		std::cout << "\nUgh... back in Kelsa. I'm a bit worse for wear, and I feel a few cakes lighter.\n";
	}
}

static void RunGoblins(World& world) {
	Encounter encounter = GoblinEncounter(world);
	PlayDialogue(LoadDialogue(encounter.preCutscene));
	CombatResult result = RunCombat(world.player, encounter.enemies);

	if (result == CombatResult::Victory) {
		PlayDialogue(LoadDialogue(encounter.postCutscene));
		RunGoblinKing(world);
	} else {
		world.player.SetCurrentHealth(std::max(1, world.player.GetMaxHealth() / 2));
		world.player.LoseAllCake();
		world.phase = StoryPhase::Kelsa;
		std::cout << "\nUgh... back in Kelsa. I'm a bit worse for wear, and I feel a few cakes lighter.\n";
	}
}

void RunCrane(World& world) {
	Encounter encounter = CraneEncounter();
	PlayDialogue(LoadDialogue(encounter.preCutscene));
	CombatResult result = RunCombat(world.player, encounter.enemies);

	if (result == CombatResult::Victory) {
		PlayDialogue(LoadDialogue(encounter.postCutscene));
		PlayDialogue(LoadDialogue("data/ending.json"));
		world.phase = StoryPhase::Complete;
	} else {
		world.player.SetCurrentHealth(1);
		world.player.LoseAllCake();
		world.phase = StoryPhase::Ship;
		std::cout << "\nBarry woke back in Greyna, battered and benchless. He'll need another ship.\n";
	}
}

void RunEncounter(World& world) {
	switch (world.phase) {
	case StoryPhase::Forest: RunBear(world); break;
	case StoryPhase::Kelsa: RunGoblins(world); break;
	default: break;
	}
}
