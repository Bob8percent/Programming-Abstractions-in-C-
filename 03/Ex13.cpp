
/*
* 英語に関して、基数を序数にする(例：1を1stにする)関数を実装する
*/

#include <iostream>
#include <iomanip>
#include <string>
#include "String.h"

std::string createOrdinalForm(int n);

int main()
{
	for (int n = 0; n <= 100; ++n)
	{
		std::cout << createOrdinalForm(n) << ", ";
	}
}

std::string createOrdinalForm(int n)
{
	if (n < 0)
	{
		std::cout << "0以上の値を入力してください\n";
		return "";
	}

	std::string strNum = std::to_string(n);
	if (n <= 10 || 20 <= n)
	{
		int remainder = n % 10;
		if (remainder == 1)
		{
			return strNum + "st";
		}
		else if(remainder==2)
		{
			return strNum + "nd";
		}
		else if (remainder == 3)
		{
			return strNum + "rd";
		}
		else
		{
			return strNum + "th";
		}
	}
	else
	{
		return strNum + "th";
	}
}
