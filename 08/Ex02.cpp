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
	moveTower(2, 'A', 'B', 'C');
}

void moveTower(int n, char start, char finish, char tmp)
{
	if (n < 0)
	{
		std::cerr << "ERROR : void moveTower(int n, char start, char finish, char tmp) : "
			<< "nが負です" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	else if (n == 0)
	{
		return;

		//	1をstartからfinishに移動
		//std::cout << "[ " << 1 << " : " << start << " >> " << finish << " ]";
	}
	else
	{
		//	1~n-1をstartからtmpに移動
		moveTower(n - 1, start, tmp, finish);
		//	nをstartからfinishに移動
		std::cout << "[ " << n << " : " << start << " >> " << finish << " ]";
		//	1~n-1をtmpからfinishに移動
		moveTower(n - 1, tmp, finish, start);
	}

}
