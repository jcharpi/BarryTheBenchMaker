#pragma once
#include <string>

enum class ItemId {
	Wood,
	Cake,
	BenchLeg,
	BenchSeat,
	Bench,
	Sword,
	Axe
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
