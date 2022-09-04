#include "String.h"

bool isVowel(char ch)
{
	ch = tolower(ch);
	return (ch == 'a' || ch == 'i' || ch == 'u' || ch == 'e' || ch == 'o');
}

std::string toLowerStr(const std::string& str)
{
	std::string newStr = "";
	for (std::size_t i = 0; i < str.length(); ++i)
	{
		newStr += tolower(str.at(i));
	}

	return newStr;
}

int isIncludeVowel(const std::string& str)
{
	for (std::size_t i = 0; i < str.length(); ++i)
	{
		if (isVowel(str.at(i)))
		{
			return i;
		}
	}

	return -1;
}

bool endWith(const std::string& str, const std::string& suffix)
{
	if (str.length() < suffix.length())
	{
		return false;
	}

	for (int i = str.length() - 1, j = suffix.length() - 1; j >= 0; --i, --j)
	{
		if (str.at(i) != suffix.at(j))
		{
			return false;
		}
	}

	return true;
}

bool endWith(const std::string& str, const char suffix)
{
	if (str.length() < 1)
	{
		return false;
	}

	return str.at(str.length() - 1) == suffix;
}

std::string trim(const std::string& str)
{
	return trimFront(trimBack(str));
}

std::string trimBack(const std::string& str)
{
	//	以下のforの実装理由：
	//	size_tは非負整数なので、"for(std::size_t i = str.length() - 1; i >= 0; --i)"としてしまうと、
	//	常にi>=0なので無限ループとなってしまうから。
	for (std::size_t i = 0; i < str.length(); ++i)
	{
		size_t currentNum = str.length() - i - 1;
		if (isspace(str.at(currentNum)))
		{
			return trimChar(str, currentNum);
		}
	}
}

std::string trimFront(const std::string& str)
{
	for (std::size_t i = 0; i < str.length(); ++i)
	{
		if (isspace(str.at(i)))
		{
			return trimChar(str, i);
		}
	}
}

std::string trimChar(const std::string& str, std::size_t num)
{
	std::string newStr = "";
	for (std::size_t i = 0; i < str.length() - 1; ++i)
	{
		if (i != num)
		{
			newStr += str.at(i);
		}
	}

	return newStr;
}
