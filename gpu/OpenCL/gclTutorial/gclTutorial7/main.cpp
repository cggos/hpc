//迈克老狼 2012-10-19

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


cl_int binSize;            //bins的大小，对于灰度图，一般为256
cl_int groupSize;       //workgroup大小
cl_int subHistgCnt;   //把图像分块来求直方图，最后再合并求整幅图像的直方图
cl_uchar *data;            //图像数据
cl_int width;              //图像宽度
cl_int height;            //图像高度
cl_uint *hostBin;       //cpu计算得到的最终直方图结果
cl_uint *midDeviceBin;      //gpu计算子块的直方图结果，也是kernel输出的结果，合并到deviceBin中。
cl_uint *deviceBin;         //设备(gpu)产生的最终结果

cl_mem dataBuf;                 //图像device memory
cl_mem midDeviceBinBuf;         //子块直方图结果device memory，这个参数和上面一个参数是kernel的输入

//cpu求直方图
void cpu_histgo()
	{
	int i, j;
	for(i = 0; i < height; ++i)
		{
		for(j = 0; j < width; ++j)
			{
			//printf("data: %d\n", data[i * width + j] );
			hostBin[data[i * width + j]]++;
			//printf("hostbin %d=%d\n", data[i * width + j], hostBin[data[i * width + j]]);
			}
		}
	}

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

int main(int argc, char* argv[])
	{

	//装入图像,
	unsigned char *src_image=0;
	gFreeImage img;
	if(!img.LoadImageGrey("../lenna.jpg"))
		{
		printf("can‘t load lenna.jpg\n");
		exit(0);
		}
	src_image = img.getImageDataGrey(width,height);

	binSize = 256;
	groupSize = 128;
	subHistgCnt = (width *height)/(binSize * groupSize);

	//width是binSize的整数倍，height是groupsize的整数倍
	width = (width / binSize ? width / binSize: 1) * binSize;
	height = (height / groupSize ? height / groupSize: 1) * groupSize;

	// 分配内存
	data = (cl_uchar*)malloc(width * height * sizeof(cl_uchar));
	if(!data)
		{
		printf("分配内存失败\n");
			return 0;
		}
	memset(data, 0,width * height * sizeof(cl_uchar));
	 
	int i, j;
	//在kernel中直接用uchar
	for(i = 0; i < width * height; i++)
		{
		data[i] =  (cl_uchar)src_image[i]; 
		//printf("%d\n", data[i]);
		//printf("src= %d\n", src_image[i]);
		}

	hostBin = (cl_uint*)malloc(binSize * sizeof(cl_uint));
	if(!hostBin)
		{
		printf("分配内存失败\n");
			return 0;
		}

	memset(hostBin, 0, binSize * sizeof(cl_uint));

	midDeviceBin = (cl_uint*)malloc(binSize * subHistgCnt * sizeof(cl_uint));
	if(!midDeviceBin)
		{
		printf("分配内存失败\n");
			return 0;
		}

	memset(midDeviceBin, 0, binSize * subHistgCnt * sizeof(cl_uint));

	deviceBin = (cl_uint*)malloc(binSize * sizeof(cl_uint));
	if(!deviceBin)
		{
		printf("分配内存失败\n");
			return 0;
		}

	memset(deviceBin, 0, binSize * sizeof(cl_uint));

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
	dataBuf = clCreateBuffer(
		context, 
		CL_MEM_READ_ONLY,
		sizeof(cl_uchar) * width  * height,
		NULL, 
		0);

	//该对象存放每个block块的直方图结果
	midDeviceBinBuf = clCreateBuffer(
		context, 
		CL_MEM_WRITE_ONLY,
		sizeof(cl_uint) * binSize * subHistgCnt,
		NULL, 
		0);

	//把图像数据写到device memory中
	cl_event writeEvt;
	status = clEnqueueWriteBuffer(queue,
		dataBuf,
		CL_FALSE,
		0,
		width * height * sizeof(cl_uchar),
		data,
		0,
		NULL,
		&writeEvt);

	status = clFlush(queue);
	waitForEventAndRelease(&writeEvt);

	//kernel文件为histo.cl
	gclFile kernelFile;
	if(!kernelFile.open("histo.cl"))
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
	cl_kernel kernel = clCreateKernel( program, "histogram256", NULL );
	//设置Kernel参数
	status = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&dataBuf); 
	status = clSetKernelArg(kernel, 1, groupSize * binSize * sizeof(cl_uchar), NULL); //local memroy size, lds for amd
	status = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&midDeviceBinBuf); 

	//执行kernel,Range用2维，work itmes size为W*H
	cl_event ev;
	size_t globalThreads;
	size_t localThreads ;

	globalThreads = (width * height) / binSize ;
	localThreads = groupSize;
	printf("global_work_size =%d, local_work_size=%d\n", globalThreads, localThreads);

	clTimer.Reset();
	clTimer.Start();
	clEnqueueNDRangeKernel( queue,
		kernel,
		1,
		NULL,
		&globalThreads,
		&localThreads, 0, NULL, &ev);
	clFlush( queue );
	waitForEventAndRelease(&ev);

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
	cl_event readEvt;
	status = clEnqueueReadBuffer(
		queue, 
		midDeviceBinBuf, 
		CL_FALSE,
		0,
		subHistgCnt * binSize * sizeof(cl_uint),
		midDeviceBin,
		0,
		NULL,
		&readEvt);

	//status = clFlush(queue);
	//waitForEventAndRelease(&readEvt);
	clWaitForEvents(1, &readEvt);

	// 合并子块直方图值 
	
	for(i = 0; i < subHistgCnt; ++i)
		{
		for( j = 0; j < binSize; ++j)
			{
			deviceBin[j] += midDeviceBin[i * binSize + j];
			}
		}

	//cpu计算直方图
	clTimer.Reset();
	clTimer.Start();
	cpu_histgo();
	clTimer.Stop();
	printf("cpu get histo time:%.6f ms \n ", clTimer.GetElapsedTime()*1000 );

	bool result = true;
	for(i = 0; i < binSize; ++i)
		{
		//printf("host%d=%d, device%d=%d\n", i, hostBin[i], i, deviceBin[i]);
		if(hostBin[i] != deviceBin[i])
			{
			printf("host%d:%d, device%d:%d\n",i, hostBin[i], i, deviceBin[i]);
			result = false;
			break;
			}
		}

	if(result)
		{
		printf("passed\n");
		}
	else
		{
		printf("failed\n");
		}

	free(data);
	free(hostBin);
	free(midDeviceBin);
	free(deviceBin);
	//删除OpenCL资源对象
	clReleaseProgram(program);
	clReleaseCommandQueue(queue);
	clReleaseContext(context);
	return 0;
	}

