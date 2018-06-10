#pragma once

#include "Sort.h"

class QuickSort : public Sort
{
public:
	using Sort::Sort;
	QuickSort();
	virtual ~QuickSort();
	
	virtual void sort();
private:
	int partition(std::vector<int>& numbers, int begin, int end);
	void quickSort(std::vector<int>& numbers, int begin, int end);
};

