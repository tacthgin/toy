#include "Sort.h"
#include <iostream>
#include <iterator>

using namespace std;

Sort::Sort(std::initializer_list<int> list)
:_numbers(list)
{

}

Sort::~Sort()
{
}

void Sort::sort()
{
	cout << "empty sort" << endl;
}

void Sort::setNumbers(const std::vector<int>& numbers)
{
	_numbers = numbers;
}

void Sort::print(const std::string & title /* = "" */)
{
	cout << title.c_str() << endl;
	copy(_numbers.begin(), _numbers.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
}
