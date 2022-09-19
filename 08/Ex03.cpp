#include <iostream>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"
#include "Library/stack.h"

void moveTower(int n, Stack<int>& start, Stack<int>& finish, Stack<int>& tmp);

int main()
{
	int n = 10;
	Stack<int> start;
	for (int i = n; i >= 1; --i) start.push(i);
	Stack<int> finish;
	Stack<int> tmp;
	moveTower(n, start, finish, tmp);

	std::cout << std::boolalpha << start.isEmpty() << std::endl;
	while (!finish.isEmpty())
	{
		std::cout << finish.pop() << " ";
	}
	std::cout << std::endl << std::boolalpha << tmp.isEmpty() << std::endl;
}

void moveTower(int n, Stack<int>& start, Stack<int>& finish, Stack<int>& tmp)
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
	}
	else
	{
		//	1~n-1をstartからtmpに移動
		moveTower(n - 1, start, tmp, finish);
		//	nをstartからfinishに移動
		finish.push(start.pop());
		//	1~n-1をtmpからfinishに移動
		moveTower(n - 1, tmp, finish, start);
	}

}
