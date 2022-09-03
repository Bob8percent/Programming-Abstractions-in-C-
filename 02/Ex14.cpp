
/*
* モンテカルロ法によりpiを導出するプログラム
*/

#include <iostream>
#include <iomanip>

double randomReal(double a, double b);	//	a以上b以下のランダムな値を返す
double calcPI(int n);
void initRand();

int main()
{
	const int sentinel = -1;

	while (1)
	{
		std::cout << "試行回数：";
		int n = -1;
		std::cin >> n;

		if (n == sentinel)
		{
			break;
		}
		
		std::cout << "PIの近似値：" << calcPI(n) << "\n";
	}
}

double calcPI(int n)
{
	int numInsideCircle = 0;
	for (int i = 0; i < n; ++i)
	{
		double x = randomReal(-1, 1);
		double y = randomReal(-1, 1);
		if ((x * x + y * y) < 1)
		{
			++numInsideCircle;
		}
	}

	return 4.0 * numInsideCircle / (n * 1.0);
}

double randomReal(double a, double b)
{
	initRand();

	return a + (b - a) * (rand() / (RAND_MAX * 1.0));
}

void initRand()
{
	static bool isFirst = true;
	if (isFirst)
	{
		srand((int)time(NULL));
		isFirst = false;
	}
}
