#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"

int fib(int n);

int main()
{
	for (int i = 0; i < 10; ++i)
	{
		std::cout << fib(i) << std::endl;
	}
}

int fib(int n)
{
	if (n <= 1)return n;

	int result = 0;
	int a = 0, b = 1;
	while (n-- >= 2)
	{
		result = a + b;
		a = b;
		b = result;
	}
	return result;
}
