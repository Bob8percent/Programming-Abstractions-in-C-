#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include "_Set.h"

Set<int> createPrimeSet(int max) {
	Set<int> s;
	for (int n = 2; n <= max; ++n) {

		bool isPrime = true;
		for (int r = 2; r * r <= n; ++r) {
			if (n % r == 0) {
				isPrime = false;
				break;
			}
		}
		if (isPrime)s.add(n);
	}
	return s;
}

int main() {
	Set<int> s = createPrimeSet(50);
	std::cout << s << std::endl;
}
