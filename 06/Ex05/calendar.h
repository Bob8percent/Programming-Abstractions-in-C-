#pragma once

#include <string>
#include <ostream>

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

class Date
{
public:
	Date();
	Date(Month month, int day, int year);
	Date(int day, Month month, int year);

	int getDay() const;
	Month getMonth() const;
	int getYear() const;

	std::string toString() const;

private:
	int mYear;
	Month mMonth;
	int mDay;
};

std::ostream& operator<<(std::ostream& os, const Date& date);
