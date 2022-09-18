#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"

int findInVector(const Vector<std::string>& vec, const std::string& key);
int binarySearch(const Vector<std::string>& vec, const std::string& key, int start, int end);

int main()
{
	Vector<std::string> vec;
	vec += "aaa", "bbb", "ccc", "ddd", "eee";

	std::cout << findInVector(vec, "ebc") << std::endl;
}

int findInVector(const Vector<std::string>& vec, const std::string& key)
{
	return binarySearch(vec, key, 0, vec.size() - 1);
}

int binarySearch(const Vector<std::string>& vec, const std::string& key, int start, int end)
{
	if (start > end)
	{
		return -1;
	}

	int mid = (start + end) / 2;
	if (key == vec[mid])return mid;
	if (key > vec[mid])
	{
		return binarySearch(vec, key, mid + 1, end);
	}
	else
	{
		return binarySearch(vec, key, start, mid - 1);
	}
}
