#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"

double getTitiusBodeDistance(int k);
int getDouble(int count, int n);

int main()
{
	for (int i = 1; i <= 8; ++i)
	{
		std::cout << getTitiusBodeDistance(i) << std::endl;
	}
}

double getTitiusBodeDistance(int k)
{
	if (k == 1)return 0.5;
	if (k <= 0)return -1;

	//	k >= 2
	return (4 + getDouble(k - 2, 3)) / 10.0;
}

int getDouble(int count, int n)
{
	if (count == 0)return n;
	if (count < 0)return -1;

	return 2 * getDouble(count - 1, n);
}

