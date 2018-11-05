///////////////////////////////////////////////////////////////////////////////
// TSC.h
// =====
// Pentium class CPU has an instruction, RDTSC, to load the current time-stamp
// counter (TSC) to registers (edx:eax) which is a 64-bit integer.
// TSC is incremented every CPU tick (1/CPU_HZ) since CPU has been reset.
// For example, 1GHz CPU ticks 1,000,000,000 times per second.
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2005-11-26
// UPDATED: 2005-11-26
///////////////////////////////////////////////////////////////////////////////

#ifndef TSC_H
#define TSC_H

#pragma warning (disable : 4035)    // disable no return value warning

class TSC
{
public:
    TSC();
    ~TSC() {}

    void start() { tickStart = rdtsc(); }
    void stop()  { tickStop = rdtsc(); }
    unsigned long getTicks() const { return (unsigned long)(tickStop - tickStart - tickOverhead); } // downcast to long
    unsigned long getOverheadTicks() const { return (unsigned long)tickOverhead; }

private:
    unsigned __int64 rdtsc();

    unsigned __int64 tickStart;
    unsigned __int64 tickStop;
    unsigned __int64 tickOverhead;
};


inline TSC::TSC()
{
    tickStart = rdtsc();
    tickStop  = rdtsc();
    tickOverhead = tickStop - tickStart;
}

inline unsigned __int64 TSC::rdtsc()
{
    __asm {
        rdtsc
    }
}

#endif
