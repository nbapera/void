#include "clicker.hpp"
#include "../menu/menu.hpp"
#include <windows.h>
#include <iostream>
#include <random>
#include <thread>

#include "../sdk/minecraft/util/movingobject.hpp"
#include "../sdk/minecraft/entity/entity.hpp"
#include "../sdk/minecraft/minecraft.hpp"
#include "../sdk/timer.hpp"

long lastClickTime = 0;
int nextCps = aclicker::cps;

float aclicker::_rand_val(float min, float max) {

	++max;
	std::random_device device;
	std::mt19937 engine(device());
	std::uniform_real_distribution<> random_value(min, max);
	return (float)random_value(engine);

}

void aclicker::precise_sleep(double secs)
{
	while (secs > 5e-3)
	{
		auto start = std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		auto end = std::chrono::high_resolution_clock::now();

		auto observed = (end - start).count() / 1e9;
		secs -= observed;
	}

	/* ~~ spin lock */
	auto start = std::chrono::high_resolution_clock::now();
	while ((std::chrono::high_resolution_clock::now() - start).count() / 1e9 < secs);
}

void aclicker::run() {
	static c_timer timer(std::chrono::milliseconds(1000 / aclicker::cps - 3));

	if (!localPlayer) { return; }

	std::string itemName = localPlayer->getCurrentItem();

	if (aclicker::sword_only) {
		if (itemName != "item.swordDiamond" && itemName != "item.swordIron" &&
			itemName != "item.swordStone" && itemName != "item.swordGold" &&
			itemName != "item.swordWood") {
			return;
		}
	}

	if (instance->is_in_gui_state()) { return; }

	if (!toggled || menu::is_open) {
		return;
	}

	if (FindWindowA("LWJGL", nullptr) != GetForegroundWindow()) {
		return;
	}

	if (!timer.is_elapsed())
		return;

	if (!is_pressed(VK_LBUTTON) || is_pressed(VK_RBUTTON)) { return; }


	SendMessageW(GetForegroundWindow(), 0x201, MK_LBUTTON, MAKELPARAM(0, 0));
	SendMessageW(GetForegroundWindow(), 0x202, MK_LBUTTON, MAKELPARAM(0, 0));

	timer.set_every(std::chrono::milliseconds(1000 / int(_rand_val(aclicker::cps - 3, aclicker::cps + 4))));
}

void aclicker::run_right() {
	static c_timer timer(std::chrono::milliseconds(1000 / aclicker::cps_right - 3));

	if (!localPlayer) { return; }

	std::string itemName = localPlayer->getCurrentItem();

	if (aclicker::blocks_only) {
		if (!itemName.starts_with("tile")) {
			return;
		}
	}

	if (instance->is_in_gui_state()) { return; }

	if (!toggled_right || menu::is_open) {
		return;
	}

	if (FindWindowA("LWJGL", nullptr) != GetForegroundWindow()) {
		return;
	}

	if (!timer.is_elapsed())
		return;

	if (!is_pressed(VK_RBUTTON) || is_pressed(VK_LBUTTON)) { return; }


	SendMessageW(GetForegroundWindow(), WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(0, 0));
	SendMessageW(GetForegroundWindow(), WM_RBUTTONUP, MK_RBUTTON, MAKELPARAM(0, 0));

	timer.set_every(std::chrono::milliseconds(1000 / int(_rand_val(aclicker::cps_right - 3, aclicker::cps_right + 4))));
}