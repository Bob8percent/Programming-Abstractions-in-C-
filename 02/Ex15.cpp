
/*
* コインをなげてn回連続で表が出たら終了するプログラム
*/

#include <iostream>
#include <iomanip>

bool randomChance(double p);
void initRand();

int main()
{
	const int numConsecutive = 3;	//	numHeadsの最大値

	int numHeads = 0;	//	連続で表が出た回数
	int count = 0;		//	試行回数
	
	while (numHeads < numConsecutive)
	{
		if (randomChance(0.5))
		{
			std::cout << "表がでた\n";
			++numHeads;
		}
		else
		{
			std::cout << "裏がでた\n";
			numHeads = 0;
		}

		++count;
	}

	std::cout << numConsecutive << "回連続で表が出るまで" << count << "回かかった\n";
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
