
/*
* 文字列から指定した文字を削除する関数を実装する
*/

#include <iostream>
#include <iomanip>
#include <string>
#include "String.h"

std::string removeCharacters(const std::string& str, const std::string& characters);
std::string removeCharacter(const std::string& str, const char character);

int main()
{
	while (1)
	{
		std::cout << "文字列：";
		std::string str = "";
		std::getline(std::cin, str);

		std::cout << "除去する文字ら：";
		std::string characters = "";
		std::getline(std::cin, characters);

		std::cout << "除去後の文字列：" << removeCharacters(str, characters) << "\n";
	}
}

std::string removeCharacters(const std::string& str, const std::string& characters)
{
	std::string newStr = removeCharacter(str, characters.at(0));
	for (int i = 1; i < characters.length(); ++i)
	{
		newStr = removeCharacter(newStr, characters.at(i));
	}

	return newStr;
}

std::string removeCharacter(const std::string& str, const char character)
{
	std::string newStr = "";
	for (int i = 0; i < str.length(); ++i)
	{
		char ch = str.at(i);
		if (ch != character)
		{
			newStr += ch;
		}
	}

	return newStr;
}



