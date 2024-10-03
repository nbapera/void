#pragma once

#define M_PI       3.14159265358979323846   // pi
#include <cmath>
#include "../sdk/minecraft/gamesettings/gamesettings.hpp"


namespace aimassist {
	void run();

	inline bool enabled = false;
	inline int speed = 4;
	inline int fov = 27;
	inline double distance = 3.4;
	inline bool item_whitelist = false;
	inline bool check_invisibles = true;
	inline float random_amount = 4;

	inline float ingame_fov = 70;


	inline double calculate_radius(double fovAngle) {
		double fovRad = fovAngle * (M_PI / 180.0);

		double radius = tan(fovRad / 2.0);

		return radius;
	}


	inline bool draw_fov = false;

	void draw();

}