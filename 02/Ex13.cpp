
/*
* 各年に残っている原子の数を表示するプログラム
* ただし半減期は1年とする
*/

#include <iostream>
#include <iomanip>

bool randomChance(double p);
void initRand();

int main()
{
	const int sentinel = -1;

	while (1)
	{
		std::cout << "原子数の初期値：";
		int n = -1;
		std::cin >> n;

		if (n == sentinel)
		{
			break;
		}
		
		int timeCount = 1;
		int currentNumAtoms = n;
		while (currentNumAtoms > 0)
		{
			std::cout << timeCount << "年後の原子数：";
			for (int i = 0; i < n; ++i)
			{
				if (randomChance(0.5))
				{
					//	原子崩壊
					--currentNumAtoms;
				}
			}
			std::cout << currentNumAtoms << "\n";
			
			n = currentNumAtoms;
			++timeCount;
		}
	}
}

bool randomChance(double p)
{
	initRand();

	return (rand() / (RAND_MAX * 1.0)) <= p;
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
