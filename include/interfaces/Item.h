#pragma once
#include <string>

enum class ItemId {
	Axe,
	BearPelt,
	Bench,
	BenchLeg,
	BenchSeat,
	Cake,
	GoblinCrown,
	GoblinEar,
	Sword,
	Wood
};

class Item {
private:
	ItemId id;
	std::string name;

public:
	Item(ItemId id, std::string name);
	virtual ~Item() = default;

	ItemId GetId() const;
	const std::string& GetName() const;

protected:
	void SetName(const std::string& newName);
};
