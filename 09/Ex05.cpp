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

//　各列、各行にクイーンは必ず一つだけおかれることを利用して計算量を減らす
//　特定の行にあるクイーンの位置を特定するのに探索すべき数はN個だけ。ー＞N個のクイーンの位置はそれぞれN回の計算で特定できる
bool findQueenPos(Vector<bool>& nQueen, const int N);
bool findQueenPos(Vector<bool>& nQueen, int row, const int N);	//	各行ずつ探索 > 各マスずつ探索
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

	return findQueenPos(nQueen, 0, N);
}

bool findQueenPos(Vector<bool>& nQueen, int row, const int N)
{
	if (row == N)
	{
		return true;
	}

	//	row行の各列における場所を探す
	for (int i = 0; i < N; ++i)
	{
		int idx = i + row * N;
		if (!isDuplicate(nQueen, idx, N))
		{
			nQueen[idx] = true;
			if (findQueenPos(nQueen, row + 1, N))
			{
				return true;
			}
			nQueen[idx] = false;
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


