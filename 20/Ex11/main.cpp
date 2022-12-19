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

//	冠詞を除く
std::string::iterator exceptArticle(std::string& s) {
	bool isExcept = true;
	//	a
	char test1[2] = { 'a',' ' };
	int count = 0;
	for (std::string::iterator i = s.begin(); i != s.end() && count < 2; ++i, ++count) {
		if (test1[count] != *i) isExcept = false;
	}
	if (isExcept)return (s.begin() + 2);

	//	an
	isExcept = true;
	count = 0;
	char test2[3] = { 'a','n',' ' };
	for (std::string::iterator i = s.begin(); i != s.end() && count < 2; ++i, ++count) {
		if (test2[count] != *i) isExcept = false;
	}
	if (isExcept)return (s.begin() + 3);

	//	the
	isExcept = true;
	count = 0;
	char test3[4] = { 't','h','e',' ' };
	for (std::string::iterator i = s.begin(); i != s.end() && count < 2; ++i, ++count) {
		if (test3[count] != *i) isExcept = false;
	}
	if (isExcept)return (s.begin() + 4);

}

//	文字の大小を無視してs1<s2かどうかを判定する
bool titleComesBefore(std::string& s1, std::string& s2) {
	for (std::string::iterator i = exceptArticle(s1), j = exceptArticle(s2)
		; i != s1.end() && j != s2.end()
		; ++i, ++j) {
		//	空白を除く句読点かどうか
		bool isPunctMark1 = !(isalnum(*i) || isspace(*i));
		bool isPunctMark2 = !(isalnum(*j) || isspace(*j));
		if (isPunctMark1 && isPunctMark2) { continue; }
		else if (isPunctMark1) { --j; continue; }
		else if (isPunctMark2) { --i; continue; }

		char c1 = tolower(*i);
		char c2 = tolower(*j);
		if (c1 < c2)return true;
		if (c1 > c2)return false;
	}

	return s1.length() < s2.length();
}



int main() {
	std::string s1 = "the ABC";
	std::string s2 = "a abc";
	std::cout << titleComesBefore(s1, s2) << std::endl;
}
