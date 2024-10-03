#pragma once

namespace velocity {
	inline bool enabled;

	inline bool air_only = false;
	inline bool moving = false;

	inline int chance = 50;

	inline int horizontal = 100;
	inline int vertical = 100;

	inline bool weapon_only = false;
	inline int delay = 2;

	void run();
}