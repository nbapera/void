#include <Windows.h>

namespace aclicker {
	inline bool toggled = false;
	inline bool toggled_right = false;

	inline bool sword_only = true;
	inline bool blocks_only = true;
	inline int cps = 15;
	inline int cps_right = 15;

	inline bool randomized = true;
	inline bool randomized_right = true;

	inline int left_clicker_key = 'V';
	inline int right_clicker_key = VK_F4;

	void run();
	void run_right();

	float _rand_val(float min, float max);

	inline bool is_pressed(BYTE x) {
		return GetAsyncKeyState(x) & 0x8000;
	}
	void precise_sleep(double secs);
}