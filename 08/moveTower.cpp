#include <iostream>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"

void moveTower(int n, char start, char finish, char tmp);

int main()
{
	moveTower(3, 'A', 'B', 'C');
}

//	nはディスクの数。ディスク番号とは無関係であることに注意
void moveTower(int n, char start, char finish, char tmp)
{
	if (n <= 0)
	{
		std::cerr << "ERROR : void moveTower(int n, char start, char finish, char tmp) : "
			<< "nが負です" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	else if (n == 1)
	{
		//	startからfinishに移動
		std::cout << "[ " << start << " >> " << finish << " ]";
	}
	else
	{
		//	上n-1個をstartからtmpに移動
		moveTower(n - 1, start, tmp, finish);
		//	最下のディスクをstartからfinishに移動
		std::cout << "[ " << start << " >> " << finish << " ]";	// moveTower(1, count)でもOK
		//	上n-1個をtmpからfinishに移動
		moveTower(n - 1, tmp, finish, start);
	}

}
