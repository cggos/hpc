#pragma once //prevent repeated references


#include <cstdlib>
#include <cstdio>
#include "FreeImage.h"

class gFreeImage
{
public:
	gFreeImage(void);
	~gFreeImage(void);
public:
    FIBITMAP *bitmap;
	unsigned char *imageData;
	unsigned char *imageData4;
	FREE_IMAGE_FORMAT imagetype;
	int width;
	int height;

	int LoadImage(char *filename);
	int LoadImageGrey(char *filename); //×°Èë»Ò¶ÈÍ¼
	int SaveImage(char *filename);
	int SaveImageGrey(char *filename);
    unsigned char * getImageData(int& w, int& h);
	unsigned char * getImageDataGrey(int& w, int& h);
};
