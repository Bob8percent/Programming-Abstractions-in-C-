
/*
* Obenglobishゲームの規則に基づいて単語を返す関数を実装する
* 
* 規則：母音が連続しているときと、eが末尾にある場合を除いて、母音の前にobを追加する
*/

#include <iostream>
#include <iomanip>
#include <string>
#include "String.h"

std::string obenglobish(const std::string& word);

int main()
{
	while (1)
	{
		std::string str;
		std::cout << "入力：";
		std::getline(std::cin, str);

		std::cout << "Obenglobish：" << obenglobish(str) << "\n";
	}
}

std::string obenglobish(const std::string& word)
{
	std::string newWord = "";
	for (std::size_t i = 0; i < word.length(); ++i)
	{
		if (isVowel(word.at(i)))
		{
			//	母音が前の母音に続くかどうか
			bool isConsecutiveVowel = (i >= 1 && isVowel(word.at(i - 1)));
			//	末尾がeであるかどうか
			bool isSuffixE = (i == word.length() - 1 && tolower(word.at(i)) == 'e');

			if (!(isConsecutiveVowel || isSuffixE))
			{
				newWord += "ob";
			}
		}

		newWord += word.at(i);
	}

	return newWord;
}
