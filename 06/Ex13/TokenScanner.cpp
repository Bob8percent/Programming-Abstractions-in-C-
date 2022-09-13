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
	savedTokens.clear();
}

std::string TokenScanner::nextToken()
{
	if (!savedTokens.isEmpty())return savedTokens.pop();
	if (isIgnoreWS) skipWhiteSpace();
	if (!hasMoreTokens())return "";

	char ch = buffer[scanningPos];
	if (isalpha(ch))
	{
		std::size_t startPos = scanningPos;
		for (std::size_t i = scanningPos; i < buffer.length(); ++i)
		{
			if (isalpha(buffer.at(i)))
			{
				++scanningPos;
			}
			else break;
		}

		return buffer.substr(startPos, scanningPos - startPos);
	}
	else if (isdigit(ch) || ch == '.')
	{
		std::size_t startPos = scanningPos;
		for (std::size_t i = scanningPos; i < buffer.length(); ++i)
		{
			if (isdigit(buffer.at(i)) || buffer.at(i) == '.')
			{
				++scanningPos;
			}
			else break;
		}

		return buffer.substr(startPos, scanningPos - startPos);
	}
	else
	{
		return std::string(1, buffer[scanningPos++]);
	}
}

bool TokenScanner::hasMoreTokens()
{
	return (scanningPos < buffer.length())||(!savedTokens.isEmpty());
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

void TokenScanner::saveToken(const std::string& token)
{
	savedTokens.push(token);
}
