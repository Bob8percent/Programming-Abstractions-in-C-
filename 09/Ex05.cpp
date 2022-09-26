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

bool findQueenPos(Vector<bool>& nQueen, const int N);
bool findQueenPos(Vector<bool>& nQueen, const int N, int depth);
bool isDuplicate(Vector<bool>& nQueen, const int idx, const int N);
void drawPixels(Vector<bool>& pixels, const int nRows, const int nCols);

int main()
{
	const int N = 8;
	Vector<bool> chess(N * N, false);
	
	std::cout << findQueenPos(chess, N) << std::endl;

	drawPixels(chess, N, N);
}

bool findQueenPos(Vector<bool>& nQueen, const int N)
{
	if (nQueen.size() != N * N) return false;

	return findQueenPos(nQueen, N, N);
}

bool findQueenPos(Vector<bool>& nQueen, const int N, int depth)
{
	if (depth == 0)
	{
		return true;
	}

	for (int i = 0; i < N * N; ++i)
	{
		if (!isDuplicate(nQueen, i, N))
		{
			nQueen[i] = true;
			if (findQueenPos(nQueen, N, depth - 1))
			{
				return true;
			}
			nQueen[i] = false;
		}
	}

	return false;
}

void drawPixels(Vector<bool>& pixels, const int nRows, const int nCols)
{
	for (int i = 0; i < nRows; ++i)
	{
		for (int j = 0; j < nCols; ++j)
		{
			char ch = pixels[j + i * nCols] ? '+' : '-';
			std::cout << ch << ' ';
		}
		std::cout << std::endl;
	}
}

bool isDuplicate(Vector<bool>& nQueen, const int idx, const int N)
{
	int col = idx % N;
	int row = idx / N;
	//	縦横
	for (int i = 0; i < N; ++i)
	{
		if (nQueen[i + row * N])return true;
		if (nQueen[col + i * N])return true;
	}

	//	斜め
	for (int i = col, j = row; i >= 0 && j >= 0; --i, --j) { if (nQueen[i + j * N]) return true; }
	for (int i = col, j = row; i < N && j >= 0; ++i, --j) { if (nQueen[i + j * N]) return true; }
	for (int i = col, j = row; i < N && j < N; ++i, ++j) { if (nQueen[i + j * N]) return true; }
	for (int i = col, j = row; i >= 0 && j < N; --i, ++j) { if (nQueen[i + j * N]) return true; }

	return false;
}


