#include "Teacher.h"
#include <fstream>

Teacher::Teacher(const std::string& name, int happines, int money, int lifePoints, int salary) 
	: Citizen(name, happines, money, lifePoints)
{
	setSalary(salary);
}

void Teacher::monthlyUpdate()
{
	characteristics.money += salary;
	characteristics.happiness = std::min(characteristics.happiness + 1, 100);
}

void Teacher::save(std::ostream& out) const
{
	out << "Teacher" << ' ';
	Citizen::saveBase(out);
}

Citizen* Teacher::load(std::istream& in)
{
	std::string name;
	int happiness, money, life, salary;

	in >> name >> happiness >> money >> life >> salary;

	return new Teacher(name, happiness, money, life, salary);
}

void Teacher::setSalary(int salary)
{
	if (salary >= 1200 && salary <= 1300)
		this->salary = salary;
	else
		this->salary = 1200;
}

