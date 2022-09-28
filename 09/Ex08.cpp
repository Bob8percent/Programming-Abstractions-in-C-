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

void solvePegSolitaire();
bool solvePegSolitaire(Vector<char>& pegs, int count);
bool nextPegSolitaire(Vector<char>& pegs, int x, int y, int toX, int toY, int count);
void moveBlack(Vector<char>& pegs, int x, int y, int toX, int toY);
void reverseBlack(Vector<char>& pegs, int x, int y, int toX, int toY);

bool isSolved(const Vector<char>& pegs);
bool isValidMove(const Vector<char>& pegs, int x, int y, int toX, int toY);

void drawPegSolitaire(const Vector<char>& pegs);

int main()
{
	solvePegSolitaire();
}

void solvePegSolitaire()
{
	Vector<char> pegs;
	//	O:outside, B:black, W:white
	pegs += 'O', 'O', 'B', 'B', 'B', 'O', 'O';
	pegs += 'O', 'O', 'B', 'B', 'B', 'O', 'O';
	pegs += 'B', 'B', 'B', 'B', 'B', 'B', 'B';
	pegs += 'B', 'B', 'B', 'W', 'B', 'B', 'B';
	pegs += 'B', 'B', 'B', 'B', 'B', 'B', 'B';
	pegs += 'O', 'O', 'B', 'B', 'B', 'O', 'O';
	pegs += 'O', 'O', 'B', 'B', 'B', 'O', 'O';
	solvePegSolitaire(pegs, 0);
	drawPegSolitaire(pegs);
}

bool solvePegSolitaire(Vector<char>& pegs, int count)
{
	if (count == 30 && pegs[24] == 'B') return true;

	for (int i = 0; i < pegs.size(); ++i)
	{
		if (pegs[i] == 'W')
		{
			int x = i % 7;
			int y = i / 7;
			if (nextPegSolitaire(pegs, x - 2, y, x, y, count))return true;
			if (nextPegSolitaire(pegs, x, y - 2, x, y, count))return true;
			if (nextPegSolitaire(pegs, x + 2, y, x, y, count))return true;
			if (nextPegSolitaire(pegs, x, y + 2, x, y, count))return true;
		}
	}

	return false;
}

bool nextPegSolitaire(Vector<char>& pegs, int x, int y, int toX, int toY, int count)
{
	if (isValidMove(pegs, x, y, toX, toY))
	{
		moveBlack(pegs, x, y, toX, toY);
		if (solvePegSolitaire(pegs, count + 1))return true;
		reverseBlack(pegs, toX, toY, x, y);
	}

	return false;
}

void moveBlack(Vector<char>& pegs, int x, int y, int toX, int toY)
{
	int idx = x + 7 * y;
	int to_idx = toX + 7 * toY;
	int mid_idx = (x == toX) ? (x + 7 * (y + toY) / 2) : ((x + toX) / 2 + 7 * y);

	pegs[idx] = 'W';
	pegs[mid_idx] = 'W';
	pegs[to_idx] = 'B';
}

void reverseBlack(Vector<char>& pegs, int x, int y, int toX, int toY)
{
	int idx = x + 7 * y;
	int to_idx = toX + 7 * toY;
	int mid_idx = (x == toX) ? (x + 7 * (y + toY) / 2) : ((x + toX) / 2 + 7 * y);

	pegs[idx] = 'W';
	pegs[mid_idx] = 'B';
	pegs[to_idx] = 'B';
}

bool isValidMove(const Vector<char>& pegs, int x, int y, int toX, int toY)
{
	if (x < 0 || 7 <= x || y < 0 || 7 <= y)return false;
	if (toX < 0 || 7 <= toX || toY < 0 || 7 <= toY)return false;

	int idx = x + 7 * y;
	int to_idx = toX + 7 * toY;
	int mid_idx = (x == toX) ? (x + 7 * (y + toY) / 2) : ((x + toX) / 2 + 7 * y);
	return (pegs[idx] == 'B') && (pegs[mid_idx] == 'B') && (pegs[to_idx] == 'W');
}

void drawPegSolitaire(const Vector<char>& pegs)
{
	if (pegs.size() != 49)return;
	for (int i = 0; i < pegs.size(); ++i)
	{
		char ch;
		switch (pegs[i])
		{
		case 'O':
			ch = ' ';
			break;
		case 'B':
			ch = '+';
			break;
		case 'W':
			ch = '-';
			break;
		default:
			break;
		}
		std::cout << ch << ' ';
		if ((i + 1) % 7 == 0)std::cout << std::endl;
	}
}
