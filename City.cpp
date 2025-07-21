#include "City.h"
#include "Miner.h"
#include "Programmer.h"
#include "Teacher.h"
#include "Unemployed.h"

#include <iostream>
#include <fstream>

City::City(size_t cityRows, size_t cityCols)
	: rows(cityRows), cols(cityCols),
	map(cityRows, std::vector<Building*>(cols, nullptr)),
	date(20, 6, 2025)
{
	buildings.reserve(rows * cols);
}

City::~City()
{
	clear();
}

bool City::addBuilding(Building* newBuilding, size_t row, size_t col)
{
	if (row >= rows || col >= cols) {
		std::cerr << "Invalid location for building\n";
		return false;
	}
	if (map[row][col]) {// is not empty
		std::cerr << "A building already exists at this location\n";
		return false;
	}

	map[row][col] = newBuilding;
	buildings.push_back(newBuilding);

	return true;
}

bool City::addBuilding(Building* newBuilding)
{
	size_t row = newBuilding->getLocation().row;
	size_t col = newBuilding->getLocation().col;

	if (row > rows || col > cols)
		return false;

	if (map[row][col] != nullptr)
		return false;

	map[row][col] = newBuilding;
	buildings.push_back(newBuilding);

	return false;
}

Building* City::getBuildingAt(size_t row, size_t col) const
{
	if (row > rows || col > cols) {
		std::cerr << "Invalid location for building\n";
		return nullptr;
	}

	return map[row][col];
}

bool City::addCitizen(size_t row, size_t col, CitizenType type, const std::string& name, int happiness, int money, int life, int salary)
{
	if (row >= this->rows || col >= this->cols)
		return false;

	Citizen* newCitizen = createCitizen(type, name, happiness, money, life, salary);
	if (!map[row][col]->addResident(newCitizen)) {
		delete newCitizen;
		return false;
	}

	citizens.push_back(newCitizen);

	return true;
}

bool City::removeCitizen(size_t row, size_t col, const std::string& name)
{
	if (row >= this->rows || col >= this->cols)
		return false;

	size_t length = map[row][col]->getPeopleCount();

	for (size_t i = 0; i < length; i++)
	{
		Citizen* c = &map[row][col]->getResident(i);
		if (c->getName() == name) {
			map[row][col]->removeResidentAtIndex(i);

			for (size_t j = 0; j < citizens.size(); j++)
			{
				if (citizens[j] == c) {
					delete citizens[j];
					std::swap(citizens[j], citizens.back());
					citizens.pop_back();
					break;
				}
			}

			return true;
		}
	}
	return false;
}

void City::liveOneDay(bool printInfo)
{
	bool isFirstDay = (date.getDay() == 1);

	for (Citizen* c : citizens)
		c->liveOneDay(isFirstDay);

	date.goToNextDay();

	if (printInfo) {
		std::cout << "Number of people with 0 happines, 0 life points or 0 money: " << numberOfCitizensToDie() << '\n';
		removeCitizensWhoMustDie();
	}
}

void City::liveNdays(unsigned n)
{
	for (size_t i = 0; i < n; i++)
	{
		liveOneDay(false);
	}
	std::cout << "Number of people with 0 happines, 0 life points or 0 money: " << numberOfCitizensToDie() << '\n';
	removeCitizensWhoMustDie();
}

const Date& City::getDate() const
{
	return date;
}

void City::setDate(const Date& newDate)
{
	date = newDate;
}

void City::infoOnLocation(size_t row, size_t col) const
{
	if (row >= this->rows || col >= this->cols)
		return;

	Building* b = getBuildingAt(row, col);
	std::cout << "Location "
		<< b->getLocation().row
		<< " "
		<< b->getLocation().col
		<< ":\n"
		<< b->getBuildingType()
		<< ":\n";

	size_t length = map[row][col]->getPeopleCount();
	for (size_t i = 0; i < length; i++)
	{
		std::cout << i + 1 << ". ";
		b->getResident(i).print();
	}
}

void City::infoForCitizenOnLocation(size_t row, size_t col, const std::string& name) const
{
	if (row >= this->rows || col >= this->cols)
		return;

	size_t length = map[row][col]->getPeopleCount();
	for (size_t i = 0; i < length; i++)
	{
		Citizen* c = &map[row][col]->getResident(i);
		if (c->getName() == name)
			c->print(); // ne spiram cikala -> vsichki s tova ime
	}
}

void City::fullInfo() const
{

	for (size_t i = 0; i < buildings.size(); i++)
	{
		std::cout << "Location "
			<< buildings[i]->getLocation().row
			<< " "
			<< buildings[i]->getLocation().col
			<< ":\n"
			<< buildings[i]->getBuildingType()
			<< ":\n";

		size_t residentsCount = buildings[i]->getPeopleCount();
		for (size_t p = 0; p < residentsCount; p++)
		{
			std::cout << p + 1 << ". ";
			buildings[i]->getResident(p).print();
		}
	}
}

size_t City::numberOfCitizensToDie() const
{
	size_t count = 0;
	for (size_t i = 0; i < citizens.size(); i++)
	{
		if (citizens[i]->getMoney() <= 0 ||
			citizens[i]->getHappines() <= 0 ||
			citizens[i]->getLifePoints() <= 0)
			++count;
	}
	return count;
}

void City::removeAllBrokeCitizens()
{
	for (size_t i = 0; i < citizens.size(); i++)
	{
		if (citizens[i]->getMoney() <= 0)
		{
			helperFunctionForRemoveingCitizens(i);
		}
	}
}

void City::removeAllLifelessCitizens()
{
	for (size_t i = 0; i < citizens.size(); i++)
	{
		if (citizens[i]->getLifePoints() <= 0)
		{
			helperFunctionForRemoveingCitizens(i);
		}
	}
}

void City::removeAllUnhappyCitizens()
{
	for (size_t i = 0; i < citizens.size(); i++)
	{
		if (citizens[i]->getHappines() <= 0)
		{
			helperFunctionForRemoveingCitizens(i);
		}
	}
}

void City::removeCitizensWhoMustDie()
{
	removeAllBrokeCitizens();
	removeAllLifelessCitizens();
	removeAllUnhappyCitizens();
}

bool City::save(const std::string& filename) const
{
	std::ofstream out(filename);
	if (!out.is_open())
		return false;

	out << "City " << rows << " " << cols << "\n";
	out << "Buildings:" << ' ' << buildings.size() << "\n";

	for (Building* b : buildings)
	{
		b->save(out);
	}

	out.close();

	return true;
}

bool City::load(const std::string& filename)
{
	std::ifstream in(filename);
	if (!in.is_open())
		return false;

	clear();

	std::string keyword;
	in >> keyword;

	if (keyword != "City")
		return false;

	in >> rows >> cols;

	map.resize(rows);
	for (size_t i = 0; i < rows; i++)
	{
		map[i].resize(cols, nullptr);
	}

	in >> keyword;
	if (keyword != "Buildings:")
		return false;
	size_t buildingsCount = 0;
	in >> buildingsCount;

	for (size_t i = 0; i < buildingsCount; i++)
	{		
		Building* b = Building::loadBuilding(in);
		if (!b)
			return false;

		size_t r = b->getLocation().row;
		size_t c = b->getLocation().col;

		buildings.push_back(b);
		map[r][c] = b;
		
		const std::vector<Citizen*>& res = b->getAllResidents();
		citizens.insert(citizens.end(), res.begin(), res.end());	
	}

	in.close();
	return true;
}

Citizen* City::createCitizen(CitizenType type, const std::string& name, int happiness, int money, int life, int salary)
{
	switch (type)
	{
	case CitizenType::Miner:
		return new Miner(name, happiness, money, life, salary);
	case CitizenType::Programmer:
		return new Programmer(name, happiness, money, life, salary);
	case CitizenType::Teacher:
		return new Teacher(name, happiness, money, life, salary);
	case CitizenType::Unemployed:
		return new Unemployed(name, happiness, money, life);
	default:
		throw std::invalid_argument("Unknown citizen type");
	}
}

void City::clear()
{
	for (Building* b : buildings)
		delete b;
	buildings.clear();

	for (Citizen* c : citizens)
		delete c;
	citizens.clear();

	for (size_t row = 0; row < map.size(); row++)
	{
		for (size_t col = 0; col < map[row].size(); col++)
		{
			map[row][col] = nullptr;
		}
	}
	map.clear();
}

void City::helperFunctionForRemoveingCitizens(size_t& index)
{
	Building* b = citizens[index]->getBuilding();

	for (size_t c = 0; c < b->getPeopleCount(); c++)
	{
		if (citizens[index] == &b->getResident(c))
		{
			b->removeResidentAtIndex(c);
		}
	}
	delete citizens[index];
	std::swap(citizens[index], citizens.back());
	citizens.pop_back();
	--index;
}
