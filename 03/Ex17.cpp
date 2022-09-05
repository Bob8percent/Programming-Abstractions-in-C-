
/*
* アルファベットをシフトする暗号文字列を返す関数を実装する
*/

#include <iostream>
#include <iomanip>
#include <string>
#include "String.h"

std::string encodeCaeserCipher(const std::string& str, int shift);

int main()
{
	while (1)
	{
		std::string str;
		std::cout << "入力：";
		std::getline(std::cin, str);
		
		int shift = 0;
		std::cout << "シフト：";
		std::cin >> shift;

		std::cout << "エンコード：" << encodeCaeserCipher(str, shift) << "\n";
	}
}

std::string encodeCaeserCipher(const std::string& str, int shift)
{
	if (shift == 0)
	{
		return str;
	}

	const int alphabetNum = 26;
	std::string newStr = "";
	for (std::size_t i = 0; i < str.length(); ++i)
	{
		char ch = str.at(i);

		if (isalpha(ch))
		{
			char startChar = islower(ch) ? 'a' : 'A';
			newStr += char(startChar + (ch - startChar + shift + alphabetNum) % alphabetNum);
		}
		else
		{
			newStr += ch;
		}
	}

	return newStr;
}
