#include <iostream>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "Card.h"
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"
#include "Library/set.h"

void listPermutations(const std::string& word);
void generatePermutations(std::size_t startIdx, const std::string& word);

int main()
{
	listPermutations("abcde");
}

void listPermutations(const std::string& word)
{
	generatePermutations(0, word);
}

void generatePermutations(std::size_t startIdx, const std::string& word)
{
	if (startIdx == word.length() - 1)
	{
		std::cout << word << ", ";
		return;
	}

	//	startIdxとそれ以降の他のインデックスを入れ替え
	char startCh = word.at(startIdx);
	for (std::size_t i = startIdx; i < word.length(); ++i)	//	i==startIdxは入れ替えないパターン
	{
		std::string newWord = word;
		newWord.at(startIdx) = newWord.at(i);
		newWord.at(i) = startCh;
		generatePermutations(startIdx + 1, newWord);
	}
}
