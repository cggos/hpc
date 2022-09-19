#include <CL/cl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>

using namespace std;
#define BUFSIZE 262144

#pragma comment (lib,"OpenCL.lib")

//���ı��ļ�����һ��string��,��������kernelԴ�ļ�
int convertToString(const char *filename, std::string& s)
	{
	size_t size;
	char*  str;

	std::fstream f(filename, (std::fstream::in | std::fstream::binary));

	if(f.is_open())
		{
		size_t fileSize;
		f.seekg(0, std::fstream::end);
		size = fileSize = (size_t)f.tellg();
		f.seekg(0, std::fstream::beg);

		str = new char[size+1];
		if(!str)
			{
			f.close();
			return NULL;
			}

		f.read(str, fileSize);
		f.close();
		str[size] = '\0';

		s = str;
		delete[] str;
		return 0;
		}
	printf("Error: Failed to open file %s\n", filename);
	return 1;
	}

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
int main(int argc, char* argv[])
	{
	//��host�ڴ��д�������������
	float *buf1 = 0;
	float *buf2 = 0;
	float *buf = 0;

	buf1 =(float *)malloc(BUFSIZE * sizeof(float));
	buf2 =(float *)malloc(BUFSIZE * sizeof(float));
	buf =(float *)malloc(BUFSIZE * sizeof(float));

	//��һЩ���ֵ��ʼ��buf1��buf2������
	int i;
	srand( (unsigned)time( NULL ) ); 
	for(i = 0; i < BUFSIZE; i++)
		buf1[i] = rand()%65535;

	srand( (unsigned)time( NULL ) +1000);
	for(i = 0; i < BUFSIZE; i++)
		buf2[i] = rand()%65535;

	//cpu����buf1,buf2�ĺ�
	for(i = 0; i < BUFSIZE; i++)
		buf[i] = buf1[i] + buf2[i];

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
	//��������OpenCL�ڴ���󣬲���buf1������ͨ����ʽ�����ķ�ʽ
	//������clbuf1,buf2������ͨ����ʾ�����ķ�ʽ������clbuf2
	cl_mem clbuf1 = clCreateBuffer(context,
		CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
		BUFSIZE*sizeof(cl_float),buf1,
		NULL );

	cl_mem clbuf2 = clCreateBuffer(context,
		CL_MEM_READ_ONLY ,
		BUFSIZE*sizeof(cl_float),NULL,
		NULL );

	cl_event writeEvt;
	status = clEnqueueWriteBuffer(queue, clbuf2, 1,
		0, BUFSIZE*sizeof(cl_float), buf2, 0, 0, &writeEvt);
	status = clFlush(queue);
	//�ȴ����ݴ�������ټ�������ִ��
	waitForEventAndRelease(&writeEvt);
	//clWaitForEvents(1, &writeEvt);

	cl_mem buffer = clCreateBuffer( context,
		CL_MEM_WRITE_ONLY,
		BUFSIZE * sizeof(cl_float),
		NULL, NULL );

	//kernel�ļ�Ϊadd.cl
	const char * filename  = "add.cl";
	std::string  sourceStr;
	status = convertToString(filename, sourceStr);
	const char * source    = sourceStr.c_str();
	size_t sourceSize[]    = { strlen(source) };

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
	cl_kernel kernel = clCreateKernel( program, "vecadd", NULL );
	//����Kernel����
	cl_int clnum = BUFSIZE;
	clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*) &clbuf1);
	clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*) &clbuf2);
	clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*) &buffer);

	//ִ��kernel,Range��1ά��work itmes sizeΪBUFSIZE,
	cl_event ev;
	size_t global_work_size = BUFSIZE;
	clEnqueueNDRangeKernel( queue,
		kernel,
		1,
		NULL,
		&global_work_size,
		NULL, 0, NULL, &ev);
	status = clFlush( queue );
	waitForEventAndRelease(&ev);
    //clWaitForEvents(1, &ev);

	//���ݿ���host�ڴ�
	cl_float *ptr;
	cl_event mapevt;
	ptr = (cl_float *) clEnqueueMapBuffer( queue,
		buffer,
		CL_TRUE,
		CL_MAP_READ,
		0,
		BUFSIZE * sizeof(cl_float),
		0, NULL, &mapevt, NULL );
	status = clFlush( queue );
	waitForEventAndRelease(&mapevt);
	//clWaitForEvents(1, &mapevt);

	//�����֤����cpu����Ľ���Ƚ�
	if(!memcmp(buf, ptr, BUFSIZE))
		printf("Verify passed\n");
	else printf("verify failed");

	if(buf)
		free(buf);
	if(buf1)
		free(buf1);
	if(buf2)
		free(buf2);

	//ɾ��OpenCL��Դ����
	clReleaseMemObject(clbuf1); 
	clReleaseMemObject(clbuf2);
	clReleaseMemObject(buffer);
	clReleaseProgram(program);
	clReleaseCommandQueue(queue);
	clReleaseContext(context);
	return 0;
	}

