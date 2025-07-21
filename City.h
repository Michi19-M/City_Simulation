#pragma once
#include <vector>
#include "Building.h"
#include "Citizen.h"
#include "Date.h"

class City
{
	friend class Building;
public:
	City(size_t cityRows, size_t cityCols);
	~City();

	bool addBuilding(Building* newBuilding, size_t row, size_t col);
	bool addBuilding(Building* newBuilding);
	Building* getBuildingAt(size_t row, size_t col)const;
	
	bool addCitizen(size_t row, size_t col, CitizenType type, const std::string& name, int happiness, int money, int life, int salary = 0);
	bool removeCitizen(size_t row, size_t col, const std::string& name);

	void liveOneDay(bool printInfo = true); // step()
	void liveNdays(unsigned n); // step(n)

	const Date& getDate() const;
	void setDate(const Date& newDate);

	void infoOnLocation(size_t row, size_t col) const;
	void infoForCitizenOnLocation(size_t row, size_t col, const std::string& name) const;

	void fullInfo() const;

	size_t numberOfCitizensToDie() const;

	void removeAllBrokeCitizens();
	void removeAllLifelessCitizens();
	void removeAllUnhappyCitizens();
	void removeCitizensWhoMustDie();

	bool save(const std::string& filename) const;
	bool load(const std::string& filename);
private:
	Citizen* createCitizen(CitizenType type, const std::string& name, int happiness, int money, int life, int salary);

	void clear();
	void helperFunctionForRemoveingCitizens(size_t& index);
private:
	size_t rows;
	size_t cols;

	std::vector<std::vector<Building*>> map; // matrix of [rows][cols] of pointers to buildings
	std::vector<Building*> buildings; // City притежава ресурсите //all buildings, for easy access
	std::vector<Citizen*> citizens;

	Date date;
};

