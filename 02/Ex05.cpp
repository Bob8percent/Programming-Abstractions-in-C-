
/*
* 1~9999の範囲の完全数をすべて表示するプログラム
*/

#include <iostream>
#include <iomanip>

bool isPerfect(int n);

int main()
{
	std::cout << "1~9999のうち完全数は、";
	for (int n = 1; n <= 9999; ++n)
	{
		if (isPerfect(n))
		{
			std::cout << "[" << n << "] ";
		}
	}
	std::cout << "\n";
}

bool isPerfect(int n)
{
	int sum = 0;
	for (int d = 1; d < n; ++d)
	{
		if (n % d == 0)
		{
			sum += d;
		}
	}

	return sum == n;
}
