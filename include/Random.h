#pragma once
#include <random>

inline std::mt19937& GetRandomEngine() {
	static std::mt19937 engine(std::random_device{}());
	return engine;
}
