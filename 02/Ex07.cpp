
/*
* 逐次近似法による平方根を求めるプログラム
*/

#include <iostream>
#include <iomanip>

double my_sqrt(double x);

int main()
{
	const int sentinel = 0;

	while (1)
	{
		int n = 0;
		std::cout << "入力：";
		std::cin >> n;
		
		std::cout << "平方根：" << my_sqrt(n) << "\n";
	}
}

double my_sqrt(double x)
{
	double result = x;

	while (1)
	{
		double average = (result + x / result) / 2;
		
		if (average == result)	
		{
			//	なぜこれが終了条件になるかは、averageとresultがint型であることを想定すればわかりやすい。
			//	これらがint型でx=2のとき、averageもresultも1で変化しない
			break;
		}

		result = average;
	}

	return result;
}
