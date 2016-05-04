#include<iostream>
#include"Heap.h"
#include"HuffmanTree.h"
#include"FileCompress.h"
#include"FileUncompress.h"
#include<windows.h>

using namespace std;

void testHuffmanHeap()
{
	int array[] = { 1, 5, 8, 2, 4, 3, 2, 8 };
	HuffmanTree<int> h1;
	//h1(array, 7, 0);
	h1.PrevOrder();
}
void testFilecompress()
{
	int begin1 = GetTickCount();
	FileCompress f1;
	f1.Compress("abc.txt");
	int end1 = GetTickCount();
	cout << "压缩时间:" << end1 - begin1 << endl;
}
void testFileUncompress()
{
	int begin1 = GetTickCount();
	FileUncompress f2;
	f2.Uncompress("abc.config");
	int end1 = GetTickCount();
	cout << "解压时间:" << end1 - begin1 << endl;
}

int main()
{
	//testHuffmanHeap();
	testFilecompress();
	testFileUncompress();
	return 0;
}