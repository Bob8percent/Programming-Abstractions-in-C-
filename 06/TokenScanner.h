#pragma once
#include <istream>
#include <string>

class TokenScanner
{
public:
	TokenScanner();
	TokenScanner(const std::string& str);

	void setInput(const std::string& str);

	std::string nextToken();
	bool hasMoreTokens();
	void ignoreWhiteSpace();

private:
	std::string buffer;
	std::size_t scanningPos;
	bool isIgnoreWS;

	void initScanner();
	void skipWhiteSpace();
};

