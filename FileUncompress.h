#pragma once
#include"FileCompress.h"

class FileUncompress
{
public:
	FileUncompress(const string& filename)
	{
		//Step1 读取配置文件，重建huffman树
		FILE* fIn = fopen(filename.c_str(), "r");
		assert(fIn);
		
		while (ch != EOF)
		{
			if ()
			_chinfos[unsigned char(ch)]
			ch 
		}
	}
private:
	Charinfo _chinfos[256];
};