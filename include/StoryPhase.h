#pragma once

enum class StoryPhase {
	Forest,   // before bear encounter
	Kelsa,    // after bear, preparing for goblins
	Ship,     // need to buy a ship to reach Crane's Reach
	Complete  // game finished
};

inline bool operator<(StoryPhase a, StoryPhase b) {
	return static_cast<int>(a) < static_cast<int>(b);
}

inline bool operator<=(StoryPhase a, StoryPhase b) {
	return static_cast<int>(a) <= static_cast<int>(b);
}

inline bool operator>(StoryPhase a, StoryPhase b) {
	return static_cast<int>(a) > static_cast<int>(b);
}

inline bool operator>=(StoryPhase a, StoryPhase b) {
	return static_cast<int>(a) >= static_cast<int>(b);
}
