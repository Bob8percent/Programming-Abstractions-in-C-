
/*
* 大きな数字をコンマを使用して記述する関数を実装する
*/

#include <iostream>
#include <iomanip>
#include <string>
#include "String.h"

std::string addConmmas(const std::string& digitsStr);
bool isAllDigits(const std::string& str);

int main()
{
	while (1)
	{
		unsigned long long digits;
		std::cout << "入力：";
		std::cin >> digits;

		std::cout << "コンマ挿入：" << addConmmas(std::to_string(digits)) << "\n";
	}

}

std::string addConmmas(const std::string& digitsStr)
{
	//	すべての文字が数字であるかどうかを判断する
	if (!isAllDigits(digitsStr))
	{
		std::cout << "入力した文字列は不適です\n";
		return "";
	}

	//	カンマを挿入する
	std::string newStr = "";
	for (std::size_t i = 0; i < digitsStr.length(); ++i)
	{
		std::size_t currentDigit = digitsStr.length() - i - 1;
		newStr = digitsStr[currentDigit] + newStr;
		if (i % 3 == 2 && i != digitsStr.length() - 1)
		{
			newStr = ',' + newStr;
		}
	}

	return newStr;
}

bool isAllDigits(const std::string& str)
{
	for (std::size_t i = 0; i < str.length(); ++i)
	{
		if (!isdigit(str.at(i)))
		{
			return false;
		}
	}

	return true;
}
