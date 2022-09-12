#include "GRectangle.h"

#include <iostream>

int main()
{
	GRectangle a(2, 3, 10, 5);

	std::cout << std::boolalpha << a.contains(5, 5) << std::endl;
}
