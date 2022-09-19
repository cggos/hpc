#include <windows.h>
#include "gclTimer.h"

gclTimer::gclTimer(void): _clocks(0.0E0), _start(0.0E0)
{

	i64 ifreq;
	QueryPerformanceFrequency((LARGE_INTEGER*)&ifreq);
	_freq = (double) ifreq;

}

gclTimer::~gclTimer(void)
{
}

void gclTimer::Start(void)
{

    i64 istart;
    QueryPerformanceCounter((LARGE_INTEGER*)&istart);
    _start = (double) istart;

}

void gclTimer::Stop(void)
{

	double n = 0;

	i64 in;
	QueryPerformanceCounter((LARGE_INTEGER*)&in);
	n = (double) in;

	n -= _start;
	_start = 0.0E0;
	_clocks += n;

}

void gclTimer::Reset(void)
{

    _clocks = 0.0E0;

}

double gclTimer::GetElapsedTime(void)
{

    return _clocks / _freq;

}
