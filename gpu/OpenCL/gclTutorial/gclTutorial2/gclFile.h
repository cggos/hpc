#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <malloc.h>

class gclFile
{
public:
	gclFile(void);
	~gclFile(void);

    //打开opencl kernel源文件(文本模式)
    bool open(const char* fileName);
    //读写二进制kernel文件
    bool writeBinaryToFile(const char* fileName, const char* birary, size_t numBytes);
    bool readBinaryFromFile(const char* fileName);

    //用空格代替回车换行符
    void replaceNewlineWithSpaces()
    {
        size_t pos = source_.find_first_of('\n', 0);
        while(pos != -1)
        {
            source_.replace(pos, 1, " ");
            pos = source_.find_first_of('\n', pos + 1);
        }
        pos = source_.find_first_of('\r', 0);
        while(pos != -1)
        {
            source_.replace(pos, 1, " ");
            pos = source_.find_first_of('\r', pos + 1);
        }
    }

	 //返回源码string
    const std::string&  source() const { return source_; }

private:
    //禁止copy函数
    gclFile(const gclFile&);

    //禁止赋值操作
    gclFile& operator=(const gclFile&);

    std::string     source_;    //源程序代码
};
