#include "String.h"

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
