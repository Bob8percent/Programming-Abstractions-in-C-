#include "calender.h"
#include <iostream>
#include <sstream>

int daysInMonth(int year, Month month)
{
	int days = -1;
	switch (month)
	{
	case FEBRUARY:
		days = (isLeapYear(year) ? 29 : 28);
		break;

	case JANUARY:
	case MARCH:
	case MAY:
	case JULY:
	case AUGUST:
	case OCTOBER:
	case DECEMBER:
		days = 31;
		break;
		
	case APRIL:
	case JUNE:
	case SEPTEMBER:
	case NOVEMBER:
		days = 30;
		break;

	default:
		break;
	}

	return days;
}

bool isLeapYear(int year)
{
	return(year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

std::string monthToString(Month month)
{
	std::string str;

	switch (month)
	{
	case FEBRUARY:
		str = "FEBRUARY";;
		break;
	case JANUARY:
		str = "JANUARY";;
		break;
	case MARCH:
		str = "MARCH";;
		break;
	case MAY:
		str = "MAY";;
		break;
	case JULY:
		str = "JULY";;
		break;
	case AUGUST:
		str = "AUGUST";;
		break;
	case OCTOBER:
		str = "OCTOBER";;
		break;
	case DECEMBER:
		str = "DECEMBER";;
		break;
	case APRIL:
		str = "APRIL";;
		break;
	case JUNE:
		str = "JUNE";;
		break;
	case SEPTEMBER:
		str = "SEPTEMBER";;
		break;
	case NOVEMBER:
		str = "NOBEMBER";;
		break;
	default:
		break;
	}

	return str;
}

Date::Date()
{
	mYear = 1900;
	mMonth = JULY;
	mDay = 1;
}

Date::Date(Month month, int day, int year)
{
	if (!(1 <= day && day <= daysInMonth(year, month)))
	{
		std::cerr << "ERROR : Date::Date(Month month, int day, int year) : "
			<< "dayが不適な値です" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	mYear = year;
	mMonth = month;
	mDay = day;
}

Date::Date(int day, Month month, int year)
{
	if (!(1 <= day && day <= daysInMonth(year, month)))
	{
		std::cerr << "ERROR : Date::Date(int day, Month month, int year) : "
			<< "dayが不適な値です" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	mYear = year;
	mMonth = month;
	mDay = day;
}

int Date::getDay() const
{
	return mDay;
}

Month Date::getMonth() const
{
	return mMonth;
}

int Date::getYear() const
{
	return mYear;
}

std::string Date::toString() const
{
	std::string ms = monthToString(mMonth).substr(0, 3);
	ms[1] = tolower(ms[1]);
	ms[2] = tolower(ms[2]);

	std::ostringstream oss;
	oss << mDay << "-" << ms << "-" << mYear;

	return oss.str();
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
	return os << date.toString();
}
