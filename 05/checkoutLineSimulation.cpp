
/*
* getReal()の実装
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
	int& queueSum,
	int& waitingTimeSum,
	int& customerServed
);

int main()
{
	std::cout << "シミュレーション時間：";
	int simulationTime = getInteger(std::cin);
	std::cout << "到着確率：";
	double arrivalProbability = getReal(std::cin);
	std::cout << "一人あたりの対応時間の最小値：";
	int minServiceTime = getInteger(std::cin);
	std::cout << "一人当たりの対応時間の最大値：";
	int maxServiceTime = getInteger(std::cin);

	int queueSum = 0;
	int waitingTimeSum = 0;
	int customerServed = 0;
	checkoutLineSimulation(arrivalProbability, minServiceTime, maxServiceTime, simulationTime,
		queueSum, waitingTimeSum, customerServed);

	std::cout << "Customer Served : " << customerServed << std::endl
		<< "Average waiting time : " << waitingTimeSum / double(customerServed) << std::endl
		<< "Average queue length : " << queueSum / double(simulationTime) << std::endl;

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
	int& queueSum,
	int& waitingTimeSum,
	int& customerServed
)
{
	int remainingTime = 0;
	Queue<int> customerQueue;

	for (int t = 0; t < simulationTime; ++t)
	{
		if (randCheck(arrivalProbability))
		{
			customerQueue.enqueue(t);
		}

		if (remainingTime > 0)
		{
			--remainingTime;
		}
		else if(!customerQueue.isEmpty())
		{
			waitingTimeSum += (t - customerQueue.dequeue());
			++customerServed;
			remainingTime = randInteger(minServiceTime, maxServiceTime);
		}

		queueSum += customerQueue.size();
	}
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
