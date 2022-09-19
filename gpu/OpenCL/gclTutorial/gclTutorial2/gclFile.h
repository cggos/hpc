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

    //��opencl kernelԴ�ļ�(�ı�ģʽ)
    bool open(const char* fileName);
    //��д������kernel�ļ�
    bool writeBinaryToFile(const char* fileName, const char* birary, size_t numBytes);
    bool readBinaryFromFile(const char* fileName);

    //�ÿո����س����з�
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

	 //����Դ��string
    const std::string&  source() const { return source_; }

private:
    //��ֹcopy����
    gclFile(const gclFile&);

    //��ֹ��ֵ����
    gclFile& operator=(const gclFile&);

    std::string     source_;    //Դ�������
};
