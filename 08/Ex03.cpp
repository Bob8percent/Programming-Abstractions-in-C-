#include <iostream>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"
#include "Library/stack.h"

struct Task
{
	int n;	//	startからfinishへ移動させるディスクの数
	char start;
	char finish;
	char tmp;
};

void moveTower(Task& task);

int main()
{
	Task task = { 3,'A','B','C' };
	moveTower(task);
}

void moveTower(Task& task)
{
	Stack<Task> tasks;
	tasks.push(task);
	while (!tasks.isEmpty())
	{
		Task currentTask = tasks.pop();
		
		if (currentTask.n <= 0)
		{
			std::cerr << "ERROR : void moveTower(int n, char start, char finish, char tmp) : "
				<< "nが負です" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		else if (currentTask.n == 1)
		{
			//	1をstartからfinishに移動
			std::cout << "[ " << currentTask.start << " >> " << currentTask.finish << " ]";
		}
		else
		{
			//	1~n-1をstartからtmpに移動するタスク
			Task t1 = { currentTask.n - 1,currentTask.start,currentTask.tmp,currentTask.finish };
			//	nをstartからfinishに移動する
			Task t2 = { 1,currentTask.start,currentTask.finish,currentTask.tmp };
			//	1~n-1をtmpからfinishに移動するタスク
			Task t3 = { currentTask.n - 1,currentTask.tmp,currentTask.finish,currentTask.start };

			//	処理の順番はt1から
			tasks.push(t3);
			tasks.push(t2);
			tasks.push(t1);
		}
	}

}
