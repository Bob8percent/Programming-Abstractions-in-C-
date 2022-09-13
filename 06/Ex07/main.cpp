
#include <iostream>
#include "LabelGenerator.h"

int main()
{
	LabelGenerator figureNumbers("Figure ", 1);
	LabelGenerator pointNumbers("P", 0);

	std::cout << "Figure Numbers: ";
	for (int i = 0; i < 3; ++i)
	{
		if (i > 0)std::cout << ", ";
		std::cout << figureNumbers.nextLabel();
	}

	std::cout << std::endl << "Point Numbers: ";
	for (int i = 0; i < 3; ++i)
	{
		if (i > 0)std::cout << ", ";
		std::cout << pointNumbers.nextLabel();
	}

	std::cout << std::endl << "Figure Numbers: ";
	for (int i = 0; i < 3; ++i)
	{
		if (i > 0)std::cout << ", ";
		std::cout << figureNumbers.nextLabel();
	}
}
