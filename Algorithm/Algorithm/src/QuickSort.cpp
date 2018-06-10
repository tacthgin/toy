#include "QuickSort.h"
#include <algorithm>
#include <cassert>

QuickSort::QuickSort()
{

}

QuickSort::~QuickSort()
{

}

void QuickSort::sort()
{
	print("QuickSort front:");
	quickSort(_numbers, 0, _numbers.size() - 1);
	print("back:");
}

int QuickSort::partition(std::vector<int>& numbers, int begin, int end)
{
	assert(numbers.size() > 1);
	int pivot = numbers[begin];
	int i = begin;
	for (int j = i + 1; j <= end; ++j)
	{
		if (numbers[j] <= pivot)
		{
			i = i + 1;
			std::swap(numbers[i], numbers[j]);
		}
	}
	std::swap(numbers[begin], numbers[i]);
	return i;
}

void QuickSort::quickSort(std::vector<int>& numbers, int begin, int end)
{
	if (begin < end)
	{
		int r = partition(numbers, begin, end);
		quickSort(numbers, begin, r - 1);
		quickSort(numbers, r + 1, end);
	}
}
