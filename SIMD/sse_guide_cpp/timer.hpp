/*! \file timer.hpp
    \brief Timing using C++11 chrono
    Copyright 2012 Tuomas Tonteri. This file is licensed as public domain.
*/

#ifndef X86TIMER_HPP
#define X86TIMER_HPP

#include <chrono>
using std::chrono::duration_cast;

/** Accurate timing and sleeping using C++11 chrono high resolution clock */
class timer {
private:

std::chrono::high_resolution_clock::time_point start_,end_;
typedef std::chrono::high_resolution_clock clock;
typedef std::chrono::duration<unsigned long long, std::pico> picoseconds;
typedef std::chrono::duration<double, typename clock::period> Cycle;

public:
void start()
{
start_ = clock::now();
}

/// Returns elapsed picoseconds
uint64_t stop()
{
end_ = clock::now();
auto ticks_per_iter = Cycle(end_-start_)/1;
return duration_cast<picoseconds>(ticks_per_iter).count();
}

};

#endif
