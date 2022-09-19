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

//�ȴ��¼����
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


//CPU��תͼ��
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

	//װ��ͼ��,
	unsigned char *src_image=0;
	unsigned char *cpu_image=0;
	int W, H;
	gFreeImage img;
	if(!img.LoadImageGrey("../lenna.jpg"))
		{
		printf("can��t load lenna.jpg\n");
		exit(0);
		}
	else
		src_image = img.getImageDataGrey(W, H);

	size_t mem_size = W*H;
	cpu_image = (unsigned char*)malloc(mem_size);


	gclTimer clTimer;
	clTimer.Reset();

	//����driver dump il��isa�ļ�
	_putenv("GPU_DUMP_DEVICE_KERNEL=3");

	cl_uint status;
	cl_platform_id platform;

	//����ƽ̨����
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

	//����GPU�豸
	clGetDeviceIDs( platform, CL_DEVICE_TYPE_GPU,
		1,
		&device,
		NULL);
	//����context
	cl_context context = clCreateContext( NULL,
		1,
		&device,
		NULL, NULL, NULL);
	//�����������
	cl_command_queue queue = clCreateCommandQueue( context,
		device,
		CL_QUEUE_PROFILING_ENABLE, NULL );
	//����2��OpenCL�ڴ����
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
	//�ȴ����ݴ�������ټ�������ִ��
	status = clFlush(queue);
	waitForEventAndRelease(&writeEvt);
	//clWaitForEvents(1, &writeEvt);

	//kernel�ļ�Ϊrotate.cl
	gclFile kernelFile;
	if(!kernelFile.open("rotate.cl"))
		{
		printf("Failed to load kernel file \n");
		exit(0);
		}
	const char * source = kernelFile.source().c_str();
	size_t sourceSize[] = {strlen(source)};
	//�����������
	cl_program program = clCreateProgramWithSource(
		context, 
		1, 
		&source,
		sourceSize,
		NULL);
	//����������
	status = clBuildProgram( program, 1, &device, NULL, NULL, NULL );
	if(status != 0)
		{
		printf("clBuild failed:%d\n", status);
		char tbuf[0x10000];
		clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0x10000, tbuf, NULL);
		printf("\n%s\n", tbuf);
		return -1;
		}

	//����Kernel����
	cl_kernel kernel = clCreateKernel( program, "image_rotate", NULL );
	//����Kernel����
	float sintheta = 1, costheta = 0;
	clSetKernelArg(kernel, 0, sizeof(cl_mem),  (void *)&d_ip); 
	clSetKernelArg(kernel, 1, sizeof(cl_mem),  (void *)&d_op);
	clSetKernelArg(kernel, 2, sizeof(cl_int),  (void *)&W);
	clSetKernelArg(kernel, 3, sizeof(cl_int),  (void *)&H);
	clSetKernelArg(kernel, 4, sizeof(cl_float), (void *)&sintheta);
	clSetKernelArg(kernel, 5, sizeof(cl_float), (void *)&costheta);


	//ִ��kernel,Range��2ά��work itmes sizeΪW*H
	cl_event ev;
	size_t globalThreads[] = {W, H};
	size_t localThreads[] = {16, 16}; // localx*localyӦ����64�ı��� 
	printf("global_work_size =(%d,%d), local_work_size=(16, 16)\n",W,H);

	clTimer.Reset();
	clTimer.Start();
	clEnqueueNDRangeKernel( queue,
		kernel,
		2,
		NULL,
		globalThreads,
		localThreads, 0, NULL, &ev);
	//û������local group sizeʱ��ϵͳ�����Զ�����Ϊ (256,1)
	status = clFlush( queue );
	waitForEventAndRelease(&ev);
	//clWaitForEvents(1, &ev);

	clTimer.Stop();
	printf("kernal total time:%.6f ms \n ", clTimer.GetElapsedTime()*1000 );

	//����kerenlִ��ʱ��
	cl_ulong startTime, endTime;
	clGetEventProfilingInfo(ev, CL_PROFILING_COMMAND_START, 
		sizeof(cl_ulong), &startTime, NULL);
	clGetEventProfilingInfo(ev,  CL_PROFILING_COMMAND_END,
		sizeof(cl_ulong), &endTime, NULL);
	cl_ulong kernelExecTimeNs = endTime-startTime;
	printf("kernal exec time :%8.6f ms\n ", kernelExecTimeNs*1e-6 );

	//���ݿ���host�ڴ�
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

	//ɾ��OpenCL��Դ����
	clReleaseMemObject(d_ip); 
	clReleaseMemObject(d_op);
	clReleaseProgram(program);
	clReleaseCommandQueue(queue);
	clReleaseContext(context);
	return 0;
	}

