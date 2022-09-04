
/*
* 最初の文字が大文字で残りは小文字となる文字列を返すcapitalize()を実装する
*/

#include <iostream>
#include <iomanip>
#include <string>
#include "String.h"

std::string capitalize(const std::string& str);

int main()
{
	while (1)
	{
		std::cout << "文字列：";
		std::string str = "";
		std::getline(std::cin, str);

		std::cout << capitalize(str) << "\n";
	}
}

std::string capitalize(const std::string& str)
{
	std::string newStr = "";

	newStr += toupper(str.at(0));
	for (int i = 1; i < str.length(); ++i)
	{
		newStr += tolower(str.at(i));
	}

	return newStr;
}


