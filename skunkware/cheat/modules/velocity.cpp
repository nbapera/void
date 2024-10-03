#include "velocity.hpp"
#include "../sdk/minecraft/entity/entity.hpp"

#include <iostream>


void velocity::run() {
    if (!enabled) {
        return;
    }

    const auto my_previous_pos = localPlayer->get_prev_pos();
    const auto my_pos = localPlayer->get_pos();

    if (velocity::air_only && localPlayer->is_on_ground()) {
        return;
    }

    if (velocity::moving && my_pos.x == my_previous_pos.x && my_pos.y == my_previous_pos.y && my_pos.z == my_previous_pos.z) {
        return;
    }

    static int previous_hurt_timer = -1;
    int current_hurt_timer = localPlayer->get_hurt_timer();

    if (current_hurt_timer == previous_hurt_timer) {
        return;
    }

    previous_hurt_timer = current_hurt_timer;

    if (current_hurt_timer != 20 - delay) {
        return;
    }

    if (rand() % 100 > chance) {
        return;
    }

    vec3_t motion = localPlayer->get_motion();

    motion.x *= horizontal / 100.0;
    motion.y *= vertical / 100.0;
    motion.z *= horizontal / 100.0;

    localPlayer->set_motion(motion);
}