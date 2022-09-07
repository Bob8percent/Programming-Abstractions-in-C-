
/*
* 読み込んだテキストファイルの各アルファベットをランダムに変換して標準出力
* ちなみに小/大文字は一致させる
*/

#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>
#include "String.h"

void initRand();
void setSeed(int seed);
double getRandReal(double low, double high);
int getRandIntger(int low, int high);

void promptForOpenFile(std::ifstream& ifs);
void copyStream(std::istream& is, std::ostream& os);
std::string encodeTextFile();

const int ALPHA_CHAR_NUM = 26;

int main()
{
	std::cout << encodeTextFile() << std::endl;
}

std::string encodeTextFile()
{
	std::ifstream ifs;
	promptForOpenFile(ifs);
	std::ostringstream oss;
	copyStream(ifs, oss);

	std::string text = oss.str();
	std::string newText = "";
	for (std::size_t i = 0; i < text.length(); ++i)
	{
		char ch = text.at(i);

		//	アルファベットであれば暗号化
		if (isalpha(ch))
		{
			char baseChar = (isupper(ch) ? 'A' : 'a');

			int shift = getRandIntger(0, ALPHA_CHAR_NUM - 1);
			char encodeChar = baseChar + (ch - baseChar + shift) % ALPHA_CHAR_NUM;
			newText += encodeChar;
		}
		else
		{
			newText += ch;
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

void initRand()
{
	static bool isFirst = true;
	if (isFirst)
	{
		srand(int(time(NULL)));
		isFirst = false;
	}
}

void setSeed(int seed)
{
	initRand();
	srand(seed);
}

double getRandReal(double low, double high)
{
	initRand();
	double ratio = rand() / (RAND_MAX * 1.0);	//	0 <= ratio <=1
	return ratio * (high - low) + low;
}

int getRandIntger(int low, int high)
{
	initRand();
	double ratio = rand() / (RAND_MAX * 1.0 + 1);	//	0 <= ratio <1
	return int(std::floor(ratio * (high - low + 1) + low));
}
