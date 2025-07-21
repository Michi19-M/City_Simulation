#include "Programmer.h"
#include <fstream>

Programmer::Programmer(const std::string& name, int happines, int money, int lifePoints, int salary)
	: Citizen(name, happines, money, lifePoints)
{
	setSalary(salary);
}

void Programmer::monthlyUpdate()
{
	characteristics.money += salary;
	characteristics.happiness = std::max(0, characteristics.happiness - 1);
}

void Programmer::save(std::ostream& out) const
{
	out << "Programmer" << ' ';
	Citizen::saveBase(out);
}

Citizen* Programmer::load(std::istream& in)
{
	std::string name;
	int happiness, money, life, salary;

	in >> name >> happiness >> money >> life >> salary;

	return new Programmer(name, happiness, money, life, salary);
}

void Programmer::setSalary(int salary)
{
	if (salary >= 2000 && salary <= 5000)
		this->salary = salary;
	else
		this->salary = 2000;
}
