#include "aimassist.hpp"
#include "../sdk/minecraft/minecraft.hpp"
#include "../sdk/minecraft/entity/entity.hpp"
#include "../sdk/java.hpp"
#include "clicker.hpp"

#include "../../vendors/imgui/imgui_impl_win32.h"
#include "../../vendors/imgui/imgui_impl_opengl2.h"

#include <random>
#include <iostream>
#include <windows.h>

float wrap_180(float value)
{
	while (value >= 180.f)
		value -= 360.f;
	while (value < -180.f)
		value += 360.f;
	return value;
}

std::pair<float, float> get_angles(double posX1, double posY1, double posZ1, double posX2, double posY2, double posZ2)
{
	double x = posX2 - posX1;
	double y = posY2 - posY1;
	double z = posZ2 - posZ1;

	double hypothenuse = sqrt(x * x + z * z);
	float yaw = ((atan2(z, x)) * 180.f / M_PI) - 90.f;
	float pitch = (-atan2(y, hypothenuse)) * 180.f / M_PI;

	return std::make_pair(yaw, pitch);
}


void aimassist::run() {

	if (!GetAsyncKeyState(VK_LBUTTON) || !enabled) { return; }
	if (instance->is_in_gui_state()) { return; }

	auto settings = std::make_unique<c_gamesettings>(java::env, instance->getGameSettings());

	if (localPlayer->getEntity() && world->getWorld()) {

		if (draw_fov) { ingame_fov = settings->get_fov(); }

		double targetDistance = distance;
		std::shared_ptr<c_entity_player> target = nullptr;

		for (auto entity : world->getPlayers())
		{
			if (!java::env->IsSameObject(entity->getEntity(), localPlayer->getEntity()))
			{
				if (!localPlayer->isInvisible() || check_invisibles)
				{
					double distance = sqrt(pow(localPlayer->getPosY() - entity->getPosY(), 2) + pow(sqrt(pow(localPlayer->getPosX() - entity->getPosX(), 2) + pow(localPlayer->getPosZ() - entity->getPosZ(), 2)), 2));

					if (distance < targetDistance)
					{
						target = entity;
						targetDistance = distance;
					}
				}
			}
		}

		std::string itemName = localPlayer->getCurrentItem();

		if (!item_whitelist || itemName._Equal("item.swordIron") || itemName._Equal("item.swordWood") || itemName._Equal("item.swordStone") || itemName._Equal("item.swordDiamond") || itemName._Equal("item.swordGold") || itemName._Equal("item.fishingRod"))
		{
			if (target)
			{
				float my_yaw = localPlayer->getRotationYaw();
				float my_pitch = localPlayer->getRotationPitch();

				auto angles = get_angles(localPlayer->getPosX(), localPlayer->getPosY(), localPlayer->getPosZ(), target->getPosX(), target->getPosY(), target->getPosZ());
				auto fovyaw = wrap_180(-(my_yaw - angles.first));
				auto fovpitch = wrap_180(-(my_pitch - angles.second));

				if (abs(wrap_180(-(my_yaw - angles.first))) <= fov)
				{

					// ANTICHEAT BYPASS METHOD 1 A BIT WEIRD MOUSE WIGGLING BUT WORKS

					/*auto device = std::random_device();
					auto engine = std::mt19937(device());
					auto gen = std::uniform_real_distribution<float>(fovyaw - random_amount, fovpitch + random_amount);

					float yaw = gen(engine);

					my_yaw += (yaw / (100 / speed)) * 0.25;*/


					auto device = std::random_device();
					auto engine = std::mt19937(device());
					auto gen = std::uniform_real_distribution<float>(speed - random_amount, speed + random_amount);
					float speed = gen(engine);

					//my_yaw += ((speed - 1) * 0.25);

					my_yaw += (fovyaw / (100 / speed)) * 0.25; //aclicker::_rand_val(0.5,1.2);

					//my_yaw = yaw;

					//std::cout << my_yaw << std::endl;

					localPlayer->setRotationYaw(my_yaw);
					Sleep(1);
					localPlayer->setPrevRotationYaw(my_yaw);



				}

			}
		}


	}

}

void aimassist::draw() {

	ImVec2 screenSize = ImGui::GetWindowSize();
	float radAimbotFov = (float)(aimassist::fov * M_PI / 180);
	float radViewFov = (float)(ingame_fov * M_PI / 180);
	float circleRadius = tanf(radAimbotFov / 2) / tanf(radViewFov / 2) * screenSize.x / 1.7325;

	ImGui::GetWindowDrawList()->AddCircle(ImVec2(screenSize.x / 2, screenSize.y / 2), circleRadius, ImColor(1.0f, 1.0f, 1.0f, 1.0f), circleRadius / 3, 1);
}