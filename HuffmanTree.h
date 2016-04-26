#pragma once
#include<iostream>
#include<assert.h>
#include"Heap.h"
using namespace std;


template<class T>
struct HuffmanTreeNode
{
	HuffmanTreeNode<T>* _left;
	HuffmanTreeNode<T>* _right;
	HuffmanTreeNode<T>* _parent;
	T _weight;

	HuffmanTreeNode(const T& weight)
		:_left(NULL)
		, _right(NULL)
		, _weight(weight)
		, _parent(NULL)
	{}
};


template<class T>
struct HuffmanLess
{
	bool operator() (const HuffmanTreeNode<T>* l, HuffmanTreeNode<T>* r)
	{
		return l->_weight < r->_weight; 
	}
};

template<class T>
class HuffmanTree
{
	typedef HuffmanTreeNode<T> Node;
public:
	HuffmanTree()
		:_root(NULL)
	{}
	HuffmanTree(const T* array, int size, const T& invalid)
	{
		assert(array);
		assert(size != 0);
		Heap<Node*, HuffmanLess<T>> minHeap;

		for (int i = 0; i < size; i++)
		{
			if (array[i] != invalid)
			{
				Node* newnode = new Node(array[i]);
				minHeap.Push(newnode);
			}	
		}
		if (size == 1)
		{
			_root = minHeap.Top();
			minHeap.Pop();
		}
		//int size1 = minHeap.Size();
		while (minHeap.Size() > 1)
		{
			Node* left = minHeap.Top();
			minHeap.Pop();
			Node* right = minHeap.Top();
			minHeap.Pop();

			Node* parent = new Node(left->_weight + right->_weight);
			parent->_left = left;
			parent->_right = right;
			left->_parent = parent;
			right->_parent = parent;
			_root = parent;
			minHeap.Push(parent);
		}
	}

	~HuffmanTree()
	{}
	
	Node* GetRoot()
	{
		return _root;
	}
		
	void PrevOrder()
	{
		_PrevOrder(_root);
	}

private:
	HuffmanTreeNode<T>* _root;
private:
	void _PrevOrder(Node* root)
	{
		if (!root)
		{
			return;
		}
		cout << root->_weight << " ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}
	
};