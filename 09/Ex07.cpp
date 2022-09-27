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

//	top-bottom方向にcubeを積み重ねていき、側面の色を見る
//	対称性を考慮して探索回数を24^4回から3*(24 or 16)^3回に減らした(33万回から1~4万回へ)
//	参考：https://www.ams.org/journals/mcom/1975-29-129/S0025-5718-1975-0373371-6/S0025-5718-1975-0373371-6.pdf

enum Color { R, G, B, W };
struct Cube
{
	Cube(Color _top, Color _bottom, Color _front, Color _back, Color _left, Color _right)
	{
		top = _top;
		bottom = _bottom;
		front = _front;
		back = _back;
		left = _left;
		right = _right;
	}

	union
	{
		Color faces[6];

		struct
		{
			Color top, bottom, front, back, left, right;
		};
	};
};

bool solveInstantInsanity(Vector<Cube>& cubes);
bool solveInstantInsanity(Vector<Cube>& cubes, int level);

bool rotateCheck(Vector<Cube>& cubes, int level);

bool isSameColor(const Cube& cube);

bool isSolved(Vector<Cube>& cubes);

//	right-left方向に回転
void rotateX(Cube& cube, bool isClockwise = false);
//	top-bottom方向に回転
void rotateY(Cube& cube, bool isClockwise = false);
//	front-back方向に回転
void rotateZ(Cube& cube, bool isClockwise = false);

std::ostream& operator<<(std::ostream& os, const Color& rhs);

int main()
{
	Vector<Cube> cubes;
	//	case.1 : true
	//cubes += Cube(G, G, B, W, B, R);
	//cubes += Cube(R, G, G, W, W, B);
	//cubes += Cube(W, G, W, R, R, B);
	//cubes += Cube(B, W, R, G, R, R);

	//	case.2 : true
	//cubes += Cube(B, W, G, R, W, R);
	//cubes += Cube(R, B, B, W, W, G);
	//cubes += Cube(G, R, W, G, B, B);
	//cubes += Cube(W, G, R, B, R, R);

	//	case.3 : false
	cubes += Cube(B, B, R, W, R, G);
	cubes += Cube(R, R, G, B, W, G);
	cubes += Cube(R, R, G, B, W, G);
	cubes += Cube(G, G, R, W, B, R);

	std::cout << std::boolalpha << solveInstantInsanity(cubes) << std::endl;

	for (int i = 0; i < cubes.size(); ++i)
	{
		for (int face = 0; face < 6; ++face)
		{
			std::cout << cubes[i].faces[face];
		}
		std::cout << std::endl;
	}
}

bool solveInstantInsanity(Vector<Cube>& cubes)
{
	return solveInstantInsanity(cubes, 0);
}

bool solveInstantInsanity(Vector<Cube>& cubes, int level)
{
	if (isSolved(cubes))return true;

	if (level == 4)return false;

	Cube& c = cubes[level];

	if (level == 0)
	{
		//	一つ目のcubeは3通りのみ考えればよい
		if (solveInstantInsanity(cubes, level + 1))return true;

		rotateX(c);
		if (solveInstantInsanity(cubes, level + 1))return true;
		rotateX(c, true);

		rotateZ(c);
		if (solveInstantInsanity(cubes, level + 1))return true;
		rotateZ(c, true);
	}
	else
	{
		if (rotateCheck(cubes, level))return true;

		rotateX(c);
		if (rotateCheck(cubes, level))return true;
		rotateX(c, isSameColor(c));	//	反転を考慮

		rotateZ(c);
		if (rotateCheck(cubes, level))return true;
		rotateZ(c, isSameColor(c));	//	反転を考慮
	}

	return false;
}

bool rotateCheck(Vector<Cube>& cubes, int level)
{
	Cube& c = cubes[level];

	for (int i = 0; i < 4; ++i)
	{
		if (solveInstantInsanity(cubes, level + 1))return true;
		rotateY(c);
	}
	if (!isSameColor(c))	//	側面について向かいの面が同色のときは対称性よりtop-bottomを反対にする場合を確認する必要ない
	{
		rotateX(c);
		rotateX(c);
		for (int i = 0; i < 4; ++i)
		{
			if (solveInstantInsanity(cubes, level + 1))return true;
			rotateY(c);
		}
	}

	return false;
}

bool isSolved(Vector<Cube>& cubes)
{
	for (int face = 2; face < 6; ++face)
	{
		Set<Color> colors;
		for (int i = 0; i < cubes.size(); ++i)
		{
			colors += cubes[i].faces[face];
		}
		if (colors.size() != 4)return false;
	}
	return true;
}

//	right-leftまたは、front-backの面の色が同じかどうか
bool isSameColor(const Cube& cube)
{
	return (cube.right == cube.left) || (cube.front == cube.back);
}

//	right-left方向に回転
void rotateX(Cube& cube, bool isClockwise)
{
	Cube tmp = cube;
	if (isClockwise)
	{
		cube.front = tmp.bottom;
		cube.bottom = tmp.back;
		cube.back = tmp.top;
		cube.top = tmp.front;
	}
	else
	{
		cube.front = tmp.top;
		cube.bottom = tmp.front;
		cube.back = tmp.bottom;
		cube.top = tmp.back;
	}
}

//	top-bottom方向に回転
void rotateY(Cube& cube, bool isClockwise)
{
	Cube tmp = cube;
	if (isClockwise)
	{
		cube.front = tmp.right;
		cube.right = tmp.back;
		cube.back = tmp.left;
		cube.left = tmp.front;
	}
	else
	{
		cube.front = tmp.left;
		cube.right = tmp.front;
		cube.back = tmp.right;
		cube.left = tmp.back;
	}
}

//	front-back方向に回転
void rotateZ(Cube& cube, bool isClockwise)
{
	Cube tmp = cube;
	if (isClockwise)
	{
		cube.bottom = tmp.right;
		cube.right = tmp.top;
		cube.top = tmp.left;
		cube.left = tmp.bottom;
	}
	else
	{
		cube.bottom = tmp.left;
		cube.right = tmp.bottom;
		cube.top = tmp.right;
		cube.left = tmp.top;
	}
}

std::ostream& operator<<(std::ostream& os, const Color& rhs)
{
	switch (rhs)
	{
	case R:
		return os << 'R';
	case G:
		return os << 'G';
	case W:
		return os << 'W';
	case B:
		return os << 'B';
	default:
		break;
	}

	return os << '-';
}
