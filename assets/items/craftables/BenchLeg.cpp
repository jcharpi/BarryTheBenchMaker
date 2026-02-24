#include "../../../include/items/craftables/BenchLeg.h"

namespace {
	std::unordered_map<ItemId, int> CreateBenchLegItemsRequired() {
		return { { ItemId::Wood, 2 } };
	}
}

BenchLeg::BenchLeg() :
	Craftable(ItemId::BenchLeg, "Bench Leg", 8, 10, CreateBenchLegItemsRequired()) {
}
