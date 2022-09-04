
/*
* 特定の文字列に対してある文字列に置き換える関数を実装する
* 
* str.find()とstr.replace()を使えば容易に実装できるが、使わずにやると以下のようになった
*/

#include <iostream>
#include <iomanip>
#include <string>
#include "String.h"

std::string replaceAll(const std::string& str, const char ch1, const char ch2);
std::string replaceAll(const std::string& str, const std::string& s1, const std::string& s2);

int main()
{
	while (1)
	{
		std::cout << "文字列：";
		std::string str = "";
		std::getline(std::cin, str);

		std::string s1 = "", s2 = "";
		std::cout << "s1：";
		std::getline(std::cin, s1);
		std::cout << "s2：";
		std::getline(std::cin, s2);

		std::cout << "s1をs2に入れ替えた文字列：" << replaceAll(str, s1, s2) << "\n";
	}
}

std::string replaceAll(const std::string& str, const char ch1, const char ch2)
{
	std::string newStr = "";
	for (int i = 0; i < str.length(); ++i)
	{
		char currentCh = str.at(i);
		if (currentCh == ch1)
		{
			newStr += ch2;
		}
		else
		{
			newStr += currentCh;
		}
	}

	return newStr;
}

std::string replaceAll(const std::string& str, const std::string& s1, const std::string& s2)
{
	std::string newStr = "";
	int startPos = 0, endPos = 0;

	while (1)
	{
		// s1の最初のアルファベットを見つける
		for (int i = startPos; i < str.length(); ++i)
		{
			if (str.at(i) == s1.at(0))
			{
				startPos = i;
				break;
			}
			else 
			{
				newStr += str.at(i);
				if (i == str.length() - 1)
				{
					return newStr;
				}
			}
		}

		//	s1を見つけたかどうかを判断する
		if (str.length() - startPos < s1.length())
		{
			newStr += str.substr(startPos);
			return newStr;
		}

		bool isS1Exist = true;
		for (int i = startPos , j = 0; j < s1.length(); ++i, ++j)	//	startPosからの残りの文字数はs1.length()以下であることは確認済み
		{
			endPos = i;
			if (str.at(i) != s1.at(j))
			{
				isS1Exist = false;
				break;
			}
		}

		if (isS1Exist)
		{
			//	s2に入れ替え
			newStr += s2;

			startPos = endPos + 1;
		}
		else
		{
			newStr += str.at(startPos);
			
			//	一つ次の文字から検索しなおす
			++startPos;
		}
	}
}

////	====================================================================
////	str.find()とstr.replace()を使う場合、とても簡単
//std::string replaceAll(const std::string& str, const std::string& s1, const std::string& s2)
//{
//	std::string newStr = str;
//	while (true)
//	{
//		std::size_t idx = newStr.find(s1);
//
//		if (idx == std::string::npos)
//		{
//			//	newStrにs1が見つからなかった場合
//			break;
//		}
//
//		newStr.replace(idx, s1.length(), s2);
//	}
//
//	return newStr;
//}


