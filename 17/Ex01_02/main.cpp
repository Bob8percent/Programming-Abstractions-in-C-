#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include "_Set.h"

int main() {
	Set<char> s1;
	Set<char> s2;

	std::cout << "Enter s1: ";
	std::cin >> s1;
	std::cout << "Enter s2: ";
	std::cin >> s2;

	std::cout << "s1 + s2 = " << (s1 + s2) << std::endl;
	std::cout << "s1 * s2 = " << (s1 * s2) << std::endl;
	std::cout << "s1 - s2 = " << (s1 - s2) << std::endl;
}
