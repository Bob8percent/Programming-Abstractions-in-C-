#include "calendar.h"

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
