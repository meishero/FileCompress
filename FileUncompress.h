#pragma once
#include"FileCompress.h"

class FileUncompress
{
public:
	FileUncompress()
	{
		for (int i = 0; i < 256; i++)
		{
			_chinfos[i]._ch = unsigned char(i);
		}
	}
	bool Uncompress(string filename)
	{
		//Step1 读取配置文件，重建huffman树
		FILE* fIn = fopen(filename.c_str(), "rb");
		assert(fIn);

		/*while (ch != EOF||ch!=)
		{
		if ()
		_chinfos[unsigned char(ch)]
		ch
		}*/

		string line;
		//_GetLine(fIn, line);
		//if (!_GetLine(fIn, line))//对于本身就是空的文件 先进行处理
		{
		}
		size_t charcount = 0;
		while (_GetLine(fIn, line))
		{
			if (line[1] != ',')
				charcount = atoi(line.c_str());
			else
			{
				unsigned char ch = unsigned char(line[0]);
				_chinfos[ch]._count = atoi(line.substr(2).c_str());
				line.clear();
			}	
		}
		fclose(fIn);
		Charinfo invaild;
		HuffmanTree<Charinfo> ht(_chinfos, 256, invaild);
		HuffmanTreeNode<Charinfo>* root = ht.GetRoot();

		//Step2 解压缩
		filename.erase(filename.length() - 7, 7);
		filename = filename + ".compress";
		FILE* filenameout = fopen(filename.c_str(), "rb");
		assert(filenameout);

		filename.erase(filename.length() - 10, 10);
		filename = filename + ".txt";
		FILE* filenamein = fopen(filename.c_str(), "wb");
		assert(filenamein);

		HuffmanTreeNode<Charinfo>* cur = root;
		int index = 8;
		char ch = fgetc(filenameout);
		size_t count = 0;
		while (!feof(filenameout))
		{
			--index;
			if (ch & (1 << index))
				cur = cur->_right;
			else
				cur = cur->_left;
			if (!cur->_left && !cur->_right)
			{
				fputc(cur->_weight._ch, filenamein);
				count++;
				if (count == charcount)
					break;
				cur = root;
			}
			if (index == 0)
			{
				ch = fgetc(filenameout);
				index = 8;
			}
		}
		fclose(filenamein);
		fclose(filenameout);
		return true;
	}
private:
	bool _GetLine(FILE*& fIn, string& line)
	{
		char ch = fgetc(fIn);
		if (ch == EOF)
		{
			return false;
		}
		if (ch == '\n')
		{
			line += '\n';
			ch = fgetc(fIn);
		}
		while (ch != '\n')
		{
			line += ch;
			ch = fgetc(fIn);
		}
		return true;
	}
private:
	Charinfo _chinfos[256];
};