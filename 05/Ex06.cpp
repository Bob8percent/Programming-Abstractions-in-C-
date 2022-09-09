int main()
{
	//	エラストテネスのふるい
	bool prime[10000];
	for (int n = 0; n < 10000; ++n)
	{
		prime[n] = true;
	}
	for (int n = 2; n * n <= 1000; ++n)
	{
		//	nの倍数に×をつける
		for (int m = n * 2; m <= 1000; m += n)
		{
			prime[m] = false;
		}
	}
	for (int n = 2; n <= 1000; ++n)
	{
		if (prime[n])
		{
			std::cout << n << ", ";
		}
	}
	std::cout << std::endl;
}
