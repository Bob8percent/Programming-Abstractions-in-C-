#pragma once

#include <string>

enum Month
{
	JANUARY = 1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
};

int daysInMonth(int year, Month month);

bool isLeapYear(int year);

std::string monthToString(Month month);
