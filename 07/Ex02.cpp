#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"

int raiseToPower(int n, int k);

int main()
{
	std::cout << raiseToPower(10, 3) << std::endl;
}

int raiseToPower(int n, int k)
{
	if (k == 0)return 1;

	return n * raiseToPower(n, k - 1);
}

