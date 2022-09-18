#include <iostream>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"

//	パスカルの三角形を使用したコンビネーション
int c(int n, int k);

int main()
{
	for (int i = 0; i <= 7; ++i)
	{
		for (int j = 0; j <= i; ++j)
		{
			std::cout << c(i, j) << " ";
		}
		std::cout << std::endl;
	}
}

int c(int n, int k)
{
	if (n == k || k == 0)return 1;

	return c(n - 1, k - 1) + c(n - 1, k);
}

