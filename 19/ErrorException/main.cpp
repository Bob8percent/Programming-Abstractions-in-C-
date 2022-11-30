#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include "_Shape.h"
#include "Library/vector.h"

double divide(double a, double b) {
	if (b == 0) {
		throw std::range_error("divided zero");
	}

	return a / b;
}

int main() {
	int value = -1;
	try {
		value = divide(100, 0);
	}
	catch (std::range_error& e) {
		value = 0;	//	軌道修正できるのが例外処理の強み(今まではstd::exitで終了するだけだった)
	}

	std::cout << value << std::endl;
}
