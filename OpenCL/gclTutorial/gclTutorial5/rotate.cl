#pragma OPENCL EXTENSION cl_amd_printf : enable
__kernel  void image_rotate(	__global uchar * src_data, __global uchar * dest_data,	//源图像和输出图像都放在global memory中
	                                            int W,    int H,								//图像size
	                                           float sinTheta, float cosTheta )					//旋转角度
{    
	const int ix = get_global_id(0); 
	const int iy = get_global_id(1);    

    int xc = W/2;
    int yc = H/2;

	int xpos =  ( ix-xc)*cosTheta - (iy-yc)*sinTheta+xc;    
	int ypos =  (ix-xc)*sinTheta + ( iy-yc)*cosTheta+yc; 

   	if ((xpos>=0) && (xpos< W)	&& (ypos>=0) && (ypos< H))	//边界检测
	{
		dest_data[ypos*W+xpos]= src_data[iy*W+ix]; 
	 }
}

