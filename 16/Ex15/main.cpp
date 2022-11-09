#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include "_Lexicon.h"

int main() {
	Lexicon lex;
	lex.add("aaaaa");
	lex.add("aaaa");
	lex.add("bbbbb");
	lex.add("ccccc");
	lex.add("ddddd");
	lex.add("eeeee");

	std::cout << lex.find("aaaaa") << std::endl;
	std::cout << lex.find("bbbbb") << std::endl;
	std::cout << lex.find("ccccc") << std::endl;
	std::cout << lex.find("ddddd") << std::endl;
	std::cout << lex.find("eeeee") << std::endl;
	std::cout << lex.find("aaaa") << std::endl;
	std::cout << lex.find("aaa") << std::endl;
	std::cout << lex.find("fffff") << std::endl;
}
