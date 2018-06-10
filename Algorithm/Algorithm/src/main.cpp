#include <iostream>
#include "InsertionSort.h"
#include "QuickSort.h"
#include "HeapSort.h"

using namespace std;

int main()
{
	InsertionSort insertionSort({ -2, -5, 2, 8, 9, 4, 4, 5, 3, 6 });
	insertionSort.sort();
	insertionSort.setNumbers({ 5, 8, 3, 2, 6 });
	insertionSort.sort();

	QuickSort quickSort({ -2, -5, 2, 8, 9, 4, 4, 5, 3, 6 });
	quickSort.sort();

	HeapSort heapSort({ -2, -5, 2, 8, 9, 4, 4, 5, 3, 6 });
	heapSort.sort();

	getchar();
	return 0;
}