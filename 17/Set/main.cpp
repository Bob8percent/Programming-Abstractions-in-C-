#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include "_Set.h"

int main() {
	Set<int> s1;
	for (int i = 1; i <= 5; ++i)s1.add(10 * i);

	Set<int> s2;
	for (int i = 1; i <= 10; ++i)s2.add(10 * i);

	s2 -= s1;

	s2.debug();

	s1 *= s2;

	std::cout << s1.isSubsetOf(s2) << std::endl;
}
