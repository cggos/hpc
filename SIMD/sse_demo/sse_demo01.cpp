#include <emmintrin.h>
#include <cmath>
#include <zconf.h>

#include "timer.h"

void normal(float* a, int N)
{
    for (int i = 0; i < N; ++i)
        a[i] = std::sqrt(a[i]);
}

void sse(float* a, int N)
{
    // We assume N % 4 == 0.
    int nb_iters = N / 4;
    __m128* ptr = (__m128*)a;

    for (int i = 0; i < nb_iters; ++i, ++ptr, a += 4)
        _mm_store_ps(a, _mm_sqrt_ps(*ptr));
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;
    int N = atoi(argv[1]);

    //    float a[] __attribute__ ((aligned (16))) = { 41982.,  81.5091, 3.14, 42.666 };
    float *a;
    posix_memalign((void**)&a, 16,  N * sizeof(float));

    for (int i = 0; i < N; ++i)
        a[i] = (float)3141592.65358;

    {
        TIMER("normal");
        normal(a, N);
    }

    for (int i = 0; i < N; ++i)
        a[i] = 3141592.65358;

    {
        TIMER("SSE");
        sse(a, N);
    }

    {
        TIMER("sleep");
        usleep(2);
    }

    return 0;
}
