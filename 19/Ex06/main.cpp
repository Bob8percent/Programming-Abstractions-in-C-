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
#include "Nim.h"

int main()
{
	Vector<int> nCoins;
	nCoins += 3, 4, 5;
	int maxGetCoins = 3;
	SimpleNim game(nCoins, maxGetCoins, COMPUTER);
	game.play();
}
