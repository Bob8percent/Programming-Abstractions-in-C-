#include <iostream>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"

std::string reverse(const std::string& word);
std::string replaceChars(const std::string& word, int left, int right);

int main()
{
	std::cout << reverse("program") << std::endl;
}

std::string reverse(const std::string& word)
{
	return replaceChars(word, 0, word.length() - 1);
}

std::string replaceChars(const std::string& word, int left, int right)
{
	if (left >= right)return word;

	std::string newWord = word;
	char temp = newWord.at(left);
	newWord.at(left) = newWord.at(right);
	newWord.at(right) = temp;
	return replaceChars(newWord, left + 1, right - 1);
}
