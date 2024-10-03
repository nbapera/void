#pragma once
#include <chrono>

class c_timer
{
public:
	c_timer(std::chrono::milliseconds everyXms);
	bool is_elapsed();
	void set_every(std::chrono::milliseconds everyXms);
	void reset();
private:
	std::chrono::steady_clock::time_point timer_begin;
	std::chrono::milliseconds target_ms;
};