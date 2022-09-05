
/*
* 文字をキーに対応する文字に置換した暗号文字列を返す関数を実装する
* 大文字と小文字を合わせるようにした(暗号としてわかりやすくなっちゃうかも？)
*/

#include <iostream>
#include <iomanip>
#include <string>
#include "String.h"

std::string encodeLetterSubstitution(const std::string& str, const std::string& key);

const int ALPHA_CHAR_NUM = 26;

int main()
{
	while (1)
	{
		std::string str = "";
		std::cout << "入力：";
		std::getline(std::cin, str);
		
		std::string key = "";
		std::cout << "キー(26文字)：";
		std::cin >> key;

		std::cout << "エンコード：" << encodeLetterSubstitution(str, key) << "\n";
	}
}

std::string encodeLetterSubstitution(const std::string& str, const std::string& key)
{
	if (key.length() != ALPHA_CHAR_NUM)
	{
		std::cout << "キーが不適です\n";
		return "";
	}

	std::string newStr = "";
	for (int i = 0; i < str.length(); ++i)
	{
		char ch = str.at(i);
		if (isalpha(ch))
		{
			char baseChar = (islower(ch)) ? 'a' : 'A';

			char k = key.at(ch - baseChar);
			char shift = (islower(k)) ? k - 'a' : k - 'A';
			newStr += baseChar + shift;
		}
		else
		{
			newStr += ch;
		}
	}

	return newStr;
}

