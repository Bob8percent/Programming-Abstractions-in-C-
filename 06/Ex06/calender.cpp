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
		str = "NOVEMBER";;
		break;
	default:
		break;
	}

	return str;
}

Month& operator++(Month& month)
{
	//int nextMonth = ((month + 1) % 12);
	//if (nextMonth == 0)nextMonth = 12;
	month = Month(month + 1);
	return month;
}

Month& operator--(Month& month)
{
	month = Month(month - 1);
	return month;
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

bool Date::operator==(const Date& rhs)
{
	return (mYear == rhs.mYear)
		&& (mMonth == rhs.mMonth)
		&& (mDay == rhs.mDay);
}

bool Date::operator!=(const Date& rhs)
{
	return !(*this == rhs);
}

bool Date::operator>(const Date& rhs)
{
	if (mYear != rhs.mYear)
	{
		return mYear > rhs.mYear;
	}
	else
	{
		if (mMonth != rhs.mMonth)
		{
			return mMonth > rhs.mMonth;
		}
		else
		{
			return mDay > rhs.mDay;
		}
	}
}

bool Date::operator>=(const Date& rhs)
{
	return !(*this < rhs);
}

bool Date::operator<(const Date& rhs)
{
	return (*this <= rhs) && (*this != rhs);
}
bool Date::operator<=(const Date& rhs)
{
	return !(*this > rhs);
}

int Date::operator-(const Date& rhs)
{
	if (*this == rhs)return 0;

	Date d = rhs;
	int count = 0;
	Date highDate = (*this > d) ? *this : d;
	Date lowDate = (*this < d) ? *this : d;
	while (1)
	{
		--count;
		if (highDate == (++lowDate))break;
	}

	return count;
}

Date Date::operator+(int n)
{
	Date temp = *this;
	temp += n;
	return temp;
}

Date Date::operator-(int n)
{
	Date temp = *this;
	temp -= n;
	return temp;
}

Date& Date::operator+=(int n)
{
	while (n--)
	{
		++(*this);
	}

	return *this;
}

Date& Date::operator-=(int n)
{
	while (n--)
	{
		--(*this);
	}

	return *this;
}

Date Date::operator++(int)
{
	Date temp = *this;
	++(*this);
	return temp;
}

Date& Date::operator++()
{
	if (mDay == daysInMonth(mYear, mMonth))
	{
		mDay = 1;
		if ((++mMonth) == 13)
		{
			mMonth = JANUARY;
			++mYear;
		}
	}
	else
	{
		++mDay;
	}

	return *this;
}

Date Date::operator--(int)
{
	Date temp = *this;
	--(*this);
	return temp;
}

Date& Date::operator--()
{
	if (mDay == 1)
	{
		if ((--mMonth) == -1)
		{
			mMonth = DECEMBER;
			--mYear;
		}
		mDay = daysInMonth(mYear, mMonth);
	}
	else
	{
		--mDay;
	}

	return *this;
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
	return os << date.toString();
}
