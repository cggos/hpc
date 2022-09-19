///////////////////////////////////////////////////////////////////////////////
// CpuInfo.cpp
// ===========
// Retrieve CPU information by cpuid
//
//  AUTHOR: Song Ho Ahn
// CREATED: 2005-11-18
// UPDATED: 2005-12-21
///////////////////////////////////////////////////////////////////////////////

#include "CpuInfo.h"
#include <cstring>
#include <iostream>
using std::cout;
using std::endl;

///////////////////////////////////////////////////////////////////////////////
// default constructor and destructor
///////////////////////////////////////////////////////////////////////////////
CpuInfo::CpuInfo()
{
    vendor[0] = '\0';
    tscFlag = mmxFlag = sseFlag = sse2Flag = amd3dnowFlag = amd3dnow2Flag = false;

    getInfo();
}

CpuInfo::~CpuInfo()
{
}




///////////////////////////////////////////////////////////////////////////////
// print itself
///////////////////////////////////////////////////////////////////////////////
void CpuInfo::printSelf() const
{
    cout << "Vendor: " << vendor << endl;
    cout  << "MMX: " << (mmxFlag ? "yes" : "no") << endl;
    cout  << "SSE: " << (sseFlag ? "yes" : "no") << endl;
    cout  << "SSE2: " << (sse2Flag ? "yes" : "no") << endl;
    cout << "3DNow!: " << (amd3dnowFlag ? "yes" : "no") << endl;
    cout << "3DNow!+: " << (amd3dnow2Flag ? "yes" : "no") << endl;
}



///////////////////////////////////////////////////////////////////////////////
// get vendor string
///////////////////////////////////////////////////////////////////////////////
const char* CpuInfo::getVendor() const
{
    return vendor;
}



///////////////////////////////////////////////////////////////////////////////
// get CPU info using inline asm
///////////////////////////////////////////////////////////////////////////////
void CpuInfo::getInfo()
{
    char vendor[13];
    unsigned int maxCalls;
    unsigned int regEax, regEdx;

    // MSVC specific inline assembly block ////////////////////////////////////

    // check cpuid is supported
    // If bit 21 (22nd bit) in EFLAGS can be toggled, cpuid is supported
    __asm {
        pushfd
        pop     eax                 // get flags
        mov     ebx,    eax         // copy the flags

        xor     eax,    0x200000    // reverse bit 21 (1->0, or 0->1)
        push    eax
        popfd                       // set flags
        pushfd
        pop     eax                 // re-get flags

        xor     eax,    ebx         // compare previous flags
        mov     regEax, eax         // it returns 0x200000, if bit 21 can be toggled, otherwise returns 0
    }

    // CPU does not support cpuid instruction, stop here
    if(!regEax)
        return;


    __asm {
        // first need to set eax to 0
        xor     eax,    eax

        // when call cpuid with eax=0, cpuid returns max number of cpuid calls and vendor string (ebx-edx-ecx)
        cpuid

        // copy max cpuid calls to maxCalls
        mov     maxCalls,   eax

        // copy vendor string (12 bytes, ebx-ecx-edx)
        mov     dword ptr [vendor],     ebx
        mov     dword ptr [vendor+4],   edx
        mov     dword ptr [vendor+8],   ecx
    }

    vendor[12] = 0; // append 0
    strcpy(this->vendor, vendor);

    // if maxCalls is greater than 1, check supported features
    if(maxCalls < 1)
    {
        steppingNumber = modelNumber = familyNumber = processorType = 0;
        extModelNumber = extFamilyNumber = 0;
        mmxFlag = sseFlag = sse2Flag = amd3dnowFlag = amd3dnow2Flag = false;
        return;
    }

    __asm {
        // call cpuid once again with eax=1
        mov     eax,    1h
        cpuid

        // get results into local vars
        mov     regEax,   eax
        mov     regEdx,   edx
    }

    // get stepping number eax:0~3
    steppingNumber = regEax & 0xF;

    // get model number eax:4~7, eax:16~19
    modelNumber = (regEax >> 4) & 0xF;
    extModelNumber = (regEax >> 16) & 0xF;

    // get family number eax:8~11, eax:20~27
    familyNumber = (regEax >> 8) & 0xF;
    extFamilyNumber = (regEax >> 20) & 0xFF;

    // get processor type
    processorType = (regEax >> 12) & 0x3;

    // check TSC (Time Stemp Counter)
    tscFlag = (regEdx >> 4) & 0x1;

    //check MMX support
    mmxFlag = (regEdx >> 23) & 0x1;

    sseFlag = (regEdx >> 25) & 0x1;

    sse2Flag = (regEdx >> 26) & 0x1;

    // extended CPUID call for AMD cpu
    if(strcmp(vendor, "AuthenticAMD") == 0)
    {
        __asm {
            // call cpuid once again with eax=1
            mov     eax,    80000001h
            cpuid

            // get results into local vars
            mov     regEax,   eax
            mov     regEdx,   edx
        }

        // check MMX support
        mmxFlag = (regEdx >> 23) & 0x1;

        // check 3DNow support
        amd3dnowFlag = (regEdx >> 30) & 0x1;

        // check 3DNow2 support
        amd3dnow2Flag = (regEdx >> 31) & 0x1;
    }
    else
    {
        amd3dnowFlag = amd3dnow2Flag = false;
    }
}
