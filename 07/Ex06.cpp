#include <iostream>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"


//	再帰の方法によって計算回数が異なることを確認する
int calcFib1(int n, int& count);
int calcFib2(int n, int a0, int a1, int& count);

int main()
{
	std::cout << std::setw(3) << "n" << std::setw(7) << "fib1" << std::setw(7) << "fib2" << std::endl;
	std::cout << std::setw(3) << "--" << std::setw(7) << "----" << std::setw(7) << "----" << std::endl;
	for (int i = 0; i < 20; ++i)
	{
		std::cout << std::setw(3) << i;
		int c1 = 0, c2 = 0;
		calcFib1(i, c1);
		calcFib2(i, 0, 1, c2);
		std::cout << std::setw(7) << c1;
		std::cout << std::setw(7) << c2 << std::endl;
	}
}

int calcFib1(int n, int& count)
{
	++count;
	if (n <= 1)return n;

	return calcFib1(n - 1, count) + calcFib1(n - 2, count);
}

int calcFib2(int n, int a0, int a1, int& count)
{
	++count;
	if (n == 0)return a0;
	if (n == 1)return a1;
	
	return calcFib2(--n, a1, a0 + a1, count);
}
