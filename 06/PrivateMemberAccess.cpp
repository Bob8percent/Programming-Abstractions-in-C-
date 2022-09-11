
//  クラスメソッドは、そのクラスの任意のオブジェクトの変数を参照できる(Privateであっても)
//  つまり、Privateは、違うオブジェクト間ではなく、違うクラス間に対してアクセスを制限するものである

#include <iostream>

class Point
{
public:
	Point(int xc, int yc)
	{
		x = xc;
		y = yc;
	}

	bool operator==(Point rhs)
	{
		return (x == rhs.x) && (y == rhs.y);
	}

private:
	int x, y;
};

int main()
{
	Point a(1, 2), b(1, 2);

	std::cout << std::boolalpha << (a == b) << std::endl;
}
