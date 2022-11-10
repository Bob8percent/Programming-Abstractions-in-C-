#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include "_cctype.h"

int main() {
	
	for (char ch = 33; ch <= 126; ++ch) {
		std::cout << ch << ":";
		std::cout << _isdigit(ch) << _islower(ch) << _isupper(ch) << _isalpha(ch) << _isalnum(ch) << ", ";
	}
}
