#include <iostream>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "Card.h"
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"
#include "Library/set.h"

Set<std::string> generatePermutations(const std::string& word);

int main()
{
	Set<std::string> set;
	set = generatePermutations("abcde");

	while (!set.isEmpty())
	{
		std::string s = set.first();
		set.remove(s);
		std::cout << s << ", ";
	}
}

Set<std::string> generatePermutations(const std::string& word)
{
	Set<std::string> result;

	if (word=="")result += "";
	else
	{
		char startCh = word.at(0);

		Set<std::string> set = generatePermutations(word.substr(1));

		//	startChをsetの文字列(以下にあるs)の可能な位置すべてに挿入
		while (!set.isEmpty())
		{
			std::string s = set.first();
			set.remove(s);
			for (std::size_t i = 0; i <= s.length(); ++i)
			{
				result += s.substr(0, i) + startCh + s.substr(i);
			}
		}
	}

	return result;
}
