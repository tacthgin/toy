#pragma once
#include <vector>

class Sort
{
public:
	Sort() {}
	Sort(std::initializer_list<int> list);
	virtual ~Sort() = 0;
	virtual void sort();
	void setNumbers(const std::vector<int>& numbers);
	void print(const std::string& title = "");
protected:
	std::vector<int> _numbers;
};

