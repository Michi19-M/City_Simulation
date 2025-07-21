#pragma once

class Date
{
public:
	Date(unsigned day, unsigned month, unsigned year);
	
	unsigned getDay() const;
	unsigned getMonth() const;
	unsigned getYear() const;

	void setDay(unsigned day);
	void setMonth(unsigned month);
	void setYear(unsigned year);

	void goToNextDay();

	void print() const;

private:
	bool isLeapYear() const;

private:
	unsigned MAX_DAYS[12] =
	{
		31,28,31,30,31,30,31,31,30,31,30,31
	};

	unsigned day = 1;
	unsigned month = 1;
	unsigned year = 1;
};


bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);