#include <iostream>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"
#include "Library/set.h"

void embeddedWords(const std::string& word, Set<std::string>& eWords);

int main()
{
	Set<std::string> set;
	embeddedWords("happy", set);

	while (!set.isEmpty())
	{
		std::string s = set.first();
		set.remove(s);
		std::cout << s << ", ";
	}
	std::cout << std::endl;
}


void embeddedWords(const std::string& word, Set<std::string>& eWords)
{
	if (word == "")return;

	for (std::size_t i = 0; i < word.length(); ++i)
	{
		embeddedWords(word.substr(0, i) + word.substr(i + 1), eWords);
	}
	eWords += word;
}
