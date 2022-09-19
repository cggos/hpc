#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include "gclFile.h"
#include "gclTimer.h"
#include "gFreeImage.h"

using namespace std;

#pragma comment (lib,"OpenCL.lib")
#pragma comment(lib,"FreeImage.lib")

//等待事件完成
int waitForEventAndRelease(cl_event *event)
	{
	cl_int status = CL_SUCCESS;
	cl_int eventStatus = CL_QUEUED;
	while(eventStatus != CL_COMPLETE)
		{
		status = clGetEventInfo(
			*event, 
			CL_EVENT_COMMAND_EXECUTION_STATUS, 
			sizeof(cl_int),
			&eventStatus,
			NULL);
		}

	status = clReleaseEvent(*event);

	return 0;
	}


//CPU旋转图像
void cpu_rotate(unsigned char* inbuf, unsigned char* outbuf, int w, int h,float sinTheta, float cosTheta)
	{
	int i, j;
	int xc = w/2;
	int yc = h/2;

	for(i = 0; i < h; i++)
		{
		for(j=0; j< w; j++)
			{
			int xpos =  ( j-xc)*cosTheta - (i-yc)*sinTheta+xc;    
			int ypos =  (j-xc)*sinTheta + ( i-yc)*cosTheta+yc; 

			if(xpos>=0&&ypos>=0&&xpos<w&&ypos<h)
				outbuf[ypos*w + xpos] = inbuf[i*w+j];
			}
		}
	}

int main(int argc, char* argv[])
	{

	//装入图像,
	unsigned char *src_image=0;
	unsigned char *cpu_image=0;
	int W, H;
	gFreeImage img;
	if(!img.LoadImageGrey("../lenna.jpg"))
		{
		printf("can‘t load lenna.jpg\n");
		exit(0);
		}
	else
		src_image = img.getImageDataGrey(W, H);

	size_t mem_size = W*H;
	cpu_image = (unsigned char*)malloc(mem_size);


	gclTimer clTimer;
	clTimer.Reset();

	//告诉driver dump il和isa文件
	_putenv("GPU_DUMP_DEVICE_KERNEL=3");

	cl_uint status;
	cl_platform_id platform;

	//创建平台对象
	//status = clGetPlatformIDs( 1, &platform, NULL );
	cl_uint numPlatforms;
	std::string platformVendor; 
	status = clGetPlatformIDs(0, NULL, &numPlatforms);
	if(status != CL_SUCCESS)
		{
		return 0;
		}
	if (0 < numPlatforms) 
		{
		cl_platform_id* platforms = new cl_platform_id[numPlatforms];
		status = clGetPlatformIDs(numPlatforms, platforms, NULL);

		char platformName[100];
		for (unsigned i = 0; i < numPlatforms; ++i) 
			{
			status = clGetPlatformInfo(platforms[i],
				CL_PLATFORM_VENDOR,
				sizeof(platformName),
				platformName,
				NULL);

			platform = platforms[i];
			platformVendor.assign(platformName);

			if (!strcmp(platformName, "Advanced Micro Devices, Inc.")) 
				{
				break;
				}
			}

		std::cout << "Platform found : " << platformName << "\n";
		delete[] platforms;
		}
	cl_device_id device;

	//创建GPU设备
	clGetDeviceIDs( platform, CL_DEVICE_TYPE_GPU,
		1,
		&device,
		NULL);
	//创建context
	cl_context context = clCreateContext( NULL,
		1,
		&device,
		NULL, NULL, NULL);
	//创建命令队列
	cl_command_queue queue = clCreateCommandQueue( context,
		device,
		CL_QUEUE_PROFILING_ENABLE, NULL );
	//创建2个OpenCL内存对象
	cl_mem d_ip = clCreateBuffer(
		context, CL_MEM_READ_ONLY,
		mem_size, 
		NULL, NULL);
	cl_mem d_op = clCreateBuffer(
		context, CL_MEM_WRITE_ONLY,
		mem_size, 
		NULL, NULL);
	
	cl_event writeEvt;
	status = clEnqueueWriteBuffer (	
		queue , d_ip, CL_TRUE,
		0, mem_size, (void *)src_image,
		0, NULL, &writeEvt);
	//等待数据传输完成再继续往下执行
	status = clFlush(queue);
	waitForEventAndRelease(&writeEvt);
	//clWaitForEvents(1, &writeEvt);

	//kernel文件为rotate.cl
	gclFile kernelFile;
	if(!kernelFile.open("rotate.cl"))
		{
		printf("Failed to load kernel file \n");
		exit(0);
		}
	const char * source = kernelFile.source().c_str();
	size_t sourceSize[] = {strlen(source)};
	//创建程序对象
	cl_program program = clCreateProgramWithSource(
		context, 
		1, 
		&source,
		sourceSize,
		NULL);
	//编译程序对象
	status = clBuildProgram( program, 1, &device, NULL, NULL, NULL );
	if(status != 0)
		{
		printf("clBuild failed:%d\n", status);
		char tbuf[0x10000];
		clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0x10000, tbuf, NULL);
		printf("\n%s\n", tbuf);
		return -1;
		}

	//创建Kernel对象
	cl_kernel kernel = clCreateKernel( program, "image_rotate", NULL );
	//设置Kernel参数
	float sintheta = 1, costheta = 0;
	clSetKernelArg(kernel, 0, sizeof(cl_mem),  (void *)&d_ip); 
	clSetKernelArg(kernel, 1, sizeof(cl_mem),  (void *)&d_op);
	clSetKernelArg(kernel, 2, sizeof(cl_int),  (void *)&W);
	clSetKernelArg(kernel, 3, sizeof(cl_int),  (void *)&H);
	clSetKernelArg(kernel, 4, sizeof(cl_float), (void *)&sintheta);
	clSetKernelArg(kernel, 5, sizeof(cl_float), (void *)&costheta);


	//执行kernel,Range用2维，work itmes size为W*H
	cl_event ev;
	size_t globalThreads[] = {W, H};
	size_t localThreads[] = {16, 16}; // localx*localy应该是64的倍数 
	printf("global_work_size =(%d,%d), local_work_size=(16, 16)\n",W,H);

	clTimer.Reset();
	clTimer.Start();
	clEnqueueNDRangeKernel( queue,
		kernel,
		2,
		NULL,
		globalThreads,
		localThreads, 0, NULL, &ev);
	//没有设置local group size时候，系统将会自动设置为 (256,1)
	status = clFlush( queue );
	waitForEventAndRelease(&ev);
	//clWaitForEvents(1, &ev);

	clTimer.Stop();
	printf("kernal total time:%.6f ms \n ", clTimer.GetElapsedTime()*1000 );

	//计算kerenl执行时间
	cl_ulong startTime, endTime;
	clGetEventProfilingInfo(ev, CL_PROFILING_COMMAND_START, 
		sizeof(cl_ulong), &startTime, NULL);
	clGetEventProfilingInfo(ev,  CL_PROFILING_COMMAND_END,
		sizeof(cl_ulong), &endTime, NULL);
	cl_ulong kernelExecTimeNs = endTime-startTime;
	printf("kernal exec time :%8.6f ms\n ", kernelExecTimeNs*1e-6 );

	//数据拷回host内存
	// copy results from device back to host
	unsigned char *op_data=0;
	//op_data =(unsigned char *)malloc(mem_size);
	//   status = clEnqueueReadBuffer(
	//queue, d_op, 
	//CL_TRUE,		//Blocking Read Back
	//0, mem_size,(void*)op_data, NULL, NULL, NULL);
	cl_event mapevt;
	op_data = (cl_uchar *) clEnqueueMapBuffer( queue,
		d_op,
		CL_TRUE,
		CL_MAP_READ,
		0, 
		mem_size,
		0, NULL, &mapevt, NULL );
	status = clFlush( queue );
	waitForEventAndRelease(&mapevt);
	//clWaitForEvents(1, &mapevt);

	int i;
	clTimer.Reset();
	clTimer.Start();
	cpu_rotate(src_image,cpu_image, W, H, 1, 0);
	clTimer.Stop();
	printf("cpu rotate time:%.6f ms \n ", clTimer.GetElapsedTime()*1000 );
	for(i = 0; i < mem_size; i++)
		{
		src_image[i] =cpu_image[i];
		}	
	img.SaveImage("../cpu_lenna_rotate.jpg");
	for(i = 0; i < mem_size; i++)
		{
		src_image[i] =op_data[i];
		}	
	img.SaveImage("../lenna_rotate.jpg");

	if(cpu_image)
		free(cpu_image);

	//删除OpenCL资源对象
	clReleaseMemObject(d_ip); 
	clReleaseMemObject(d_op);
	clReleaseProgram(program);
	clReleaseCommandQueue(queue);
	clReleaseContext(context);
	return 0;
	}

