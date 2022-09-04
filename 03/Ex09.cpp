
/*
* 二重文字を単一の文字にする関数を実装する
*/

#include <iostream>
#include <iomanip>
#include <string>
#include "String.h"

std::string removeDoubledLetters(const std::string& str);

int main()
{
	while (1)
	{
		std::cout << "文字列：";
		std::string str = "";
		std::cin >> str;

		std::cout << "処理後の文字列：" << removeDoubledLetters(str) << "\n";
	}
}

std::string removeDoubledLetters(const std::string& str)
{
	if (str.length() <= 1)
	{
		return str;
	}

	std::string newStr = "";
	for (int i = 0; i < str.length() - 1; ++i)
	{
		char ch = str.at(i);
		char nextCh = str.at(i + 1);
		if (ch == nextCh)
		{
			++i;
		}

		newStr += ch;
	}

	return newStr;
}



