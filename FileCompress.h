#pragma once
#include"HuffmanTree.h"
//#define _DEBUG_

#pragma warning(disable:4996)


class Charinfo
{
public:
	Charinfo(unsigned char ch = 0)
		:_ch(ch)
		, _count(0)
		, _code("")
	{}
	bool operator< (const Charinfo& tmp)const
	{
		return _count < tmp._count;
	}
	bool operator> (const Charinfo& tmp)const
	{
		return _count > tmp._count;
	}
	bool operator!= (const Charinfo& tmp) const
	{
		return (_count != tmp._count);
	}
	Charinfo operator+ (const Charinfo& var)
	{
		Charinfo tmp;
		tmp._count = _count + var._count;
		return tmp;
	}

//private:
	string _code;
	int _count;
	unsigned char _ch;
};


class FileCompress
{
public:
	FileCompress()
	{
		for (int i = 0; i < 256; i++)
		{
			_chinfos[i]._ch = unsigned char(i);
		}
	}

	void Compress(string filename)
	{
		assert(filename.c_str());
		FILE* fOut = fopen(filename.c_str(), "rb");
		assert(fOut);
		
		//Step1 统计每个字符出现的个数
		char ch = fgetc(fOut);
		while (!feof(fOut))
		{
			_chinfos[(unsigned char)ch]._count++;
			ch = fgetc(fOut);
		}
		

		//Step2 建立Huffman树
		Charinfo invaild;
		HuffmanTree<Charinfo> h(_chinfos, 256, invaild);
		
		//Step3 获取每个字符（至少出现一次的）的Huffman编码
		HuffmanTreeNode<Charinfo>* root = h.GetRoot();
		string code = "";
		_GetHuffmanCode(root, code);

		//Step4 写入压缩文件
		filename.erase(filename.length() - 4, 4);
		string filenameout = filename + ".compress";
		
		FILE* fIn = fopen(filenameout.c_str(), "wb");
		assert(fIn);
		fseek(fOut, 0, SEEK_SET);

		ch = fgetc(fOut);
		unsigned char inCh = 0;
		int index = 0; //写入配置文件
		while (ch != EOF)
		{
			string& code = _chinfos[unsigned char(ch)]._code;
			for (int i = 0; i < code.size(); i++)
			{
				inCh <<= 1;
				if (code[i] == '1')
					inCh |= 1;
				
				index++;

				if(index == 8)
				{
					fputc(inCh, fIn);
#ifdef _DEBUG_
					printf("%x", inCh);
#endif
					inCh = 0;
					index = 0;
				}
			}
			ch = fgetc(fOut);
		}
		if (index != 0)
		{
			inCh <<= 8 - index;
#ifdef _DEBUG_
			printf("%x", inCh);
#endif
			fputc(inCh, fIn);
		}
		

		//Step5 写入配置文件
		string filenamein = filename + ".config";
		FILE* fInconfig = fopen(filenamein.c_str(), "wb");
		assert(fInconfig);
		for (int i = 0; i < 256; i++)
		{
			string chInfo;
			if (_chinfos[i]._count)
			{
				char buffer[128];
				chInfo += _chinfos[i]._ch;
				chInfo += ',';
				chInfo += itoa(_chinfos[i]._count, buffer, 10);
				chInfo += '\n';
				fputs(chInfo.c_str(), fInconfig);
			}
		}
		root = h.GetRoot();
		size_t charcount = root->_weight._count;
		char buffer[128];
		fputs(itoa(charcount, buffer, 10), fInconfig);
		fputc('\n', fInconfig);
		fclose(fInconfig);
		fclose(fIn);
		fclose(fOut);
	}
private:
	 void _GetHuffmanCode(HuffmanTreeNode<Charinfo>* root, string& code) 
	{
		if (!root->_left && !root->_right)
		{
			_chinfos[root->_weight._ch]._code = code;
			code.erase(code.length()-1,1);
			return;
		}
		if (root->_left)
		{
			code += '0';
			_GetHuffmanCode(root->_left, code);
		}
		if (root->_right)
		{
			code += '1';
			_GetHuffmanCode(root->_right, code);
		}
		if (code.size()>0)
			code.erase(code.length() - 1, 1);
	}
private:
	Charinfo _chinfos[256];
};