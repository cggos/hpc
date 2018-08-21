/*
	SSE_Tutorial
	This tutorial was written for supercomputingblog.com
	This tutorial may be freely redistributed provided this header remains intact
*/


#include <xmmintrin.h>	// Need this for SSE compiler intrinsics
#include <math.h>		// Needed for sqrt in CPU-only version
#include <stdio.h>
#include <malloc.h>

int main(int argc, char* argv[])
{
    printf("Starting calculation...\n");

    const int length = 64000;

    // We will be calculating Y = Sin(x) / x, for x = 1->64000

    // If you do not properly align your data for SSE instructions, you may take a huge performance hit.

    float *pResult = (float*) _mm_malloc(length * sizeof(float), 16);	// align to 16-byte for SSE

    __m128 x;
    __m128 xDelta = _mm_set1_ps(4.0f);		// Set the xDelta to (4,4,4,4)
    __m128 *pResultSSE = (__m128*) pResult;


    const int SSELength = length / 4;

    for (int stress = 0; stress < 100000; stress++)	// lots of stress loops so we can easily use a stopwatch

    {
#define TIME_SSE	// Define this if you want to run with SSE

#ifdef TIME_SSE
        x = _mm_set_ps(4.0f, 3.0f, 2.0f, 1.0f);	// Set the initial values of x to (4,3,2,1)

        for (int i=0; i < SSELength; i++)
        {

            __m128 xSqrt = _mm_sqrt_ps(x);
            // Note! Division is slow. It's actually faster to take the reciprocal of a number and multiply
            // Also note that Division is more accurate than taking the reciprocal and multiplying

#define USE_DIVISION_METHOD

#ifdef USE_FAST_METHOD
            __m128 xRecip = _mm_rcp_ps(x);

            pResultSSE[i] = _mm_mul_ps(xRecip, xSqrt);
#endif //USE_FAST_METHOD

#ifdef USE_DIVISION_METHOD
            pResultSSE[i] = _mm_div_ps(xSqrt, x);

#endif	// USE_DIVISION_METHOD

            // NOTE! Sometimes, the order in which things are done in SSE may seem reversed.
            // When the command above executes, the four floating elements are actually flipped around
            // We have already compensated for that flipping by setting the initial x vector to (4,3,2,1) instead of (1,2,3,4)

            x = _mm_add_ps(x, xDelta);	// Advance x to the next set of numbers

        }
#endif	// TIME_SSE

#ifndef TIME_SSE
        float xFloat = 1.0f;
		for (int i=0 ; i < length; i++)
		{

			pResult[i] = sqrt(xFloat) / xFloat;	// Even though division is slow, there are no intrinsic functions like there are in SSE
			xFloat += 1.0f;
		}

#endif	// !TIME_SSE
    }

    // To prove that the program actually worked
    for (int i=0; i < 20; i++)
    {
        printf("Result[%d] = %f\n", i, pResult[i]);
    }

    // Results for my particular system
    // 23.75 seconds for SSE with reciprocal/multiplication method
    // 38.5 seconds for SSE with division method
    // 301.5 seconds for CPU


    return 0;
}