#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include <stack>
#include "StringMap.h"

int main() {
	StringMap s;
	s.put("aaa", "111");
	s.put("bbb", "1122");
	s.put("ccc", "113");
	s.put("ddd", "114");
	for (StringMap::iterator i = s.begin(); i != s.end(); i++) {
		std::cout << *i << std::endl;
	}
}
