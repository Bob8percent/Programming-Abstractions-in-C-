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

//	nはディスクの数。ディスク番号とは無関係であることに注意
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
		//	startからfinishに移動
		//std::cout << "[ " << start << " >> " << finish << " ]";
	}
	else
	{
		//	上n-1個をstartからtmpに移動
		moveTower(n - 1, count);
		//	最下のディスクをstartからfinishに移動
		//std::cout << "[ " << start << " >> " << finish << " ]";	// moveTower(1, count)でもOK
		//	上n-1個をtmpからfinishに移動
		moveTower(n - 1, count);
	}

}
