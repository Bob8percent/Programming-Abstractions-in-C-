
/*
* DNA一本鎖(鋳型鎖)に対して、それより短い一本鎖DNAの結合位置を返す関数を実装する
*
* 範囲を超えた結合は、s2の一つずつ左端を除外してfindDNAMatch()を実行、返り値が0であればOK、という関数を実装すればよい。
* s2の右端を除外する場合も同様(この場合返り値はs1.length()-1であればOK)。
*/

#include <iostream>
#include <iomanip>
#include <string>
#include "String.h"

int findDNAMatch(const std::string& s1, const std::string& s2, int start = 0);	//	startは検索開始位置
bool isComplementary(const char b1, const char b2);	//	塩基が相補的であるかどうか


int main()
{
	while (1)
	{
		//	s1, s2に全文字がATGCatgcのどれかで構成されている前提
		std::string s1 = "";
		std::cout << "鋳型鎖：";
		std::cin >> s1;

		std::string s2 = "";
		std::cout << "プライマー鎖：";
		std::cin >> s2;

		std::cout << "結合開始位置(鋳型鎖基準)：" << findDNAMatch(s1, s2) << "\n";
	}
}

int findDNAMatch(const std::string& s1, const std::string& s2, int start)
{
	if (s1.length() - 1 < start)
	{
		return -1;
	}

	int pos = start;
	while (1)
	{
		//	プライマー鎖の左端の塩基と結合する位置を探す
		for (std::size_t i = pos; i < s1.length(); ++i)
		{
			if (isComplementary(s1.at(i), s2.at(0)))
			{
				pos = i;
				break;
			}
			else if (i == s1.length() - 1)
			{
				return -1;
			}
		}

		//	s2がs1をはみ出そうだったら不適
		if (pos + s2.length() > s1.length())
		{
			return -1;
		}

		//	上の位置を起点としたとき、s1とs2の結合が成立するかを確かめる
		for (std::size_t i = pos, j = 0; i < s1.length() && j < s2.length(); ++i, ++j)
		{
			if (!isComplementary(s1.at(i), s2.at(j)))
			{
				//	次の塩基から探索しなおす
				++pos;
				break;
			}
			else if (i == s1.length() - 1 || j == s2.length() - 1)
			{
				return pos;
			}
		}
	}
}

bool isComplementary(const char b1, const char b2)
{
	std::string basePair(1, char(toupper(b1)));
	basePair += char(toupper(b2));

	return (basePair == "AT" || basePair == "TA" || basePair == "GC" || basePair == "CG");
}
