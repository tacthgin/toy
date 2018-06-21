#include <iostream>
#include "InsertionSort.h"
#include "QuickSort.h"
#include "HeapSort.h"
#include "PriorityQueue.h"

using namespace std;

int main()
{
	InsertionSort insertionSort({ -2, -5, 2, 8, 9, 4, 4, 5, 3, 6 });
	insertionSort.sort();
	insertionSort.setNumbers({ 5, 8, 3, 2, 6 });
	insertionSort.sort();

	QuickSort quickSort({ -2, -5, 2, 8, 9, 4, 4, 5, 3, 6 });
	quickSort.sort();

	QuickSort randomQuickSort({ -2, -5, 2, 8, 9, 4, 4, 5, 3, 6 });
	randomQuickSort.randomSort();

	HeapSort heapSort({ -2, -5, 2, 8, 9, 4, 4, 5, 3, 6 });
	heapSort.sort();

	MaximumPriorityQueue maxpq({1});
	maxpq.insert(5);
	maxpq.insert(8);
	maxpq.insert(15);
	maxpq.insert(6);
	maxpq.insert(-2);

	getchar();
	return 0;
}