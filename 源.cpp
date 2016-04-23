#include<iostream>
#include"Heap.h"
#include"HuffmanTree.h"
#include"FileCompress.h"

using namespace std;

void testHuffmanHeap()
{
	int array[] = { 1, 5, 8, 2, 4, 3, 2, 8 };
	HuffmanTree<int> h1(array, 8);
	h1.PrevOrder();
}
void testFilecompressStep12()
{
	FileCompress f1;
	f1.Compress("abc.txt");
}

int main()
{
	//testHuffmanHeap();
	testFilecompressStep12();


	return 0;
}