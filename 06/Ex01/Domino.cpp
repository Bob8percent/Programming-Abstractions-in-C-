#include "Domino.h"
#include <iostream>

Domino::Domino()
{
	rightNum = 0;
	leftNum = 0;
}

Domino::Domino(int x, int y)
{
	if (0 <= x && x <= 6 && 0 <= y && y <= 6)
	{
		if (x > y)
		{
			leftNum = x;
			rightNum = y;
		}
		else
		{
			leftNum = y;
			rightNum = x;
		}
	}
	else
	{
		std::cerr << "ERROR : Domino::Domino(int x, int y) : "
			<< "x, yは0~6のどれかでなければいけません" << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

std::ostream& operator<<(std::ostream& os, const Domino& rhs)
{
	return os << "(" << rhs.leftNum << ", " << rhs.rightNum << ")";
}
