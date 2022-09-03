
/*
* nPkを求めるプログラム
*/

#include <iostream>
#include <iomanip>

long long permutations(int n, int k);

int main()
{
	const int sentinel = -1;

	while (1)
	{
		int n = 0, k = 0;
		std::cout << "n：";
		std::cin >> n;
		std::cout << "k：";
		std::cin >> k;

		if (n == sentinel && k == sentinel)
		{
			break;
		}
		
		std::cout << "P(n, k)：" << permutations(n, k) << "\n";
	}
}

long long permutations(int n, int k)
{
	if (n < 0 || k < 0||n<k)
	{
		std::cerr << "不適な値入力で計算できません\n";
		return -1;
	}

	long long result = 1;
	for (int i = 0; i < k; ++i, --n)
	{
		result *= n;
	}

	return result;
}
