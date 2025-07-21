#include "Citizen.h"
#include <iostream>

#include "Miner.h"
#include "Programmer.h"
#include "Teacher.h"
#include "Unemployed.h"

Citizen::Citizen(const std::string& name, int happines, int money, int lifePoints) 
	: name(name), salary(0), building(nullptr)
{
	characteristics.happiness = happines;
	characteristics.money = money;
	characteristics.life = lifePoints;
}

void Citizen::liveOneDay(bool isFirstDayOfMonth)
{
	characteristics.money -= 50;

	if (isFirstDayOfMonth) {
		payRent();
		monthlyUpdate();
	}
}

void Citizen::payRent()
{
	if (building) {
		characteristics.money -= building->getRent();
	}
}

void Citizen::print() const
{
	std::cout << "Name: " << name << "\n" << "Happiness: " << characteristics.happiness << '\n'
		<< "Money: " << characteristics.money << '\n' << "Life points: " << characteristics.life << '\n'
		<< "Salary: " << salary << '\n';
}

const std::string& Citizen::getName() const
{
	return name;
}

int Citizen::getHappines() const
{
	return characteristics.happiness;
}

int Citizen::getMoney() const
{
	return characteristics.money;
}

int Citizen::getLifePoints() const
{
	return characteristics.life;
}

int Citizen::getSalary() const
{
	return salary;
}

bool Citizen::setBuilding(Building* newBuilding)
{
	if (this->building)
		return false;

	this->building = newBuilding;
	return true;
}

bool Citizen::leaveBuilding()
{
	if (!building)
		return false;

	building = nullptr;

	return true;
}

const Building* Citizen::getBuilding() const
{
	return building;
}

Building* Citizen::getBuilding()
{
	return building;
}

Citizen* Citizen::loadCitizen(std::istream& in)
{
	std::string type;
	in >> type;

	if (type == "Miner") return Miner::load(in);
	if (type == "Programmer") return Programmer::load(in);
	if (type == "Teacher") return Teacher::load(in);
	if (type == "Unemployed") return Unemployed::load(in);

	throw std::runtime_error("Unknown citizen type");
}

void Citizen::saveBase(std::ostream& out) const
{
	out << name << ' '
		<< characteristics.happiness << ' '
		<< characteristics.money << ' '
		<< characteristics.life << ' '
		<< salary << '\n';
}
