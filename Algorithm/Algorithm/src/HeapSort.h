#pragma once
#include "Sort.h"

class HeapSort :public Sort
{
public:
	using Sort::Sort;
	HeapSort();
	virtual ~HeapSort();

	virtual void sort();
private:
	int parent(int i) { return (i + 1) / 2 - 1; } //如果起始值是1，是i/2 left是2i right是2i+1
	int left(int i) { return 2 * i + 1; }
	int right(int i) { return 2 * (i + 1); }
	void maxHeapify(int i);
	void buildMaxHeap();
	int _heapSize = {0};
};

