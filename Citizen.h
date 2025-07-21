#pragma once
#include <string>
#include "Building.h"

enum class CitizenType
{
	Miner,
	Programmer,
	Teacher,
	Unemployed
};

class Citizen
{
	friend class Building;

public:
	Citizen(const std::string& name, int happines, int money, int lifePoints);

	// citizens will be unique
	Citizen(const Citizen&) = delete;
	Citizen& operator=(const Citizen&) = delete;

	virtual ~Citizen() = default;

	virtual void liveOneDay(bool isFirstDayOfMonth);
	virtual void monthlyUpdate() = 0;

	virtual void payRent();

	void print() const;

	const std::string& getName() const;
	int getHappines() const;
	int getMoney() const;
	int getLifePoints() const;
	int getSalary() const;

	bool setBuilding(Building* newBuilding);
	bool leaveBuilding();
	const Building* getBuilding() const;
	Building* getBuilding();

	virtual void save(std::ostream& out) const = 0;
	static Citizen* loadCitizen(std::istream& in);
protected:
	void saveBase(std::ostream& out) const;

protected:
	std::string name;

	struct Characteristics {
		int happiness;
		int money;
		int life;
	} characteristics;

	int salary;

	Building* building = nullptr; // pointer to the building in which he lives
protected:
	virtual void setSalary(int salary) = 0;
};

