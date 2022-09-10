
/*
* checkoutLineSimulationの実装
*/

#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>
#include "String.h"
#include "Library/vector.h"
#include "Library/queue.h"

double getReal(std::istream& is);
int getInteger(std::istream& is);
bool randCheck(double prob);
double randReal(double low, double high);
int randInteger(int low, int high);
void initRand();

void checkoutLineSimulation(
	const double arrivalProbability,
	const int minServiceTime,
	const int maxServiceTime,
	const int simulationTime,
	const int nQueues,
	int& queueSum,
	int& waitingTimeSum,
	int& customerServed
);

int minSizeQueue(const Vector<Queue<int>>& queues);
int findNextQueue(const Vector<Queue<int>>& queues, int currentQueue);

int main()
{
	while (1)
	{
		std::cout << "シミュレーション時間：";
		int simulationTime = getInteger(std::cin);
		std::cout << "到着確率：";
		double arrivalProbability = getReal(std::cin);
		std::cout << "一人あたりの対応時間の最小値：";
		int minServiceTime = getInteger(std::cin);
		std::cout << "一人当たりの対応時間の最大値：";
		int maxServiceTime = getInteger(std::cin);
		std::cout << "列の数 : ";
		int nQueues = getInteger(std::cin);

		int queueSum = 0;
		int waitingTimeSum = 0;
		int customerServed = 0;
		initRand();
		srand(1);
		checkoutLineSimulation(arrivalProbability, minServiceTime, maxServiceTime, simulationTime,
			nQueues, queueSum, waitingTimeSum, customerServed);

		std::cout << "Customer Served : " << customerServed << std::endl
			<< "Average waiting time : " << double(waitingTimeSum) / customerServed << std::endl
			<< "Average queue length : " << queueSum / double(nQueues * simulationTime) << std::endl;
	}
}

double getReal(std::istream& is)
{
	while (1)
	{
		std::string str = "";
		std::getline(is, str);

		std::istringstream iss(str);
		double value;
		iss >> value >> std::skipws;

		if (!iss.fail() && iss.eof())
		{
			return value;
		}

		iss.clear();
		std::cout << "ERROR : double getReal(std::istream& is) : 入力結果を実数に変換できません" << std::endl;
	}
}

int getInteger(std::istream& is)
{
	while (1)
	{
		std::string str = "";
		std::getline(is, str);

		std::istringstream iss(str);
		int value;
		iss >> value >> std::skipws;

		if (!iss.fail() && iss.eof())
		{
			return value;
		}

		iss.clear();
		std::cout << "ERROR : int getIntger(std::istream& is) : 入力結果を整数に変換できません" << std::endl;
	}
}

void checkoutLineSimulation(
	const double arrivalProbability,
	const int minServiceTime,
	const int maxServiceTime,
	const int simulationTime,
	const int nQueues,
	int& queueSum,
	int& waitingTimeSum,
	int& customerServed
)
{
	Vector<int> remainingTime(nQueues, 0);
	Vector<Queue<int>> customerQueues(nQueues);
	queueSum = 0;
	waitingTimeSum = 0;
	customerServed = 0;
	for (int t = 0; t < simulationTime; ++t)
	{
		if (randCheck(arrivalProbability))
		{
			//	人が少ない列に客が並ぶ
			int idx = minSizeQueue(customerQueues);
			customerQueues[idx].enqueue(t);
		}

		for (int i = 0; i < customerQueues.size(); ++i)
		{
			if (remainingTime[i] > 0)
			{
				--remainingTime[i];
			}
			else
			{
				int d = findNextQueue(customerQueues, i);
				if (d != -1)
				{
					waitingTimeSum += (t - customerQueues[d].dequeue());
					++customerServed;
					remainingTime[i] = randomInteger(minServiceTime, maxServiceTime);
				}
			}
			queueSum += customerQueues[i].size();
		}
	}
}

int findNextQueue(const Vector<Queue<int>>& queues, int currentQueue)
{
	if (!queues[currentQueue].isEmpty())
	{
		return currentQueue;
	}
	else
	{
		for (int i = 0; i < queues.size(); ++i)
		{
			if (!queues[i].isEmpty())
			{
				return i;
			}
		}
	}

	return -1;
}

int minSizeQueue(const Vector<Queue<int>>& queues)
{
	int idx = 0;
	int size = queues[0].size();
	for (int i = 1; i < queues.size(); ++i)
	{
		int s = queues[i].size();
		if (size > s)
		{
			idx = i;
			size = s;
		}
	}
	return idx;
}

bool randCheck(double prob)
{
	return randReal(0, 1) <= prob;
}

double randReal(double low, double high)
{
	initRand();

	double ratio = rand() / double(RAND_MAX);	//	0<=ratio<=1
	return low + ratio * (high - low);
}

int randInteger(int low, int high)
{
	initRand();

	double ratio = rand() / (double(RAND_MAX) + 1);
	return low + int(std::floor(ratio * (high - low + 1)));
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
