#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"

int main()
{
	TokenScanner scanner("This string 1739 3.1416 3.0E+9 numbers");
	scanner.scanNumbers();
	while (scanner.hasMoreTokens())
	{
		std::cout << scanner.nextToken() << std::endl;
	}
}
