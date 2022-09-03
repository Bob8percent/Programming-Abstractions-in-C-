
/*
* 年の各月の日数を表示するプログラム
*/

#include <iostream>
#include <iomanip>
#include "calender.h"

int main()
{
	const int sentinel = -1;

	while (1)
	{
		int year = -1;
		std::cout << "入力：";
		std::cin >> year;

		if (year == sentinel)
		{
			break;
		}

		for (int month = 1; month <= 12; ++month)
		{
			Month m = Month(month);
			std::cout << monthToString(m) << "は" << daysInMonth(year, m) << "日です\n";
		}
	}
}
