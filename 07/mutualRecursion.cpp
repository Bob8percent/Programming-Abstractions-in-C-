#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"

bool isOdd(int num);
bool isEven(int num);

int main()
{
	std::cout << isOdd(4) << std::endl;
}

bool isOdd(int num)
{
	return !isEven(num);
}

bool isEven(int num)
{
	if (num == 0)return true;

	if (isOdd(--num))return true;
}


