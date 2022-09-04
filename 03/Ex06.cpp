
/*
* 非アルファベットで区切られた複合語の頭文字を表示する関数を実装する
*/

#include <iostream>
#include <iomanip>
#include <string>
#include "String.h"

std::string acronym(const std::string& str);

int main()
{
	while (1)
	{
		std::cout << "文字列：";
		std::string str = "";
		std::getline(std::cin, str);

		std::cout << "頭文字：" << acronym(str) << "\n";
	}
}

std::string acronym(const std::string& str)
{
	std::string newStr = "";
	int wordPos = 0;	//	英単語の位置

	while (1)
	{
		//	英単語の最初の位置を求める
		for (int i = wordPos; i < str.length(); ++i)
		{
			char ch = str.at(i);
			if (isalpha(ch))
			{
				wordPos = i;
				newStr += toupper(ch);
				break;
			}
			else if (i == str.length() - 1)
			{
				return newStr;
			}
		}

		//	英単語の最後の位置を求める
		for (int i = wordPos + 1; i < str.length(); ++i)
		{
			char ch = str.at(i);
			if (!isalpha(ch))
			{
				wordPos = i;
				break;
			}
			if (i == str.length() - 1)
			{
				return newStr;
			}
		}
	}
}



