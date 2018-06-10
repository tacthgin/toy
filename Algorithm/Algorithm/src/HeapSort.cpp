#include "HeapSort.h"
#include <algorithm>
#include <string>

using namespace std;

HeapSort::HeapSort()
{
}

HeapSort::~HeapSort()
{
}

void HeapSort::sort()
{
	print("HeapSort Max Heap Front:");
	buildMaxHeap();
	for (int i = _numbers.size() - 1; i >= 1; i--)
	{
		swap(_numbers[0], _numbers[i]);
		_heapSize = _heapSize - 1;
		maxHeapify(0);
	}
	print("Back:");
}

void HeapSort::maxHeapify(int i)
{
	int largest = 0;
	int l = left(i);
	if (l >= 0 && l < _heapSize && _numbers[l] > _numbers[i])
		largest = l;
	else
		largest = i;

	int r = right(i);
	if (r >= 0 && r < _heapSize && _numbers[r] > _numbers[largest])
		largest = r;

	if (largest != i)
	{
		swap(_numbers[largest], _numbers[i]);
		maxHeapify(largest);
	}
}

//保证根节点都是最大
void HeapSort::buildMaxHeap()
{
	_heapSize = _numbers.size();
	for (int i = _heapSize / 2 - 1; i >= 0; i--)
	{
		maxHeapify(i);
	}
}
