#define LINEAR_MEM_ACCESS
#pragma OPENCL EXTENSION cl_khr_byte_addressable_store : enable 

#define BIN_SIZE 256

/**
 * 计算直方图,bins是256
 * data  输入数据
 * 一个workgroup内所有thread共享的内存，
 * 每个workgroup的直方图
 */

__kernel
void histogram256(__global const uchar4* data,
                  __local uchar* sharedArray,
                  __global uint* binResult)
{
    size_t localId = get_local_id(0);
    size_t globalId = get_global_id(0);
    size_t groupId = get_group_id(0);
    size_t groupSize = get_local_size(0);

    //初始化共享内存
    for(int i = 0; i < BIN_SIZE; ++i)
        sharedArray[localId * BIN_SIZE + i] = 0;

    barrier(CLK_LOCAL_MEM_FENCE);
    
	uchar R, G, B, A, T;
    //计算thread直方图
    for(int i = 0; i < BIN_SIZE; ++i)
    {
#ifdef LINEAR_MEM_ACCESS
	    R =  (uint)data[groupId * groupSize * BIN_SIZE + i * groupSize + localId].x;
		G =  (uint)data[groupId * groupSize * BIN_SIZE + i * groupSize + localId].y;
		B =  (uint)data[groupId * groupSize * BIN_SIZE + i * groupSize + localId].z;
		A =  (uint)data[groupId * groupSize * BIN_SIZE + i * groupSize + localId].w;
		uint value = (uint)max(max(R,G),max(B,A));
#else
        uint value = data[globalId * BIN_SIZE + i];
#endif // LINEAR_MEM_ACCESS
        sharedArray[localId * BIN_SIZE + value]++;
    }
    
    barrier(CLK_LOCAL_MEM_FENCE); 
    
   //合并workgroup中所有线程的直方图，产生workgroup直方图
    for(int i = 0; i < BIN_SIZE / groupSize; ++i)
    {
        uint binCount = 0;
        for(int j = 0; j < groupSize; ++j)
            binCount += sharedArray[j * BIN_SIZE + i * groupSize + localId];
            
        binResult[groupId * BIN_SIZE + i * groupSize + localId] = binCount;
    }
}