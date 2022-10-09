#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/stack.h"

int main()
{
	TokenScanner scanner;
	scanner.setInput(std::cin);

	while (scanner.hasMoreTokens()) {
		std::cout << scanner.nextToken() << std::endl;
	}
}
