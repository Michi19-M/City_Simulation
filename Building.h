#pragma once
#include "Citizen.h"
#include <vector>

class Building
{
	friend class Citizen;

protected:
	struct Location {
		size_t row;
		size_t col;
	} location;

public:
	Building(size_t row, size_t col, unsigned rent, size_t capacity);

	// ne moje da ima dve sgradi na edna lokaciq i s edni i sushti jivushti => nqma kopirane
	Building(const Building& other) = delete; 
	Building& operator=(const Building& other) = delete;

	bool isCentral() const;
	bool isPeripheral() const;

	unsigned getRent() const;
	size_t getPeopleCount() const;
	const std::vector<Citizen*>& getAllResidents() const;
	Citizen& getResident(size_t index);
	const Citizen& getResident(size_t index) const;
	const Location& getLocation() const;

	virtual std::string getBuildingType() const = 0;

	virtual ~Building();

	bool addResident(Citizen* newResident); // will take ownership of the object
	
	bool removeResidentAtIndex(size_t index);

	void print() const;

	virtual void save(std::ostream& out) const = 0;
	static Building* loadBuilding(std::istream& in); //fabric

protected:
	void saveBase(std::ostream& out) const;
	void loadBase(std::istream& in);

protected:
	unsigned rent;
	std::vector<Citizen*> residents;
	size_t peopleCapacity;

private:
	void setRent();
	void free();
};