#include "../../../include/items/craftables/Bench.h"

namespace {
    std::unordered_map<ItemId, int> CreateBenchItemsRequired() {
        return {
            { ItemId::BenchLeg, 4 },
            { ItemId::BenchSeat, 1 }
        };
    }
}

Bench::Bench() :
	Craftable(ItemId::Bench, "Bench", 200, 35, CreateBenchItemsRequired()) {
}
