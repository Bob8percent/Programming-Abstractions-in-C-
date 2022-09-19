#include <iostream>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"
#include "Library/set.h"

bool subsetSumExists(const Set<int>& set, int target, int& count);
bool _subsetSumExists(const Set<int>& set, int target, int& count);


int main()
{
	Set<int> s;
	s += -2, 1, 3, 8;
	int count = 0;
	std::cout << std::boolalpha << _subsetSumExists(s, 7, count) << std::endl;
	std::cout << count << std::endl;
	count = 0;
	std::cout << std::boolalpha << subsetSumExists(s, 7, count) << std::endl;
	std::cout << count << std::endl;
}

bool subsetSumExists(const Set<int>& set, int target, int& count)
{
	++count;
	if (target == 0)return true;
	else if (set.isEmpty()) return false;

	Set<int> temp = set;
	while (!temp.isEmpty())
	{
		int val = temp.first();
		temp.remove(val);
		Set<int> newSet = temp;
		if (subsetSumExists(newSet, target - val, count))
		{
			return true;
		}
	}

	return false;
}

bool _subsetSumExists(const Set<int>& set, int target, int& count)
{
	++count;
	if (set.isEmpty())
	{
		return target == 0;
	}

	else
	{
		int val = set.first();
		Set<int> temp = set - val;
		return (_subsetSumExists(temp, target, count)) || (_subsetSumExists(temp, target - val, count));
	}
}

