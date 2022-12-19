#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include <stack>
#include <SFML/Graphics.hpp>
#include "Plot.h"
#include "Expression.h"
#include "Library/tokenscanner.h"
#include "Library/strlib.h"
#include "Library/vector.h"

//	文字の大小を無視してs1<s2かどうかを判定する
bool lessIgnoringCase(std::string& s1, std::string& s2) {
	for (std::string::iterator i = s1.begin(), j = s2.begin()
		; i != s1.end() && j != s2.end()
		; ++i, ++j) {
		char c1 = tolower(*i);
		char c2 = tolower(*j);
		if (c1 < c2)return true;
		if (c1 > c2)return false;
	}

	return s1.length() < s2.length();
}

int main() {
	std::string s1 = "bbcdefg";
	std::string s2 = "cBCdefgh";
	std::cout << lessIgnoringCase(s1, s2) << std::endl;
}
