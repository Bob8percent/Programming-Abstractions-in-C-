
/*
* 特定の文字列に対して、句読点や大/小文字の区別などを無視したとき、回文であるかどうかを判断する関数を実装する
*/

#include <iostream>
#include <iomanip>
#include <string>
#include "String.h"

bool isSentencePalindrome(const std::string& str);

int main()
{
	while (1)
	{
		std::cout << "文字列：";
		std::string str = "";
		std::getline(std::cin, str);

		std::cout << "これは回文" << (isSentencePalindrome(str) ? "です" : "ではありません") << "\n";
	}
}


bool isSentencePalindrome(const std::string& str)
{
	std::string newStr = "";

	//	アルファベット以外の文字を除外し、すべて小文字にした文字列に変換する
	for (int i = 0; i < str.length(); ++i)
	{
		char ch = str.at(i);
		if (isalpha(ch))
		{
			newStr += tolower(ch);
		}
	}

	//	変換した文字列が回文であるかどうかを判断する
	for (int i = 0; i < newStr.length() / 2; ++i)
	{
		if (newStr.at(i) != newStr.at(newStr.length() - i - 1))
		{
			return false;
		}
	}

	return true;
}

