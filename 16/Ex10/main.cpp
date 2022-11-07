#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include "Library/vector.h"
#include "_Map.h"

int main() {
	Map<std::string, std::string> m;
	for (char ch = 'a'; ch <= 'z'; ++ch) {
		std::string key(3, ch);
		char uch = toupper(ch);
		std::string value(3, uch);

		m.put(key, value);
	}

	for (char ch = 'a'; ch <= 'z'; ++ch) {
		std::string key(3, ch);
		char uch = toupper(ch);
		//std::string value(3, uch);

		std::cout << key << " : " << m.get(key) << std::endl;
	}

	m["aaa"] = "AAAAA";
	std::cout << m["aaa"] << std::endl;

	m.remove("ddd");
	m.remove("fff");
	m.remove("zzz");
	m.remove("ggg");
	m.remove("ppp");
	m.debug();
}
