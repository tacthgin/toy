#include "InsertionSort.h"

InsertionSort::InsertionSort()
{
}


InsertionSort::~InsertionSort()
{
}

void InsertionSort::sort()
{
	print("InsertionSort front:");
	int key = 0;
	int j = 0;
	for (int i = 1; i < _numbers.size(); i++)
	{
		key = _numbers[i];
		j = i - 1;
		while (j >= 0 && _numbers[j] > key)
		{
			_numbers[j + 1] = _numbers[j];
			_numbers[j] = key;
			j--;
		}
		
	}
	print("back:");
}
