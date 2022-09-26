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

//　計算時間が長すぎた
void knightTour(int x, int y);
bool knightTour(Vector<int>& tour, int x, int y, int count);

const int N = 8;

int main()
{
	knightTour(0, 0);
}

void knightTour(int x, int y)
{
	Vector<int> tour(N * N, -1);
	knightTour(tour, x, y, 1);

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			std::cout << std::setw(3) << tour[j + i * N];
		}
		std::cout << std::endl;
	}
}

bool knightTour(Vector<int>& tour, int x, int y, int count)
{
	int idx = x + N * y;
	if (count > N * N)return true;
	if (x < 0 || N <= x || y < 0 || N <= y)return false;
	if (tour[idx] != -1)return false;

	tour[idx] = count;
	if (knightTour(tour, x + 2, y + 1, count + 1))return true;
	if (knightTour(tour, x + 2, y - 1, count + 1))return true;
	if (knightTour(tour, x - 2, y + 1, count + 1))return true;
	if (knightTour(tour, x - 2, y - 1, count + 1))return true;
	if (knightTour(tour, x + 1, y + 2, count + 1))return true;
	if (knightTour(tour, x - 1, y + 2, count + 1))return true;
	if (knightTour(tour, x + 1, y - 2, count + 1))return true;
	if (knightTour(tour, x - 1, y - 2, count + 1))return true;

	tour[idx] = -1;
	return false;
}
