#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"

int cannonBall(int height);

int main()
{
	std::cout << cannonBall(3) << std::endl;
}

int cannonBall(int height)
{
	if (height <= 0)return 0;
	if (height == 1)return 1;

	return height * height + cannonBall(height - 1);
}

