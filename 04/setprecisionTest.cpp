
/*
* setprecisionマニピュレータの挙動を確認する
*/

#include <iostream>
#include <iomanip>
#include <string>
#include "String.h"

using std::setprecision;
const double PI = 3.14159265358979323846;
const double SPEED_OF_LIGHT = 2.99792458e+8;
const double FINE_STRUCTURE = 7.2573525e-3;

void printPrecisionTable();

int main()
{
  //  デフォルト
	std::cout << "Default format:" << std::endl << std::endl;
	printPrecisionTable();

  //  fixed状態のsetprecision
	std::cout << std::endl << "Fixed format:" << std::fixed << std::endl << std::endl;
	printPrecisionTable();

  //  scientific状態の
	std::cout << std::endl << "Scientific format:" << std::scientific << std::endl << std::endl;
	printPrecisionTable();
}

void printPrecisionTable()
{
	for (int precision = 0; precision <= 6; precision += 2)
	{
		std::cout << "setprecision(" << precision << ")の場合、" << std::endl;
		std::cout << "PI : " << setprecision(precision) << PI << std::endl;
		std::cout << "SPEED_OF_LIGHT : " << setprecision(precision) << SPEED_OF_LIGHT << std::endl;
		std::cout << "FINE_STRUCTURE : " << setprecision(precision) << FINE_STRUCTURE << std::endl;
	}
}
