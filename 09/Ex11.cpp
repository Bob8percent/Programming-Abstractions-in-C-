#define _USE_MATH_DEFINES

#include <iostream>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"
#include "Library/set.h"
#include "Domino.h"

bool wildcardMatch(const std::string& filename, const std::string& pattern);
bool wildcardMatch(std::size_t fp, std::size_t pp, const std::string& filename, const std::string& pattern);

int main()
{
	std::cout << wildcardMatch("US.txt", "*.*") << std::endl;
	std::cout << wildcardMatch("test", "*.*") << std::endl;
	std::cout << wildcardMatch("test.h", "test.?") << std::endl;
	std::cout << wildcardMatch("test.cpp", "test.?") << std::endl;
	std::cout << wildcardMatch("x", "??*") << std::endl;
	std::cout << wildcardMatch("yy", "??*") << std::endl;
	std::cout << wildcardMatch("zzz", "??*") << std::endl;
}

bool wildcardMatch(const std::string& filename, const std::string& pattern)
{
	return wildcardMatch(0, 0, filename, pattern);
}

bool wildcardMatch(std::size_t fp, std::size_t pp, const std::string& filename, const std::string& pattern)
{
	if (fp == filename.size() && pp == pattern.size())return true;
	if (pp == pattern.size())return false;
	if (fp == filename.size())
	{
		if (pattern.at(pp) != '*')return false;
	}
	else if (fp > filename.size())return false;

	//	任意の文字列
	if (pattern.at(pp) == '*')
	{
		if (wildcardMatch(fp, pp + 1, filename, pattern))return true;
		if (wildcardMatch(fp + 1, pp, filename, pattern))return true;
	}

	//	1文字
	else if (pattern.at(pp) == '?')
	{
		if (wildcardMatch(fp + 1, pp + 1, filename, pattern))return true;
	}

	//	char
	else
	{
		if (filename.at(fp) != pattern.at(pp))return false;
		else if (wildcardMatch(fp + 1, pp + 1, filename, pattern))return true;
	}

	return false;
}

