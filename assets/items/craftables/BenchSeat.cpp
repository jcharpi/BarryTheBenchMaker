#include "../../../include/items/craftables/BenchSeat.h"

namespace {
	std::unordered_map<ItemId, int> CreateBenchSeatItemsRequired() {
		return { { ItemId::Wood, 12 } };
	}
}

BenchSeat::BenchSeat() :
	Craftable(ItemId::BenchSeat, "Bench Seat", 90, 25, CreateBenchSeatItemsRequired()) {
}
