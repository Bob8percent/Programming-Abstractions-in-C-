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

void generateGrayCode(int nBits);
void generateGrayCode(int nBits,std::string bin);

int main() {
	generateGrayCode(3);
}

void generateGrayCode(int nBits) {
	generateGrayCode(nBits - 1, "0");
	generateGrayCode(nBits - 1, "1");
}

//	binのうち1の個数が奇数であれば(1,0)の順に再帰、偶数であれば(0,1)の順に再帰
void generateGrayCode(int nBits, std::string bin) {
	if (nBits <= 0) {
		std::cout << bin << std::endl;
		return;
	}

	std::size_t nOnes = 0;
	for (std::size_t i = 0; i < bin.length(); ++i) {
		if (bin[i] == '1')++nOnes;
	}

	if (nOnes % 2 == 0) {
		generateGrayCode(nBits - 1, bin + '0');
		generateGrayCode(nBits - 1, bin + '1');
	}
	else {
		generateGrayCode(nBits - 1, bin + '1');
		generateGrayCode(nBits - 1, bin + '0');
	}
}

