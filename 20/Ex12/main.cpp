#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include <stack>
#include "_Set.h"

int main() {
	Set<std::string> s1;
	s1.add("abc");
	s1.add("def");
	s1.add("ghi");
	s1.add("jkl");
	s1.add("opq");
	Set<std::string> s2;
	s2.add("abc");
	s2.add("def");
	s2.add("ghi");
	s2.add("jkl");

	std::cout << (s1 == s2) << std::endl;
}
