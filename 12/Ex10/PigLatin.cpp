#include <cctype>
#include "PigLatin.h"
#include "String.h"

//std::string lineToPigLatin(const std::string& str)
//{
//	std::string newStr = "";
//
//	int start = 0;
//	for (int i = 0; i < str.length(); ++i)
//	{
//		char ch = str.at(i);
//		if (isalpha(ch))
//		{
//
//			if (i == str.length() - 1 || !isalpha(str.at(i + 1)))
//			{
//				newStr += wordToPigLatin(str.substr(start, i - start + 1));
//			}
//		}
//		else
//		{
//			newStr += ch;
//
//			start = i + 1;
//		}
//	}
//
//	return newStr;
//}
//
//std::string wordToPigLatin(const std::string& word)
//{
//	const char startCh = word.at(0);
//
//	if (isVowel(startCh))
//	{
//		//	最初の文字が母音の場合
//		return word + "way";
//	}
//	else
//	{
//		int idx = isIncludeVowel(word);
//		if (idx != -1)
//		{
//			std::string lowerWord = toLowerStr(word);
//
//			std::string s1 = lowerWord.substr(0, idx);
//			std::string s2 = lowerWord.substr(idx);
//
//			std::string newWord = s2 + s1 + "ay";
//
//			char newStartChar = isupper(word.at(0)) ? toupper(newWord.at(0)) : newWord.at(0);
//			return newStartChar + newWord.substr(1);
//		}
//		else
//		{
//			return word;
//		}
//	}
//
//}

MyString lineToPigLatin(const MyString& str)
{
	MyString newStr;

	int start = 0;
	for (int i = 0; i < str.length(); ++i)
	{
		char ch = str[i];
		if (isalpha(ch))
		{

			if (i == str.length() - 1 || !isalpha(str[i + 1]))
			{
				newStr += wordToPigLatin(str.substr(start, i - start + 1));
			}
		}
		else
		{
			std::string s;
			s += ch;

			newStr += MyString(s);

			start = i + 1;
		}
	}

	return newStr;
}

MyString wordToPigLatin(const MyString& word)
{
	const char startCh = word[0];

	if (isVowel(startCh))
	{
		//	最初の文字が母音の場合
		return word + MyString("way");
	}
	else
	{
		int idx = isIncludeVowel(word.toString());
		if (idx != -1)
		{
			MyString lowerWord = toLowerStr(word.toString());

			MyString s1 = lowerWord.substr(0, idx);
			MyString s2 = lowerWord.substr(idx);

			MyString newWord = s2 + s1 + MyString("ay");

			char newStartChar = isupper(word[0]) ? toupper(newWord[0]) : newWord[0];

			std::string s;
			s += newStartChar;
			return MyString(s) + newWord.substr(1);
		}
		else
		{
			return word;
		}
	}

}
