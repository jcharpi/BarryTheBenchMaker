#include "../include/World.h"

World::World() :
	sword(),
	axe(),
	wood(ItemId::Wood, "Wood", 0, 3),
	cake(10, 5, 25),
	benchLeg(ItemId::BenchLeg, "Bench Leg", 8, 10, {{ItemId::Wood, 2}}),
	benchSeat(ItemId::BenchSeat, "Bench Seat", 60, 25, {{ItemId::Wood, 12}}),
	bench(ItemId::Bench, "Bench", 200, 35, {{ItemId::BenchLeg, 4}, {ItemId::BenchSeat, 1}}),
	bearPelt(ItemId::BearPelt, "Bear Pelt", 50),
	goblinEar(ItemId::GoblinEar, "Goblin Ear", 15),
	goblinCrown(ItemId::GoblinCrown, "Goblin Crown", 200),
	player(100, 0, &sword, &axe),
	phase(StoryPhase::Forest)
{
	buyables = { &cake };
	craftables = { &benchLeg, &benchSeat, &bench };
	sellables = { &wood, &cake, &benchLeg, &benchSeat, &bench, &bearPelt, &goblinEar, &goblinCrown };
}
