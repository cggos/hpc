#pragma OPENCL EXTENSION cl_amd_printf : enable

__kernel void vecadd(__global const float* a, __global const float* b, __global float* c)
{
	int x = get_global_id(0);
	int y = get_global_id(1);
	int width = get_global_size(0);
	int height = get_global_size(1);
	//if(x == 1 && y ==1)
	//     printf("%d, %d,%d,%d,%d,%d\n",get_local_size(0),get_local_size(1),get_local_id(0),get_local_id(1),get_group_id(0),get_group_id(1));
	
	c[x + y * width] = a[x + y * width] + b[x + y * width];
	
}



