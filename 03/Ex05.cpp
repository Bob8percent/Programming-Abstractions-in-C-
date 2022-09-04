
/*
* Scrabbleという単語ゲームにおける得点を計算する関数を実装する
* 
* 大文字以外は空白ととらえ、空白ごとに単語に分割してそれぞれの単語の点数を計算した
*/

#include <iostream>
#include <iomanip>
#include <string>
#include "String.h"

void scrabble(std::string& str);
unsigned long long scrabbleScore(const std::string& word);

int main()
{
	while (1)
	{
		std::cout << "文字列：";
		std::string str = "";
		std::getline(std::cin, str);
		scrabble(str);
	}
}

void scrabble(std::string& str)
{
	unsigned long long score = 0;

	while (str.length() > 0)
	{
		int startUpperPos = 0;	//	大文字文字列の最初の位置
		for (int i = 0; i < str.length(); ++i)
		{
			if (isupper(str.at(i)))
			{
				startUpperPos = i;
				break;
			}
			else if (i == str.length() - 1)
			{
				//	大文字は含まれていない
				std::cout << "score：0\n";
				return;
			}
		}

		int endUpperPos = startUpperPos + 1;	//	大文字文字列の最後の位置
		for (int i = startUpperPos + 1; i < str.length(); ++i)
		{
			if (!isupper(str.at(i)))
			{
				endUpperPos = i;
				break;
			}
			else if (i == str.length() - 1)
			{
				endUpperPos = str.length();
				break;
			}
		}

		std::string upperWord = str.substr(startUpperPos, endUpperPos - startUpperPos);
		std::cout << "[" << str.substr(0, endUpperPos) << "]のscore:" << scrabbleScore(upperWord) << "\n";

		//	計算済みの文字列を除外
		str.erase(0, endUpperPos);
	}
}

unsigned long long scrabbleScore(const std::string& word)
{
	unsigned long long score = 0;
	for (std::size_t i = 0; i < word.length(); ++i)
	{
		char ch = word.at(i);
		switch (ch)
		{
		case 'A': case 'E': case 'I': case 'L': case 'N':
		case 'O': case 'R': case 'S': case 'T': case 'U':
			score += 1;
			break;

		case 'D': case 'G':
			score += 2;
			break;

		case 'B': case 'C': case 'M': case 'P':
			score += 3;
			break;

		case 'F': case 'H': case 'V': case 'W': case 'Y':
			score += 4;
			break;

		case 'K':
			score += 5;
			break;

		case 'J': case 'X':
			score += 8;
			break;

		case 'Q': case 'Z':
			score += 10;
			break;

		default:
			break;
		}
	}

	return score;
}


