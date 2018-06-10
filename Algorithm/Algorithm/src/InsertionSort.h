#pragma once
#include "Sort.h"

class InsertionSort : public Sort
{
public:
	using Sort::Sort;
	InsertionSort();
	virtual ~InsertionSort();
	virtual void sort();
};

