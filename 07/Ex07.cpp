#include <iostream>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"

//	各桁の合計を計算する
int digitSum(int num);

int main()
{
	std::cout << digitSum(1729) << std::endl;
}

int digitSum(int num)
{
	if (num <= 0)return 0;

	int d = num % 10;
	int nextNum = num / 10;
	return d + digitSum(nextNum);
}

