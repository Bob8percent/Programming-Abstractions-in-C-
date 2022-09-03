#include <cctype>
#include "PigLatin.h"
#include "String.h"

std::string lineToPigLatin(const std::string& str)
{
	std::string newStr = "";

	int start = 0;
	for (int i = 0; i < str.length(); ++i)
	{
		char ch = str.at(i);
		if (isalpha(ch))
		{

			if (i == str.length() - 1 || !isalpha(str.at(i + 1)))
			{
				newStr += wordToPigLatin(str.substr(start, i - start + 1));
			}
		}
		else
		{
			newStr += ch;

			start = i + 1;
		}
	}

	return newStr;
}

std::string wordToPigLatin(const std::string& word)
{
	const char startCh = tolower(word.at(0));
	if (isVowel(startCh))
	{
		//	最初の文字が母音の場合
		return word + "way";
	}
	else
	{
		int idx = isIncludeVowel(word);
		if (idx != -1)
		{
			std::string s1 = word.substr(0, idx);
			std::string s2 = word.substr(idx);

			return s2 + s1 + "ay";
		}
		else
		{
			return word;
		}
	}
}
