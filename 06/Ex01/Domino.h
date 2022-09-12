#pragma once
#include <ostream>

class Domino
{
public:
	Domino();
	Domino(int x, int y);

	friend std::ostream& operator<<(std::ostream& os, const Domino& rhs);
private:
	int rightNum, leftNum;
};

std::ostream& operator<<(std::ostream& os, const Domino& rhs);
