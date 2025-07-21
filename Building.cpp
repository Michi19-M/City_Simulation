#include "Building.h"
#include <cmath>
#include <stdexcept>
#include <iostream>

#include "Dormitory.h"
#include "ModernBuilding.h"
#include "PanelBuilding.h"

void Building::free()
{
	if (residents.empty())
		return;

	for (size_t i = 0; i < residents.size(); i++)
	{
		residents[i]->leaveBuilding();
	}
	residents.clear();
}

unsigned Building::getRent() const
{
	return rent;
}

size_t Building::getPeopleCount() const
{
	return residents.size();
}

const std::vector<Citizen*>& Building::getAllResidents() const
{
	return residents;
}

Citizen& Building::getResident(size_t index)
{
	if (index >= residents.size())
		throw std::out_of_range("Invalid index for citizen");

	return *residents[index];
}

const Citizen& Building::getResident(size_t index) const
{
	if (index >= residents.size())
		throw std::out_of_range("Invalid index for citizen");

	return *residents[index];
}

const Building::Location& Building::getLocation() const
{
	return location;
}

Building::~Building()
{
	free();
}

bool Building::addResident(Citizen* newResident)
{
	if (residents.size() == peopleCapacity)
		return false;

	if (!newResident->setBuilding(this))
		return false;

	residents.push_back(newResident);

	return true;
}

bool Building::removeResidentAtIndex(size_t index)
{
	if (index >= residents.size())
		return false;

	residents[index]->leaveBuilding();
	std::swap(residents[index], residents.back());
	residents.pop_back();
	//residents.erase(residents.begin() + index); // запазва редът на настаняване, но е по-бавно

	return true;
}

void Building::print() const
{
	std::cout << "Location row: " << location.row << " cow: " << location.col << "\nRent: " << rent << "\nResidents: " << residents.size() << '\n';
}

Building::Building(size_t row, size_t col, unsigned rent, size_t capacity)
	: rent(rent), peopleCapacity(capacity), location{ row, col }
{
	setRent();

	residents.reserve(peopleCapacity);
}

bool Building::isCentral() const
{
	size_t centerRow = location.row / 2;
	size_t centerCol = location.col / 2;

	double distance = std::sqrt((location.row - centerRow) * (location.row - centerRow) + (location.col - centerCol) * (location.col - centerCol));

	return distance > (6.0 * std::min(location.row, location.col) / 8.0);
}

bool Building::isPeripheral() const
{
	size_t centerRow = location.row / 2;
	size_t centerCol = location.col / 2;
	double distance = std::sqrt((location.row - centerRow) * (location.row - centerRow) + (location.col - centerCol) * (location.col - centerCol));

	return distance <= (std::min(location.row, location.col) / 8.0);
}

Building* Building::loadBuilding(std::istream& in)
{
	std::string type;
	in >> type;

	if (type == "Dormitory") return Dormitory::load(in);
	if (type == "Modern") return ModernBuilding::load(in);
	if (type == "Panel") return PanelBuilding::load(in);
	
	throw std::runtime_error("Unknown building type");
}

void Building::saveBase(std::ostream& out) const
{
	out << location.row << ' '
		<< location.col << ' '
		<< rent << ' '
		<< peopleCapacity << ' '
		<< residents.size() << '\n';

	for (Citizen* c : residents) {
		c->save(out);
	}
}

void Building::loadBase(std::istream& in)
{
	size_t capacity, size;
	in >> capacity >> size;

	peopleCapacity = capacity;
	residents.clear();

	for (size_t i = 0; i < size; i++)
	{
		Citizen* c = Citizen::loadCitizen(in);
		c->setBuilding(this);
		residents.push_back(c);
	}
}

void Building::setRent()
{
	if (isCentral())
		rent *= 2.5;

	if (isPeripheral())
		rent *= 0.8;
}