
/*
* 最も長い行を表示する関数を実装する
*/

#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>
#include "String.h"

std::string longestLine();
void openFile(std::ifstream& ifs);

int main()
{
	std::cout << longestLine() << std::endl;
}

std::string longestLine()
{
	std::ifstream ifs;
	openFile(ifs);

	std::string longestLine = "";
	std::string currentLine = "";
	while (std::getline(ifs, currentLine))
	{
		if (longestLine.length() < currentLine.length())
		{
			longestLine = currentLine;
		}
	}

	ifs.close();
	return longestLine;
}

//	ifs.fail()を確認してファイルオープンの際のエラーが消えるまで読み込みを繰り返す
void openFile(std::ifstream& ifs)
{
	while (1)
	{
		std::cout << "ファイル名を入力：";
		
		std::string filename = "";
		std::getline(std::cin, filename);

		ifs.open(filename);
		if (!ifs.fail())
		{
			return;
		}

		ifs.clear();
		std::cout << "ファイルを開けません" << std::endl;
	}
}
