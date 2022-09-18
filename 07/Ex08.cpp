#include <iostream>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"

int digitSum(int num);
int digitalRoot(int num);

int main()
{
	std::cout << digitalRoot(1723) << std::endl;
}

int digitSum(int num)
{
	if (num <= 0)return 0;

	int d = num % 10;
	int nextNum = num / 10;
	return d + digitSum(nextNum);
}

int digitalRoot(int num)
{
	if (num < 10)return num;

	return digitalRoot(digitSum(num));
}

