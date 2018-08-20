#include "gclFile.h"

gclFile::gclFile(void):source_("")
{
}

gclFile::~gclFile(void)
{
}

bool gclFile::writeBinaryToFile(const char* fileName, const char* birary, size_t numBytes)
{
    FILE *output = NULL;
    output = fopen(fileName, "wb");
    if(output == NULL)
        return false;

    fwrite(birary, sizeof(char), numBytes, output);
    fclose(output);

    return true;
}


bool gclFile::readBinaryFromFile(const char* fileName)
{
    FILE * input = NULL;
    size_t size = 0;
    char* binary = NULL;

    input = fopen(fileName, "rb");
    if(input == NULL)
    {
        return false;
    }

    fseek(input, 0L, SEEK_END); 
    size = ftell(input);
	//指向文件起始位置
    rewind(input);
    binary = (char*)malloc(size);
    if(binary == NULL)
    {
        return false;
    }
    fread(binary, sizeof(char), size, input);
    fclose(input);
    source_.assign(binary, size);
    free(binary);

    return true;
}

bool gclFile::open(const char* fileName)   //!< file name
	{
	size_t      size;
	char*       str;

	//以流方式打开文件
	std::fstream f(fileName, (std::fstream::in | std::fstream::binary));

	// 检查是否打开了文件流
	if (f.is_open())
		{
		size_t  sizeFile;
		// 得到文件size
		f.seekg(0, std::fstream::end);
		size = sizeFile = (size_t)f.tellg();
		f.seekg(0, std::fstream::beg);

		str = new char[size + 1];
		if (!str)
			{
			f.close();
			return  false;
			}

		// 读文件
		f.read(str, sizeFile);
		f.close();
		str[size] = '\0';

		source_  = str;

		delete[] str;

		return true;
		}

	return false;
	}




