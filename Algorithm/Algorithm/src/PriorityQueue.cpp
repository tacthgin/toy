#include "PriorityQueue.h"
#include <cassert>
#include <algorithm>
#include <string>

using namespace std;

MaximumPriorityQueue::MaximumPriorityQueue()
{
}

MaximumPriorityQueue::~MaximumPriorityQueue()
{
}

void MaximumPriorityQueue::insert(int key)
{
	_heapSize = _heapSize + 1;
	_numbers.push_back(INT_MIN);
	increaseKey(_numbers.size() - 1, key);
	print("MaximumPriorityQueue insert key:"  + std::to_string(key));
}

int MaximumPriorityQueue::maximum()
{
	assert(_numbers.size() != 0);
	return _numbers[0];
}

int MaximumPriorityQueue::extractMax()
{
	assert(_numbers.size() > 0);
	int max = _numbers[0];
	swap(_numbers[0], _numbers[_numbers.size() - 1]);
	_heapSize = _heapSize - 1;
	_numbers.erase(_numbers.end() - 1);
	maxHeapify(0);
	return max;
}

void MaximumPriorityQueue::increaseKey(int index, int key)
{
	assert(_numbers[index] < key);
	_numbers[index] = key;
	while (index >= 0  && parent(index) >= 0 && _numbers[parent(index)] < _numbers[index])
	{
		swap(_numbers[parent(index)], _numbers[index]);
		index = parent(index);
	}
}

void MaximumPriorityQueue::maxHeapify(int i)
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



MinimumPriorityQueue::MinimumPriorityQueue()
{
}

MinimumPriorityQueue::~MinimumPriorityQueue()
{
}

void MinimumPriorityQueue::insert(int element)
{
}

int MinimumPriorityQueue::minimum()
{
	return 0;
}

void MinimumPriorityQueue::extractMin()
{
}

void MinimumPriorityQueue::decreaseKey(int element, int key)
{
}
