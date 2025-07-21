#include "Unemployed.h"
#include <fstream>

Unemployed::Unemployed(const std::string& name, int happines, int money, int lifePoints, int salary)
	: Citizen(name, happines, money, lifePoints)
{
	setSalary(salary);
}

void Unemployed::monthlyUpdate()
{
	characteristics.life = std::max(0, characteristics.life - 1);
}

void Unemployed::save(std::ostream& out) const
{
	out << "Unemployed" << ' ';
	Citizen::saveBase(out);
}

Citizen* Unemployed::load(std::istream& in)
{
	std::string name;
	int happiness, money, life, salary;

	in >> name >> happiness >> money >> life >> salary;

	return new Unemployed(name, happiness, money, life, salary);
}

void Unemployed::setSalary(int salary)
{
	this->salary = 0;
}
