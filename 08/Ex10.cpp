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

void listMnemonics(const std::string& num);
void generateMnemonics(std::size_t idx, const std::string& num, const std::string& mnemonic);
std::string numMnemonics(char n);

int main()
{
	listMnemonics("723");
}

void listMnemonics(const std::string& num)
{
	generateMnemonics(0, num, "");
}

void generateMnemonics(std::size_t idx, const std::string& num, const std::string& mnemonic)
{
	if (idx == num.length())
	{
		std::cout << mnemonic << ", ";
		return;
	}

	std::string ms = numMnemonics(num.at(idx));
	for (std::size_t i = 0; i < ms.length(); ++i)
	{
		generateMnemonics(idx + 1, num, mnemonic + ms.at(i));
	}
}

std::string numMnemonics(char n)
{
	if (isdigit(n))
	{
		switch (n)
		{
		case '2':
			return "ABC";
		case '3':
			return "DEF";
		case '4':
			return "GHI";
		case '5':
			return "JKL";
		case '6':
			return "MNO";
		case '7':
			return "PQRS";
		case '8':
			return "TUV";
		case '9':
			return "WXYZ";
		default:
			break;
		}
	}

	return "";
}
