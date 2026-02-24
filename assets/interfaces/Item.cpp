#include "../../include/interfaces/Item.h"

Item::Item(ItemId id, std::string name) : id(id), name(name) {}

ItemId Item::GetId() const {
	return id;
}

const std::string& Item::GetName() const {
	return name;
}

void Item::SetName(const std::string& newName) {
	name = newName;
}
