
/*
* Ex18の暗号を複合化するキーを返す関数を実装する
* 
* すべて大文字にして返す(大小の区別は暗号化とは無関係となる実装をEx18にて行ったから)
*/

#include <iostream>
#include <iomanip>
#include <string>
#include "String.h"

std::string encodeLetterSubstitution(const std::string& str, const std::string& key);

std::string invertKey(const std::string& key);

const int ALPHA_CHAR_NUM = 26;

int main()
{
	while (1)
	{		
		std::string key = "";
		std::cout << "キー(26文字)：";
		std::cin >> key;

		std::cout << "複合化キー：" << invertKey(key) << "\n";
	}
}

std::string encodeLetterSubstitution(const std::string& str, const std::string& key)
{
	if (key.length() != ALPHA_CHAR_NUM)
	{
		std::cout << "キーが不適です\n";
		return "";
	}

	std::string newStr = "";
	for (int i = 0; i < str.length(); ++i)
	{
		char ch = str.at(i);
		if (isalpha(ch))
		{
			char baseChar = (islower(ch)) ? 'a' : 'A';

			char k = key.at(ch - baseChar);
			char shift = (islower(k)) ? k - 'a' : k - 'A';
			newStr += baseChar + shift;
		}
		else
		{
			newStr += ch;
		}
	}

	return newStr;
}

std::string invertKey(const std::string& key)
{
	if (key.length() != ALPHA_CHAR_NUM)
	{
		std::cout << "キーは26文字でなければいけません\n";
		return "";
	}

	std::string newKey(ALPHA_CHAR_NUM, '0');
	for (std::size_t i = 0; i < ALPHA_CHAR_NUM; ++i)
	{
		char ch = key.at(i);
		char baseChar = (islower(key.at(i))) ? 'a' : 'A';

		newKey.at(ch - baseChar) = char('A' + i);
	}

	return newKey;
}

