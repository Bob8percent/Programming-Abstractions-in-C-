#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/stack.h"
#include "CharStack.h"
#include "UnitTest.h"
#include "PigLatin.h"

int main() {
	std::string line("this is a pig latin.");
	std::cout << line << std::endl;
	std::cout << "-> Pig Latin output : " << lineToPigLatin(line) << std::endl;
}

