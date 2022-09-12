#include "TokenScanner.h"
#include <iostream>

TokenScanner::TokenScanner()
{
	initScanner();
}

TokenScanner::TokenScanner(const std::string& str)
{
	initScanner();
	setInput(str);
}

void TokenScanner::setInput(const std::string& str)
{
	buffer = str;
}

std::string TokenScanner::nextToken()
{
	if (isIgnoreWS) skipWhiteSpace();
	if (!hasMoreTokens())return "";

	if (isalnum(buffer[scanningPos]))
	{
		std::size_t startPos = scanningPos;
		for (std::size_t i = scanningPos; i < buffer.length(); ++i)
		{
			if (isalnum(buffer[i]))
			{
				++scanningPos;
			}
			else
			{
				return buffer.substr(startPos, scanningPos - startPos);
			}
		}
	}
	else
	{
		return std::string(1, buffer[scanningPos++]);
	}
}

bool TokenScanner::hasMoreTokens()
{
	return scanningPos < buffer.length();
}

void TokenScanner::ignoreWhiteSpace()
{
	isIgnoreWS = true;
}

void TokenScanner::initScanner()
{
	buffer = "";
	isIgnoreWS = false;
	scanningPos = 0;
}

void TokenScanner::skipWhiteSpace()
{
	for (int i = scanningPos; i < buffer.length(); ++i)
	{
		if (isspace(buffer[i]))
		{
			++scanningPos;
		}
		else
		{
			return;
		}
	}
}
