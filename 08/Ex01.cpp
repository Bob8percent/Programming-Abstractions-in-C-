#include <iostream>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"

int countHanoiMoves(int n);
void moveTower(int n, int& count);

int main()
{
	std::cout << std::setw(3) << "n" << std::setw(20) << "countHanoiMoves" << std::endl << std::endl;

	for (int i = 1; i <= 10; ++i)
	{
		std::cout << std::setw(3) << i << std::setw(15) << countHanoiMoves(i) << std::endl;
	}
}

int countHanoiMoves(int n)
{
	int count = 0;
	moveTower(n, count);
	return count;
}

void moveTower(int n, int& count)
{
	++count;
	if (n <= 0)
	{
		std::cerr << "ERROR : void moveTower(int n, char start, char finish, char tmp) : "
			<< "nが負です" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	else if (n == 1)
	{
		//	1をstartからfinishに移動
		//std::cout << "[ " << 1 << " : " << start << " >> " << finish << " ]";
	}
	else
	{
		//	1~n-1をstartからtmpに移動
		moveTower(n - 1, count);
		//	nをstartからfinishに移動
		//std::cout << "[ " << n << " : " << start << " >> " << finish << " ]";
		//	1~n-1をtmpからfinishに移動
		moveTower(n - 1, count);
	}

}
