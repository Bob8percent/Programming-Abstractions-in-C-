
#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>
#include "String.h"
#include "Library/vector.h"
#include "Library/queue.h"
#include "Library/map.h"
#include "Rational.h"
#include "TokenScanner.h"
#include "Domino.h"
#include "Card.h"

int main()
{
	for (Suit suit = CLUBS; suit <= SPADES; ++suit)
	{
		for (int rank = ACE; rank <= KING; ++rank)
		{
			std::cout << " " << Card(rank, suit);
		}
		std::cout << std::endl;
	}
}
