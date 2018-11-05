///////////////////////////////////////////////////////////////////////////////
// test SSE movaps and movups intruction
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2005-11-26
// UPDATED: 2005-12-20
///////////////////////////////////////////////////////////////////////////////

#include "Timer.h"
#include "CpuInfo.h"
#include <iostream>
#include <cstring>
using std::cout;
using std::endl;

void moveSSE(float* dst, const float* src, int size);
void moveASM(float* dst, const float* src, int size);


int main()
{
    // check if SSE & MMX is supported by CPU
    CpuInfo cpu;
    if(!cpu.isSupportedSSE())
    {
        cout << "ERROR: SSE is not supported." << endl;
        return 0;
    }
    if(!cpu.isSupportedMMX())
    {
        cout << "ERROR: MMX is not supported." << endl;
        return 0;
    }

    // align array with 16-byte (128-bit) boundary for SSE instructions
    __declspec(align(16)) float a[4000] ={1,2,3,4, 5,6,7,8};
    __declspec(align(16)) float b[4000];
    int i;
    Timer t;



    // aligned move ///////////////////////////////////////////////////////////
    // memory must be aligned 16-byte boundary
    // use __declspec(align(#)) in MSVC
    __asm {
        movaps      xmm0,  [a]
        movaps      [b],    xmm0
    }
    cout << "Aligned Move: " << b[0] << ", " << b[1] << ", " << b[2] << ", " << b[3] << endl;
    cout << endl;



    // arithmetic /////////////////////////////////////////////////////////////
    __asm {
        movaps      xmm0,   [a]     // x = 1,2,3,4
        movaps      xmm1,   [a+16]  // y = 5,6,7,8

        // copy xmm1 to other registers
        movaps      xmm2,   xmm1    // y
        movaps      xmm3,   xmm1    // y
        movaps      xmm4,   xmm1    // y
        movaps      xmm5,   xmm1    // y
        movaps      xmm6,   xmm1    // y
        movaps      xmm7,   xmm1    // y

        // arithmetic
        addps       xmm1,   xmm0
        subps       xmm2,   xmm0
        mulps       xmm3,   xmm0
        divps       xmm4,   xmm0
        rcpps       xmm5,   xmm0
        sqrtps      xmm6,   xmm0
        rsqrtps     xmm7,   xmm0

        // output
        movaps      [b],    xmm1
        movaps      [b+16], xmm2
        movaps      [b+32], xmm3
        movaps      [b+48], xmm4
        movaps      [b+64], xmm5
        movaps      [b+80], xmm6
        movaps      [b+96], xmm7
    }
    cout << "Add: " << b[0] << ", " << b[1] << ", " << b[2] << ", " << b[3] << endl;
    cout << "Sub: " << b[4] << ", " << b[5] << ", " << b[6] << ", " << b[7] << endl;
    cout << "Mul: " << b[8] << ", " << b[9] << ", " << b[10] << ", " << b[11] << endl;
    cout << "Div: " << b[12] << ", " << b[13] << ", " << b[14] << ", " << b[15] << endl;
    cout << "Rcp: " << b[16] << ", " << b[17] << ", " << b[18] << ", " << b[19] << endl;
    cout << "Sqrt: " << b[20] << ", " << b[21] << ", " << b[22] << ", " << b[23] << endl;
    cout << "Rsqrt: " << b[24] << ", " << b[25] << ", " << b[26] << ", " << b[27] << endl;
    cout << endl;



    // shuffle ////////////////////////////////////////////////////////////////
    __asm {
        movaps      xmm0,   [a]     // 1,2,3,4
        movaps      xmm1,   xmm0    // copy
        movaps      xmm2,   xmm0    // copy
        movaps      xmm3,   xmm0    // copy
        movaps      xmm4,   xmm0    // copy
        movaps      xmm5,   xmm0    // copy
        movaps      xmm6,   xmm0    // copy

        // broadcast
        shufps      xmm0,   xmm0,   00h     // 1st
        shufps      xmm1,   xmm1,   55h     // 2nd
        shufps      xmm2,   xmm2,   0AAh    // 3rd
        shufps      xmm3,   xmm3,   0FFh    // 4th

        // swap
        shufps      xmm4,   xmm4,   0x1B    // swap

        // rotate
        shufps      xmm5,   xmm5,   0x93    // <-- 
        shufps      xmm6,   xmm6,   0x39    // -->

        movaps      [b],    xmm0
        movaps      [b+16], xmm1
        movaps      [b+32], xmm2
        movaps      [b+48], xmm3
        movaps      [b+64], xmm4
        movaps      [b+80], xmm5
        movaps      [b+96], xmm6
    }
    cout << "Broadcast 1st: " << b[0] << ", " << b[1] << ", " << b[2] << ", " << b[3] << endl;
    cout << "Broadcast 2nd: " << b[4] << ", " << b[5] << ", " << b[6] << ", " << b[7] << endl;
    cout << "Broadcast 3rd: " << b[8] << ", " << b[9] << ", " << b[10] << ", " << b[11] << endl;
    cout << "Broadcast 4th: " << b[12] << ", " << b[13] << ", " << b[14] << ", " << b[15] << endl;
    cout << "Swap: " << b[16] << ", " << b[17] << ", " << b[18] << ", " << b[19] << endl;
    cout << "Rotate Left: " << b[20] << ", " << b[21] << ", " << b[22] << ", " << b[23] << endl;
    cout << "Rotate Right: " << b[24] << ", " << b[25] << ", " << b[26] << ", " << b[27] << endl;
    cout << endl;



    // unpack /////////////////////////////////////////////////////////////////
    __asm {
        movaps      xmm0,   [a]
        movaps      xmm1,   [a+16]

        // unpack low 2 elements
        unpcklps    xmm0,   xmm1

        movaps      [b],    xmm0
    }
    cout << "Unpack: " << b[0] << ", " << b[1] << ", " << b[2] << ", " << b[3] << endl;
    cout << endl;



    // comparison /////////////////////////////////////////////////////////////
    __asm {
        movaps      xmm0,   [a]     // 1,2,3,4
        movaps      xmm1,   [a+16]  // 5,6,7,8

        // compare the lowest element
        cmpltss     xmm0,   xmm1    // less than

        movss       [b],    xmm0
    }
    cout << "Compare: " << (b[0] ? "true": "false") << endl;
    cout << endl;



    // absolute and negate ////////////////////////////////////////////////////
    unsigned int absBits = 0x7fffffff;
    unsigned int negBits = 0x80000000;
    a[0] = -1;                      // make negative number
    a[1] = 2;                       // make positive number
    __asm {
        movss       xmm0,   [a]     // hold negative number, a[0]
        movss       xmm1,   absBits // get bits (0111..1111b)
        andps       xmm0,   xmm1    // set the most significant bit to 0
        movss       [b],    xmm0    // b[0]

        // negating
        movss       xmm0,   [a+4]   // a[1]
        movss       xmm1,   negBits // 1000..0000b
        xorps       xmm0,   xmm1
        movss       [b+4],  xmm0    // b[1]
    }
    cout << "Absolute: " << b[0] << endl;
    cout << "Negate: " << b[1] << endl;
    cout << endl;



    // convert to integer /////////////////////////////////////////////////////
    a[0] = 1.5f;
    __asm {
        movss       xmm0,   [a]     // float number
        cvtss2si    eax,    xmm0    // convert to rounded integer
        mov         i,      eax
    }
    cout << "Conversion: " << i << endl;
    cout << endl;



    // prefetch memory ///////////////////////////////////////////////////////
    // Note that the current CPUs (AthlonXP, Pentium$ or higher) include automatic
    // cache prefetching in hardware. calling prefetch* instruction in software
    // may slow down performance.
    // In my measurement, without prefeching is faster than with prefetching.

    // init input array
    for(i=0; i < 4000; ++i)
        a[i] = b[i] = i;

    // without prefetch
    t.start();
    __asm {
        // loop 1000 times
        mov         ecx,    1000
        xor         esi,    esi

    loop1:
        // get data
        movaps      xmm0,   [a + esi]
        movaps      xmm1,   xmm0

        // multiply 4 elements at once
        // and copy results back to array
        mulps       xmm0,   xmm1
        movaps      [a + esi], xmm0

        // next index
        add         esi,    16
        dec         ecx
        jnz         loop1
    }
    t.stop();
    cout << "Without Prefetch: " << t.getElapsedTimeInMicroSec() << " us\n";

    // with prefetch
    t.start();
    __asm {
        // loop 1000 times
        mov         ecx,    1000
        xor         esi,    esi

    loop2:
        // prefetch next data
        prefetchnta [b + esi + 32]

        // get data
        movaps      xmm0,   [b + esi]
        movaps      xmm1,   xmm0

        // multiply 4 elements at once
        // and copy results to array
        mulps       xmm0,   xmm1
        movaps      [b + esi], xmm0

        // next index
        add         esi,    16
        dec         ecx
        jnz         loop2
    }
    t.stop();
    cout << "With Prefetch: " << t.getElapsedTimeInMicroSec() << " us\n";
    cout <<endl;



    ///////////////////////////////////////////////////////////////////////////
    // comparison of speed of memory copy (memcpy, moveASM, moveSSE)

    // copy data with standard C lib
    t.start();
    memcpy(b, a, 4000*sizeof(float));
    t.stop();
    cout << "Std Move Elapsed time: " << t.getElapsedTimeInMicroSec() << " us\n";

    // copy data with inline assembly
    t.start();
    moveASM(b, a, 4000);
    t.stop();
    cout << "ASM Move Elapsed time: " << t.getElapsedTimeInMicroSec() << " us\n";

    // copy data with SSE instructions
    t.start();
    moveSSE(b, a, 4000);
    t.stop();
    cout << "SSE Move Elapsed time: " << t.getElapsedTimeInMicroSec() << " us\n";

    return 0;
}



///////////////////////////////////////////////////////////////////////////////
// src and dst must aligned 4-byte (128-bit) boundary, and the number of data
// also must be divisible by 4. (copy 4 data at once)
///////////////////////////////////////////////////////////////////////////////
void moveSSE(float* dst, const float* src, int size)
{
    int count = size >> 2;          // loop count

    __asm {
        mov     ecx,    count       // # of 16-byte blocks
        mov     edi,    dst         // dst pointer
        mov     esi,    src         // src pointer

    loop1:
        movaps  xmm0,   [esi]       // source
        movaps  [edi],  xmm0        // destination
        //movntps [edi],  xmm0        // Why is it slower than movaps?

        add     esi,    16
        add     edi,    16

        dec     ecx                 // next
        jnz     loop1
    }
}



///////////////////////////////////////////////////////////////////////////////
// inline assembly version of memory copy
void moveASM(float* dst, const float* src, int count)
{
    int bytes = sizeof(float) * count;

    __asm {
        mov     ecx,    bytes       // total # of bytes
        shr     ecx,    2           // convert to # of quad (4-byte, dword)

        cld                         // clear direction flag
        mov     esi,    src         // src pointer
        mov     edi,    dst         // dst pointer
        rep     movsd               // copy dword at a time
    }
}
