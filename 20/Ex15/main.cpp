#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include <stack>
#include "_Map.h"

int main() {
	Map<std::string, std::string> m;
	m.put("aaa", "T");
	m.put("bbb", "h");
	m.put("ccc", "a");
	m.put("ddd", "n");
	m.put("eee", "k");
	m.put("fff", "y");
	m.put("ggg", "o");
	m.put("hhh", "u");

	for (Map<std::string, std::string>::iterator i = m.begin(); i != m.end(); ++i) {
		std::cout << *i << std::endl;
	}
}
