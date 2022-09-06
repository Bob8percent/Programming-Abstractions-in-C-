
/*
* 正弦余弦を表示するプログラム
*/

//　visual studioでM_PIを使うためのdefine
#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>
#include "String.h"

void sincosTable();

int main()
{
	sincosTable();
}

void sincosTable()
{
	std::cout << " theta | sin(theta) | cos(theta) |" << std::endl;
	std::cout << "-------+------------+------------+" << std::endl;
	std::cout << std::setprecision(7) << std::fixed;
	for (int theta = -90; theta <= 90; theta += 15)
	{

		//	sin, cosについて、setprecisionで小数点の桁数は、
		//	最大で-がついた10桁とわかるので、前にsetw(10)を指定すればよい。
		//	setwの数は、小数点の場合、最後の桁から数えた数。
		double radian = M_PI * theta / 180.0;
		std::cout << std::setw(5) << theta << "  | "
			<< std::setw(10) << std::sin(radian) << " | "
			<< std::setw(10) << std::cos(radian) << " |" << std::endl;
	}
}
