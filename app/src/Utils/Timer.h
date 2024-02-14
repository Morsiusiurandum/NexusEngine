#ifndef NEXUS_TIMER_H
#define NEXUS_TIMER_H

#include <chrono>
class Timer
{
 public:
	/**
	 * \brief Default constructor
	 */
	Timer();

	auto Mark() -> float;

	auto Peek() const -> float;

 private:
	std::chrono::steady_clock::time_point last;
};

#endif//NEXUS_TIMER_H
