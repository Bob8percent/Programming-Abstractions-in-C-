
/*
* 1~100までの素数をすべて表示するプログラム
*/

#include <iostream>
#include <iomanip>

bool isPrime(int n);

int main()
{
	std::cout << "1~100のうち素数は、";
	for (int n = 2; n <= 100; ++n)
	{
		if (isPrime(n))
		{
			std::cout << "[" << n << "] ";
		}
	}
	std::cout << "\n";
}

bool isPrime(int n)
{
	for (int d = 2; d * d <= n; ++d)
	{
		if (n % d == 0)
		{
			return false;
		}
	}

	return true;
}
