#include "QuickSort.h"
#include <algorithm>
#include <cassert>
#include <random>

using namespace std;

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

void QuickSort::randomSort()
{
	print("QuickSort randomSort front:");
	randomQuickSort(_numbers, 0, _numbers.size() - 1);
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

int QuickSort::randomPartition(std::vector<int>& numbers, int begin, int end)
{
	random_device r;
	default_random_engine el(r());
	uniform_int_distribution<int> dist(begin, end);
	int index = dist(el);
	if (index != begin)
	{
		swap(numbers[begin], numbers[index]);
	}
	return partition(numbers, begin, end);
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

void QuickSort::randomQuickSort(std::vector<int>& numbers, int begin, int end)
{
	if (begin < end)
	{
		int r = randomPartition(numbers, begin, end);
		randomQuickSort(numbers, begin, r - 1);
		randomQuickSort(numbers, r + 1, end);
	}
}
