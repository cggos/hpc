///////////////////////////////////////////////////////////////////////////////
// CpuInfo.h
// =========
// Retrieve CPU information by cpuid
//
//  AUTHOR: Song Ho Ahn
// CREATED: 2005-11-18
// UPDATED: 2005-12-21
///////////////////////////////////////////////////////////////////////////////

#ifndef CPUINFO_H
#define CPUINFO_H

class CpuInfo
{
public: //=====================================================================
    //ctor/dtor
    CpuInfo();
    ~CpuInfo();

    // member functions
    void printSelf() const;                     // print all CPU info
    const char* getVendor() const;              // get cpu vendor string

    // tell cpu features
    bool isSupportedMMX() const { return mmxFlag; };
    bool isSupportedSSE() const { return sseFlag; };
    bool isSupportedSSE2() const { return sse2Flag; };
    bool isSupported3DNow() const { return amd3dnowFlag; };
    bool isSupported3DNow2() const { return amd3dnow2Flag; };


private: //====================================================================
    void getInfo();         // get cpu info using CPUID

    char vendor[13];        // 12 bytes + null char
    int steppingNumber;     // eax:0~3
    int modelNumber;        // eax:4~7
    int familyNumber;       // eax:8~11
    int processorType;      // eax:12~13
    int extModelNumber;     // eax:16~19
    int extFamilyNumber;    // eax:20~27

    bool tscFlag;           // edx:4
    bool mmxFlag;           // edx:23
    bool sseFlag;           // edx:25
    bool sse2Flag;          // edx:26
    bool amd3dnowFlag;      // edx:30
    bool amd3dnow2Flag;     // edx:31
};

#endif
