#include<iostream>
#include"Heap.h"
#include"HuffmanTree.h"
#include"FileCompress.h"
#include"FileUncompress.h"

using namespace std;

void testHuffmanHeap()
{
	int array[] = { 1, 5, 8, 2, 4, 3, 2, 8 };
	HuffmanTree<int> h1(array, 8);
	h1.PrevOrder();
}
void testFilecompress()
{
	FileCompress f1;
	f1.Compress("abc.txt");
}
void testFileUncompress()
{
	FileUncompress f2;
	f2.Uncompress("abc.config");
}

int main()
{
	//testHuffmanHeap();
	testFilecompress();
	testFileUncompress();
	return 0;
}