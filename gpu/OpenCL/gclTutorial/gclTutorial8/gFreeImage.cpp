#include "gFreeImage.h"

gFreeImage::gFreeImage(void)
	{
	FreeImage_Initialise(FALSE);

	bitmap = NULL;
	imageData = NULL;
	imageData4 = NULL;

	width = 0;
	height = 0;

	}

gFreeImage::~gFreeImage(void)
	{
	if(bitmap)
		FreeImage_Unload(bitmap);

	if(imageData4!=NULL)
		free(imageData4);

	FreeImage_DeInitialise();

	}

int gFreeImage::LoadImage(char *filename)
	{

	imagetype = FIF_UNKNOWN;

	imagetype = FreeImage_GetFileType(filename,0);

	// 设法根据图片文件类型猜测图像格式
	if(imagetype == FIF_UNKNOWN)
		imagetype = FreeImage_GetFIFFromFilename(filename);


	if(imagetype == FIF_UNKNOWN)
		{
		printf("unknow image format\n");
		return 0;
		}
	// 检测是否FreeImage是否支持该文件格式
	if((imagetype != FIF_UNKNOWN) && FreeImage_FIFSupportsReading(imagetype)) 
		{
		bitmap = FreeImage_Load(imagetype,filename,0);

		if(!bitmap)
			{
			printf("can't load image\n");
			return 0;
			}
		}
	else
		{
		printf("format can't be supported.\n");
		return 0;
		}


	bitmap = FreeImage_ConvertTo24Bits(bitmap);
	//bitmap = FreeImage_ConvertTo32Bits(bitmap);
	//use 24bit format, for 32bits can't support jpg format, so I will change to 32bit manually

	//FreeImage_Save(imagetype, bitmap, "x3.jpg", 0);
	imageData = (unsigned char *)FreeImage_GetBits(bitmap);
	width = FreeImage_GetWidth(bitmap);
	height = FreeImage_GetHeight(bitmap);
	int pitch = FreeImage_GetPitch(bitmap);


	printf("load image succeed. width:%d, height:%d\n", width, height);

	imageData4 = (unsigned char*)malloc(width*height*4*sizeof(unsigned char));

	int i, j;
	long t;

	t = width*height*3;
	i = j = 0;
	while(i < t)
		{
		if(i%3==0 && i>0)
			{
			imageData4[i+j] = 1;
			j++;
			imageData4[i+j] = imageData[i];
			}
		else
			{
			imageData4[i+j] = imageData[i];
			}
		i++;

		}


	//note that it's BRG mode at default
	//for(i = 0; i < 24; i++)
	//{

	//	printf("%d, %d\n", i, imageData[i]);
	//}    
	//for(i = 0; i < 24; i++)
	//{

	//	printf("%d, %d\n", i, imageData4[i]);
	//} 
	return 1;
	}

int gFreeImage::LoadImageGrey(char *filename)
	{

	imagetype = FIF_UNKNOWN;

	imagetype = FreeImage_GetFileType(filename,0);

	// try to guess the file format from the file extension
	if(imagetype == FIF_UNKNOWN)
		imagetype = FreeImage_GetFIFFromFilename(filename);


	if(imagetype == FIF_UNKNOWN)
		{
		printf("unknow image format\n");
		return 0;
		}
	// check that the plugin has reading capabilities ...
	if((imagetype != FIF_UNKNOWN) && FreeImage_FIFSupportsReading(imagetype)) 
		{
		bitmap = FreeImage_Load(imagetype,filename,0);

		if(!bitmap)
			{
			printf("can't load image\n");
			return 0;
			}
		}
	else
		{
		printf("format can't be supported.\n");
		return 0;
		}



	//8bits is grey bitmap.grey = (0.2126 x R + 0.7152 * G + 0.0722 x B) 
	bitmap = FreeImage_ConvertTo8Bits(bitmap);


	//FreeImage_Save(imagetype, bitmap, "x3.jpg", 0);
	imageData = (unsigned char *)FreeImage_GetBits(bitmap);
	width = FreeImage_GetWidth(bitmap);
	height = FreeImage_GetHeight(bitmap);
	int pitch = FreeImage_GetPitch(bitmap);


	printf("load image succeed. width:%d, height:%d\n", width, height);

	return 1;
	}


int gFreeImage::SaveImage(char *filename)
	{

	if(imageData4!=NULL)
		{
		int i, j;
		long t;

		t = width*height*4;
		i = j  = 0;
		while(i < t)
			{
			if((i+1)%4 ==0 && i>0)
				{

				}
			else
				{
				imageData[j] = imageData4[i];
				j++;
				}
			i++;
			}
		}


	if(bitmap)
		{
		FreeImage_Save(imagetype, bitmap, filename, 0);
		return 1;
		}


	return 0;
	}

int gFreeImage::SaveImageGrey(char *filename)
	{

	if(bitmap)
		{
		FreeImage_Save(imagetype, bitmap, filename, 0);
		return 1;
		}


	return 0;
	}

unsigned char* gFreeImage::getImageData(int& w, int& h)
	{
	w = width;
	h = height;

	return imageData4;
	}

unsigned char* gFreeImage::getImageDataGrey(int& w, int& h)
	{
	w = width;
	h = height;

	return imageData;
	}