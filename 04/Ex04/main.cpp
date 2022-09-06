
/*
* テキストファイルの文字数、単語数、行数を表示するプログラム
*/

#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>
#include "String.h"

void printTextInfo();
void promptForOpenFile(std::ifstream& ifs);

int main()
{
	printTextInfo();
	
}

void printTextInfo()
{
	std::ifstream ifs;
	promptForOpenFile(ifs);

	std::string line = "";
	std::size_t lineNum = 0, wordNum = 0, charNum = 0;
	while (std::getline(ifs, line))
	{
		++lineNum;

		charNum += line.length() + 1;	//	改行文字、空白文字を含める

		std::istringstream iss(line);
		std::string word;
		while (iss >> std::skipws >> word)	//	前にある空白文字をスキップして単語を読む
		{
			++wordNum;
		}
	}

	//	charNumかlineNumの桁数が必ず最大なので、
	int n = (charNum > lineNum) ? charNum : lineNum;
	int setwNum = 1;
	while (n /= 10)
	{
		++setwNum;
	}
	std::cout << "Chars: " << std::setw(setwNum) << charNum << std::endl;
	std::cout << "Words: " << std::setw(setwNum) << wordNum << std::endl;
	std::cout << "Lines: " << std::setw(setwNum) << lineNum << std::endl;
}

void promptForOpenFile(std::ifstream& ifs)
{
	while (1)
	{
		std::cout << "ファイル名：";
		std::string filename = "";
		std::getline(std::cin, filename);

		ifs.open(filename);
		if (!ifs.fail())
		{
			return;
		}

		ifs.clear();
		std::cout << "ファイルが開けません" << std::endl;
	}
}
