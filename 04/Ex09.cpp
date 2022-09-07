
/*
* タブ文字を指定したスペース数になるように変換する
* 
* 文字列に関して、タブ文字は列数は多いが文字数は1つであることに注意
*/

#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>
#include "String.h"

void tabToSpace(std::istream& is, std::ostream& os, int tabNum);

void promptForOpenFile(std::ifstream& ifs, const std::string& prompt);
void promptForOpenFile(std::ofstream& ofs, const std::string& prompt);
int promptForIntger(std::istream& is, const std::string& prompt);

int main()
{
	//std::ifstream ifs;
	//promptForOpenFile(ifs, "ファイル入力：");

	//std::ofstream ofs;
	//promptForOpenFile(ofs, "ファイル出力：");

	int tabNum = promptForIntger(std::cin, "スペース数");

	//tabToSpace(ifs, ofs, tabNum);

	//ofs.close();
	//ifs.close();
}

void tabToSpace(std::istream& is, std::ostream& os, int tabNum)
{
	std::string line = "";
	
	while (std::getline(is, line))
	{
		int count = 0;
		for (std::size_t i = 0; i < line.length(); ++i)
		{
			char ch = line.at(i);
			if (ch == '\t')
			{
				int shift = tabNum - count % tabNum;
				while (shift--)
				{
					os.put(' ');
				}

				count = 0;
				continue;
			}
			else
			{
				os.put(ch);
			}

			count++;
		}

		os.put('\n');
	}
}

void promptForOpenFile(std::ifstream& ifs, const std::string& prompt)
{
	while (1)
	{
		std::cout << prompt;
		std::string filename = "";
		std::getline(std::cin, filename);

		ifs.open(filename);
		if(!ifs.fail())
		{
			return;
		}

		ifs.clear();
		std::cout << "ERROR:void promptForOpenFile(std::ifstream& ifs, const std::string& prompt) : "
			<< "ファイルが開けません" << std::endl;
	}
}

void promptForOpenFile(std::ofstream& ofs, const std::string& prompt)
{
	while (1)
	{
		std::cout << prompt;
		std::string filename = "";
		std::getline(std::cin, filename);

		ofs.open(filename);
		if (!ofs.fail())
		{
			return;
		}

		ofs.clear();
		std::cout << "ERROR:void promptForOpenFile(std::ofstream& ofs, const std::string& prompt) : "
			<< "ファイルが開けません" << std::endl;
	}
}

int promptForIntger(std::istream& is, const std::string& prompt)
{
	while (1)
	{
		std::cout << prompt;
		std::string line;
		std::getline(is, line);

		//	正しく整数に変換できないときのエラー検出のためにstringstreamを使用
		int value;
		std::istringstream iss(line);
		//	std::skipwsは入力の際に先頭の空白を無効にするマニピュレータなので、指定位置は無関係
		//	line=="1 2"のとき、valueは1を読み込む際に先頭の空白を無効にしようとするが、空白はないので無意味となる
		//	std::wsのfailbit指定の挙動はよく知らないのでしばらくstd::skipwsを使っていくことにする
		iss >> value >> std::skipws >> std::skipws;	

		//	以下のすべての場合を正しく判定するために!iss.fail()とiss.eof()が必要
		//	"1 2 3"	->	!iss.fail() = true, iss.eof() = false
		//	"8t"	->	!iss.fail() = true,	iss.eof() = false
		//	"8 "	->	!iss.fail() = true,	iss.eof() = false(この判定が正しいとするかは微妙ではあるが)
		//	"8"		->	!iss.fail() = true,	iss.eof() = true
		//	" 8"	->	!iss.fail() = true, iss.eof() = true

		std::cout << std::boolalpha << !iss.fail() << std::endl;
		std::cout << std::boolalpha << iss.eof() << std::endl;
		if (!iss.fail() && iss.eof())
		{
			return value;
		}

		iss.clear();
		std::cout << "ERROR:int promptForIntger(std::istream& is, const std::string& prompt) : "
			<< "整数に変換できません" << std::endl;
	}
}
