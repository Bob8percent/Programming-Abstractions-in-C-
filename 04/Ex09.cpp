
/*
* テキストファイルの文字列から指定のアルファベットを除く(小/大文字関係なく)
*/

#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>
#include "String.h"

std::string removeCharas(const std::string& text, const std::string& charas);
std::string removeChara(const std::string& text, const char ch);
void promptForOpenFile(std::ifstream& ifs);
void promptForOpenFile(std::ofstream& ofs);

void copyStream(std::istream& is, std::ostream& os);

int main()
{
	std::ifstream ifs;
	promptForOpenFile(ifs);

	std::ofstream ofs;
	promptForOpenFile(ofs);

	std::string removeStr = "";
	std::cout << "除去するアルファベット：";
	std::getline(std::cin, removeStr);

	std::ostringstream oss;
	copyStream(ifs, oss);

	std::string text = removeCharas(oss.str(), removeStr);

	ofs << text;

	ofs.close();
	ifs.close();
}

void promptForOpenFile(std::ifstream& ifs)
{
	while (1)
	{
		std::cout << "入力ファイル名：";
		std::string filename = "";
		std::getline(std::cin, filename);

		ifs.open(filename);
		if(!ifs.fail())
		{
			return;
		}

		ifs.clear();
		std::cout << "ファイルが開けません" << std::endl;
	}
}

void promptForOpenFile(std::ofstream& ofs)
{
	while (1)
	{
		std::cout << "出力ファイル名：";
		std::string filename = "";
		std::getline(std::cin, filename);

		ofs.open(filename);
		if (!ofs.fail())
		{
			return;
		}

		ofs.clear();
		std::cout << "ファイルが開けません" << std::endl;
	}
}

std::string removeCharas(const std::string& text, const std::string& charas)
{
	std::string newText = text;
	for (std::size_t n = 0; n < charas.length(); ++n)
	{
		char ch = charas.at(n);
		if (isalpha(ch))
		{
			newText = removeChara(newText, ch);
		}
	}

	return newText;
}

std::string removeChara(const std::string& text, const char ch)
{
	std::string newText = "";
	char lowerCh = tolower(ch);
	for (std::size_t i = 0; i < text.length(); ++i)
	{
		char currentCh = tolower(text.at(i));
		if (!(currentCh == lowerCh))
		{
			newText += text.at(i);
		}
	}

	return newText;
}

void copyStream(std::istream& is, std::ostream& os)
{
	char ch;
	while (is.get(ch))
	{
		os.put(ch);
	}
}
