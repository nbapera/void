#include "timer.hpp"

c_timer::c_timer(std::chrono::milliseconds everyXms)
{
	set_every(everyXms);
}

bool c_timer::is_elapsed()
{
	std::chrono::steady_clock::time_point timerNow = std::chrono::steady_clock::now();
	if (duration_cast<std::chrono::milliseconds>(timerNow - timer_begin) >= target_ms)
	{
		timer_begin = timerNow;
		return true;
	}
	return false;
}

void c_timer::set_every(std::chrono::milliseconds everyXms)
{
	timer_begin = std::chrono::steady_clock::now();
	target_ms = everyXms;
}

void c_timer::reset()
{
	timer_begin = std::chrono::steady_clock::now();
}