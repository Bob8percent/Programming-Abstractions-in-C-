#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/stack.h"
#include "CharStack.h"
#include "UnitTest.h"

int* createIndexArray(int n);

int main() {
	int n = 10;
	int* a = createIndexArray(n);

	for (int i = 0; i < n; ++i) {
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
}

int* createIndexArray(int n) {
	int* a = new int[n];
	for (int i = 0; i < n; ++i) {
		a[i] = i;
	}
	return a;
}


