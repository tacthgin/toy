#pragma once
#include "Sort.h"

//最大优先级队列
class MaximumPriorityQueue : public Sort
{
public:
	using Sort::Sort;
	MaximumPriorityQueue();
	virtual ~MaximumPriorityQueue();
	void insert(int key);
	int maximum();
	int extractMax();
	void increaseKey(int index, int key);
private:
	int parent(int i) { return (i + 1) / 2 - 1; }
	int left(int i) { return 2 * i + 1; }
	int right(int i) { return 2 * (i + 1); }
	void maxHeapify(int i);
	int _heapSize = { 0 };
};

//最小优先级队列
class MinimumPriorityQueue : public Sort
{
public:
	MinimumPriorityQueue();
	virtual ~MinimumPriorityQueue();
	void insert(int element);
	int minimum();
	void extractMin();
	void decreaseKey(int element, int key);
};


