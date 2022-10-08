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
#include "Library/random.h"
#include "Library/map.h"
#include "Library/set.h"
#include <ctime>

//	漸化式の解から導いた近似式から求める
int fib(int n, int& count);
//  分割統治法によるO(logN)のraiseToPower
double raiseToPower(double x, int n, int& count);

int main()
{
	int count = 0;
	std::cout << fib(5, count) << std::endl;
	std::cout << count << std::endl << std::endl;
	count = 0;
	std::cout << fib(6, count) << std::endl;
	std::cout << count << std::endl << std::endl;
	count = 0;
	std::cout << fib(7, count) << std::endl;
	std::cout << count << std::endl << std::endl;
	count = 0;
	std::cout << fib(8, count) << std::endl;
	std::cout << count << std::endl << std::endl;
}

int fib(int n, int& count) {
	const double phai = (std::sqrt(5) + 1) / 2;
	int result = int(raiseToPower(phai, n, count) / std::sqrt(5) + 0.5);
	return result;
}

//	x^2n=x^n*x^nへの分割ごとに一回の計算で実現しO(logN)を実現
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
