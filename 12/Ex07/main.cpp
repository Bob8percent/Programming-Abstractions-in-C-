#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/stack.h"
#include "CharStack.h"
#include "UnitTest.h"

struct Domino {
	int leftDots;
	int rightDots;
};

void initPair(Domino list[], Domino& dom);

int main() {
	Domino onetwo;
	onetwo.leftDots = 1;
	onetwo.rightDots = 2;
	Domino* array = new Domino[2];
	std::cout << "--main()--" << std::endl;
	std::cout << "array : " << array << std::endl;
	std::cout << "&array : " << &array << std::endl;
	std::cout << "&onetwo : " << &onetwo << std::endl;
	initPair(array, onetwo);
}


void initPair(Domino list[], Domino& dom) {
	list[0] = dom;
	list[1].leftDots = dom.rightDots;
	list[1].rightDots = dom.leftDots;
	dom = list[1];

	std::cout << std::endl << "--initPair()--" << std::endl;
	std::cout << "list[0].leftDots : " << list[0].leftDots << std::endl;
	std::cout << "list[0].rightDots : " << list[0].rightDots << std::endl;
	std::cout << "list[1].leftDots : " << list[1].leftDots << std::endl;
	std::cout << "list[1].rightDots : " << list[1].rightDots << std::endl;

	std::cout << "&dom : " << &dom << std::endl;
	std::cout << "&list : " << &list << std::endl;
	std::cout << "list : " << list << std::endl;
}


