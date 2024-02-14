#include "Timer.h"

Timer::Timer()
{
	using a = std::chrono::steady_clock;
	last = std::chrono::steady_clock::now();
}

auto Timer::Mark() -> float
{
	const auto old = last;
	last = std::chrono::steady_clock::now();
	const std::chrono::duration<float> frame_time = last - old;
	return frame_time.count();
}

auto Timer::Peek() const -> float
{
	const std::chrono::duration<float> frame_time = std::chrono::steady_clock::now() - last;
	return frame_time.count();
}