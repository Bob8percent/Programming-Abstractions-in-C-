#define _USE_MATH_DEFINES

#include <iostream>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cmath>
#include <string>
#include <SFML/Graphics.hpp>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"
#include "Library/set.h"

//  O(logN)のraiseToPower
double raiseToPower(double x, int n, int& count);

int main()
{
	int count = 0;
	std::cout << raiseToPower(4.2, 5, count) << std::endl;
	std::cout << count << std::endl << std::endl;
	count = 0;
	std::cout << raiseToPower(4.2, 10, count) << std::endl;
	std::cout << count << std::endl << std::endl;
	count = 0;
	std::cout << raiseToPower(4.2, 20, count) << std::endl;
	std::cout << count << std::endl << std::endl;
	count = 0;
	std::cout << raiseToPower(4.2, 100, count) << std::endl;
	std::cout << count << std::endl << std::endl;
}

double raiseToPower(double x, int n, int& count)
{
	++count;
	if (n == 0)return 1;
	else if (n == 1)return x;

	int a = n / 2;
	int b = n - a;
	double result = raiseToPower(x, a, count);
	if (b > a)
	{
		//	b=a+1のとき
		return result * result * x;
	}
	else
	{
		return result * result;
	}
}

