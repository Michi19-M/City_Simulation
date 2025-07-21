#include "Miner.h"
#include <fstream>

Miner::Miner(const std::string& name, int happines, int money, int lifePoints, int salary)
	: Citizen(name, happines, money, lifePoints)
{
	setSalary(salary);
}

void Miner::monthlyUpdate()
{
	characteristics.money += salary;
	characteristics.life = std::max(0, characteristics.life - 1);
}

void Miner::save(std::ostream& out) const
{
	out << "Miner" << ' ';
	Citizen::saveBase(out);
}

Citizen* Miner::load(std::istream& in)
{
	std::string name;
	int happiness, money, life, salary;

	in >> name >> happiness >> money >> life >> salary;

	return new Miner(name, happiness, money, life, salary);
}

void Miner::setSalary(int salary)
{
	if (salary >= 1000 && salary <= 3000)
		this->salary = salary;
	else
		this->salary = 1000;
}
