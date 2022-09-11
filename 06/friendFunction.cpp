
//  friendは、自由関数にプライベート変数へのアクセス権を与えるもの。クラスから指定する。
//  また、friend関数に必要なアクセス権(下の==の場合PointとPoint2)をすべて満たさないと不適 … PointとPoint2からのfriend指定が必要

#include <iostream>

class Point2;

class Point
{
public:
	Point(int xc, int yc)
	{
		x = xc;
		y = yc;
	}

	friend bool operator==(Point p, Point2 p2);

private:
	int x, y;
};

class Point2
{
public:
	Point2(int xc, int yc)
	{
		x = xc;
		y = yc;
	}

	friend bool operator==(Point p, Point2 p2);
private:
	int x, y;
};

bool operator==(Point p, Point2 p2)
{
	return (p.x == p2.x) && (p.y == p2.y);
}


int main()
{
	Point p(1, 2);
	Point2 p2(1, 2);

	std::cout << std::boolalpha << (p == p2) << std::endl;
}
