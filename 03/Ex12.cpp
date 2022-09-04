
/*
* 単語を複数形にする関数を実装する
*/

#include <iostream>
#include <iomanip>
#include <string>
#include "String.h"

std::string createRegularPlural(const std::string& word);

int main()
{
	while (1)
	{
		std::cout << "単数の単語：";
		std::string word = "";
		std::cin >> word;

		std::cout << createRegularPlural(word) << "\n";
	}
}

std::string createRegularPlural(const std::string& word)
{
	if (endWith(word, 's') || endWith(word, 's') || endWith(word, 'z')
		|| endWith(word, "sh") || endWith(word, "ch"))
	{
		return word + "es";
	}
	else if (endWith(word, 'y'))
	{
		std::string newWord = word.substr(0, word.length() - 1);
		return newWord + "ies";
	}
	else
	{
		return word + 's';
	}
}

