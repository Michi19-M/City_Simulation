#include "Date.h"
#include <iostream>

Date::Date(unsigned day, unsigned month, unsigned year)
{
	setYear(year);
	setMonth(month);
	setDay(day);
}

unsigned Date::getDay() const
{
	return day;
}

unsigned Date::getMonth() const
{
	return month;
}

unsigned Date::getYear() const
{
	return year;
}

void Date::setDay(unsigned day)
{
	if (day == this->day)
		return;

	if (day == 0 || day > MAX_DAYS[month - 1])
		day = 1;
	this->day = day;
}

void Date::setMonth(unsigned month)
{
	if (month == this->month)
		return;

	if (month == 0 || month > 12)
		month = 1;

	this->month = month;
	setDay(getDay());
}

void Date::setYear(unsigned year)
{
	if (year == this->year)
		return;
	
	this->year = year;
	
	if (isLeapYear())
		MAX_DAYS[1] = 29;
	else
		MAX_DAYS[1] = 28;

	setDay(getDay());
}

void Date::goToNextDay()
{
	if (year == 1916 && month == 3 && day == 31) {
		setDay(14);
		setMonth(4);
		return;
	}

	setDay(getDay() + 1);

	if (day == 1)
	{
		setMonth(getMonth() + 1);
		if (month == 1)
			setYear(getYear() + 1);
	}
}

void Date::print() const
{
	std::cout << day << "." << month << "." << year << std::endl;
}

bool Date::isLeapYear() const
{
	if (year <= 1916)
		return year % 4 == 0;
	else
		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool operator==(const Date& lhs, const Date& rhs)
{
	return lhs.getDay() == rhs.getDay() &&
		lhs.getMonth() == rhs.getMonth() &&
		lhs.getYear() == rhs.getYear();
}

bool operator!=(const Date& lhs, const Date& rhs)
{
	return !(lhs == rhs);
}
