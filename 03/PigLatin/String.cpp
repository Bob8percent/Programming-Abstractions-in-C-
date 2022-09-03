#include "string.h"

bool isVowel(const char ch)
{
	return (ch == 'a' || ch == 'i' || ch == 'u' || ch == 'e' || ch == 'o');
}

int isIncludeVowel(const std::string& str)
{
	for (int i = 0; i < str.length(); ++i)
	{
		if (isVowel(str.at(i)))
		{
			return i;
		}
	}

	return -1;
}
