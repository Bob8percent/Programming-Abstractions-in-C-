#include <iostream>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"
#include "Library/set.h"

Set<std::string> generatePermutations(const std::string& str);
//void generatePermutation(const std::string& newStr, const Set<char>& chars, Set<std::string>& set);

int main()
{
	Set<std::string> set = generatePermutations("aeinrst");

	while (!set.isEmpty())
	{
		std::string str = set.first();
		std::cout << str << std::endl;
		set.remove(str);
	}
}

Set<std::string> generatePermutations(const std::string& str)
{
	Set<std::string> result;
	if (str == "")
	{
		result += "";
	}
	else
	{
		for (std::size_t i = 0; i < str.length(); ++i)
		{
			char startCh = str.at(i);
			std::string newStr = str.substr(0, i) + str.substr(i + 1);
			Set<std::string> temp = generatePermutations(newStr);
			while (!temp.isEmpty())
			{
				std::string s = temp.first();
				temp.remove(s);
				result += startCh + s;	//	重複はsetが排除してくれる
			}
		}
	}

	return result;
}



//Set<std::string> generatePermutations(const std::string& str)
//{
//	Set<char> chars;
//	for (std::size_t i = 0; i < str.length(); ++i)
//	{
//		chars += str.at(i);
//	}
//
//	Set<std::string> result;
//	generatePermutation("", chars, result);
//
//	return result;
//}
//
//void generatePermutation(const std::string& newStr,const Set<char>& chars, Set<std::string>& set)
//{
//	if (chars.isEmpty())
//	{
//		set += newStr;
//		return;
//	}
//
//	Set<char> temp = chars;
//	while (!temp.isEmpty())
//	{
//		char ch = temp.first();
//		temp.remove(ch);
//		generatePermutation(newStr + ch, chars - ch, set);
//	}
//}

