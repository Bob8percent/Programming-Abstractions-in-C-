/*
* startPosから最大n文字の部分文字列を返す関数substr()のような関数を実装する
*/

#include <iostream>
#include <iomanip>
#include <string>
#include "String.h"

std::string my_substr(const std::string& str, std::size_t startPos, std::size_t n);

int main()
{
	while (1)
	{
		std::cout << "文字列：";
		std::string str = "";
		std::getline(std::cin, str);
		std::size_t startPos, n;
		std::cout << "startPos, n：";
		std::cin >> startPos >> n;

		std::cout << my_substr(str, startPos, n) << "\n";
	}
}

std::string my_substr(const std::string& str, std::size_t startPos, std::size_t n)
{
	std::string newStr = "";
	
	if (!(startPos < str.length()))
	{
		std::cerr << "ERROR my_substr() : startPosがstrの長さを超えています\n";
		return newStr;
	}

	std::size_t maxPos = ((startPos + n) < str.length()) ? startPos + n : str.length();
	for (std::size_t i = startPos; i < maxPos; ++i)
	{
		newStr += str.at(i);
	}

	return newStr;
}

