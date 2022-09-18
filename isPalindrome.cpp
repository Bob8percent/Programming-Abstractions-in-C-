#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"

bool isPalindrome(const std::string& str, std::size_t start, std::size_t end);

int main()
{
	while (1)
	{
		std::string str = "";
		std::getline(std::cin, str);
		std::cout << std::boolalpha << isPalindrome(str, 0, str.length()) << std::endl;
	}
}

bool isPalindrome(const std::string& str, std::size_t start, std::size_t end)
{
	if ((end - start) <= 1)return true;

	return (str.at(start) == str.at(end - 1)) && isPalindrome(str, start + 1, end - 1);
}
