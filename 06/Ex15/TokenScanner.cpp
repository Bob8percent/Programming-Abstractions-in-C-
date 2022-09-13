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
	if (isalnum(ch))
	{
		if (isScanNumber)
		{
			std::string num = scanNumber();
			if (!num.empty())
			{
				return num;
			}
		}

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
	else
	{
		if (isScanString && isQuotation(ch))
		{
			std::size_t startPos = scanningPos;
			for (std::size_t i = scanningPos + 1; i < buffer.length(); ++i)
			{
				char currentChar = buffer.at(i);
				if (isQuotation(currentChar) && ch == currentChar)
				{
					scanningPos = i + 1;
					return buffer.substr(startPos, scanningPos - startPos);
				}
			}
		}
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
	isScanString = false;
	isScanNumber = false;
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

void TokenScanner::scanString()
{
	isScanString = true;
}

void TokenScanner::scanNumbers()
{
	isScanNumber = true;
}

bool TokenScanner::isQuotation(char ch) const
{
	return (ch == '\'' || ch == '\"');
}


/*
* 有限ステートマシンを使用した実装：ScanNumber()
*/
enum State
{
	s0,
	s1,
	s2,
	s3,
	s4,
	s5
};
std::string TokenScanner::scanNumber()
{
	std::string str = "";
	State state = s0;
	std::size_t startPos = scanningPos;
	while (scanningPos < buffer.length())
	{
		char ch = buffer.at(scanningPos);
		switch (state)
		{
		case s0:
			if (isdigit(ch))
			{
				str += ch;
				state = s1;
			}
			else
			{
				return "";
			}
			break;

		case s1:
			if (isdigit(ch))
			{
				str += ch;
			}
			else if (ch == '.')
			{
				str += ch;
				state = s2;
			}
			else if (ch == 'E')
			{
				str += ch;
				state = s3;
			}
			else
			{
				return str;
			}
			break;

		case s2:
			if (isdigit(ch))
			{
				str += ch;
			}
			else if (ch == 'E')
			{
				str += ch;
				state = s3;
			}
			else
			{
				return str;
			}
			break;

		case s3:
			if (isdigit(ch))
			{
				str += ch;
				state = s5;
			}
			else if ((ch == '+') || (ch == '-'))
			{
				str += ch;
				state = s4;
			}
			else
			{
				--scanningPos;
				return buffer.substr(startPos, scanningPos - startPos);
			}
			break;

		case s4:
			if (isdigit(ch))
			{
				str += ch;
				state = s5;
			}
			else
			{
				scanningPos -= 2;
				return buffer.substr(startPos, scanningPos - startPos);
			}
			break;

		case s5:
			if (isdigit(ch))
			{
				str += ch;
			}
			else
			{
				return buffer.substr(startPos, scanningPos - startPos);
			}
			break;
		}

		++scanningPos;
	}

	return str;
}

