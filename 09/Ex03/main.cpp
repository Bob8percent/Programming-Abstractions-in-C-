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
#include "Maze.h"



int main()
{
	Maze maze("mazeTest.txt");

	Vector<IPoint> path;
	maze.findSolutionPath(path);
	
	for (int i = 0; i < path.size(); ++i)
	{
		std::cout << "(" << path[i].x << ", " << path[i].y << ")";
	}

	maze.drawMaze();
}

