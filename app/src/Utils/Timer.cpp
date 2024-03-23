#include "Timer.h"

Timer::Timer()
{
    last   = std::chrono::steady_clock::now();
    _start = std::chrono::steady_clock::now();
}

auto Timer::Mark() -> float
{
    const auto old = last;
    last           = std::chrono::steady_clock::now();

    const std::chrono::duration<float> frame_time = last - old;
    return frame_time.count();
}

auto Timer::Peek() const -> float
{
    const std::chrono::duration<float> frame_time = std::chrono::steady_clock::now() - _start;
    return frame_time.count();
}
