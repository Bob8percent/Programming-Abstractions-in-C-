#define _USE_MATH_DEFINES

#include <iostream>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cmath>
#include <string>
#include <SFML/Graphics.hpp>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/random.h"
#include "Library/map.h"
#include "Library/set.h"
#include <ctime>

void generateBinaryCode(int nBits);

int main() {
	generateBinaryCode(3);
}

void generateBinaryCode(int nBits) {
	int maxVal = std::pow(2, nBits);
	for (int n = 0; n < maxVal; ++n) {
		int val = n;
		std::string str;
		for (int i = 0; i < nBits; ++i){
			str = (char)(val % 2 + '0') + str;
			val /= 2;
		}
		std::cout << str << std::endl;
	}
}



