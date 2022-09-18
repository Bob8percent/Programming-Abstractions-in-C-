#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"

int gcd(int x, int y);

int main()
{
	std::cout << gcd(50, 40) << std::endl;
}

int gcd(int x, int y)
{
	if (x <= 0 || y <= 0)
	{
		std::cerr << "ERROR : int gcd(int x, int y) : xまたはyが負になっています" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	int d = x % y;
	if (d == 0)return y;
	return gcd(y, d);
}
