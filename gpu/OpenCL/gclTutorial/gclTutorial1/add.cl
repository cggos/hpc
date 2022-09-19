
__kernel void vecadd(__global const float* A, __global const float* B, __global float* C)
{
    int id = get_global_id(0);
    C[id] = A[id] + B[id];
}
