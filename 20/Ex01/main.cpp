#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include <stack>
#include <map>
#include "Library/vector.h"

//	WordFrequencyプログラムを書き換えるのは面倒だったので、イテレーターに関していろいろテストしてみた
int main() {
	Vector<std::string> sv;
	sv += "abc";
	sv += "def";
	sv += "ghi";
	sv += "jkl";
	sv += "mno";
	sv += "pqr";
	sv += "stu";
	sv += "vwx";
	sv += "yz";
	for (Vector<std::string>::iterator i = sv.begin(); i != sv.end(); ++i) {
		std::cout << *i << std::endl;
	}

	std::map<std::string, int> sm;
	for (Vector<std::string>::iterator i = sv.begin(); i != sv.end(); ++i) {
		sm[*i] = (i - sv.begin());
	}
	for (std::map<std::string, int>::iterator i = sm.begin(); i != sm.end(); ++i) {
		std::cout << i->first << " " << i->second << std::endl;
	}
}
