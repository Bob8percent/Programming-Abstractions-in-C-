#pragma once
#include <istream>
#include <string>
#include "Library/stack.h"

class TokenScanner
{
public:
	TokenScanner();
	TokenScanner(const std::string& str);

	void setInput(const std::string& str);

	void saveToken(const std::string& token);
	std::string nextToken();
	bool hasMoreTokens();
	void ignoreWhiteSpace();

private:
	std::string buffer;
	std::size_t scanningPos;
	bool isIgnoreWS;
	Stack<std::string> savedTokens;

	void initScanner();
	void skipWhiteSpace();
};

