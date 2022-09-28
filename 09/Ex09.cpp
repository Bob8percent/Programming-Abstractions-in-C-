#define _USE_MATH_DEFINES

#include <iostream>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"
#include "Library/set.h"
#include "Domino.h"

bool formsDominoChain(Vector<Domino>& dominos);
bool formsDominoChain(Vector<Domino>& dominos, int edgeNum, Set<int>& indices);

int main()
{
	Vector<Domino> dominos;
	dominos += Domino(2, 6), Domino(1, 4), Domino(6, 1), Domino(4, 3);

	std::cout << formsDominoChain(dominos) << std::endl;
}

bool formsDominoChain(Vector<Domino>& dominos)
{
	Set<int> indices;
	return formsDominoChain(dominos, -1, indices);
}

bool formsDominoChain(Vector<Domino>& dominos, int edgeNum, Set<int>& indices)
{
	if (indices.size() == dominos.size())return true;

	for (int i = 0; i < dominos.size(); ++i)
	{
		if (indices.isEmpty())
		{
			indices += i;
			if (formsDominoChain(dominos, dominos[i].getLeftDots(), indices))return true;
			if (formsDominoChain(dominos, dominos[i].getRightDots(), indices))return true;
			indices -= i;
		}
		else if (!indices.contains(i))
		{
			int newEdge;
			if (edgeNum == dominos[i].getRightDots())newEdge = dominos[i].getLeftDots();
			else if (edgeNum == dominos[i].getLeftDots())newEdge = dominos[i].getRightDots();
			else continue;

			indices += i;
			if (formsDominoChain(dominos, newEdge, indices))return true;
			indices -= i;
		}
	}

	return false;
}

