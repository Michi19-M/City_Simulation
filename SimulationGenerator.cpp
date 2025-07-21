#include "SimulationGenerator.h"

#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include <sstream> 

//Buildings
#include "PanelBuilding.h"
#include "ModernBuilding.h"
#include "Dormitory.h"

// Citizens
#include "Citizen.h"
#include "Teacher.h"
#include "Programmer.h"
#include "Miner.h"
#include "Unemployed.h"

#include "City.h"

#pragma warning (disable : 4996)

// Примерни списъци
const std::vector<std::string> possibleNames = {
	"Ivan", "Maria", "Georgi", "Petya", "Dimitar", "Elena", "Stefan", "Yana", "Todor", "Petko", "Mario", "Rayna"
};

const std::vector<std::string> possibleJobs = {
	"Miner", "Programmer", "Unemployed", "Teacher"
};
CitizenType getTypeFromJob(const std::string& job) {
	if (job == "Miner") return CitizenType::Miner;
	if (job == "Programmer") return CitizenType::Programmer;
	if (job == "Teacher") return CitizenType::Teacher;
	if (job == "Unemplyoed") return CitizenType::Unemployed;
	return CitizenType::Unemployed;
}

Date getCurrentDate() {
	std::time_t now = std::time(nullptr);
	std::tm* localTime = std::localtime(&now);

	int day = localTime->tm_mday;
	int month = localTime->tm_mon + 1;
	int year = localTime->tm_year + 1900;

	return Date(day, month, year);
}

int generateSalaryForJob(const std::string& job) {
	if (job == "Teacher") {
		return 1200 + rand() % (1300 - 1200 + 1); // 1200-1300
	}
	else if (job == "Programmer") {
		return 2000 + rand() % (5000 - 2000 + 1); // 2000-5000
	}
	else if (job == "Miner") {
		return 1000 + rand() % (3000 - 1000 + 1); // 1000-3000
	}
	else {
		return 0;
	}
}

void generateCity(int n, int m, City* city) {
	srand(time(0));

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			size_t row = i;
			size_t col = j;
			size_t capacity = 1 + rand() % 10; // between 1 nad 10

			int type = rand() % 3;
			Building* b = nullptr;
			if (type == 0)
				b = new PanelBuilding(row, col, capacity);
			else if (type == 1)
				b = new ModernBuilding(row, col, capacity);
			else
				b = new Dormitory(row, col, capacity);

			city->addBuilding(b, i, j);

			int numPeople = rand() % (capacity + 1); // от 0 до capacity
			for (int p = 0; p < numPeople; ++p) {
				std::string name = possibleNames[rand() % possibleNames.size()];
				std::string job = possibleJobs[rand() % possibleJobs.size()];
				CitizenType type = getTypeFromJob(job);

				int happiness = 1 + rand() % 100;
				int money = 1 + rand() % 1000;
				int life = 1 + rand() % 100;

				int salary = generateSalaryForJob(job);

				city->addCitizen(i, j, type, name, happiness, money, life, salary);
			}
		}
	}

	city->setDate(getCurrentDate());

	std::cout << "Simulation created on ";
	getCurrentDate().print();
	std::cout << std::endl;
}


CitizenType setCitizenTypeFromString(const std::string& str)
{
	CitizenType type;
	if (str == "Miner") {
		return type = CitizenType::Miner;
	}
	if (str == "Programmer")
	{
		return type = CitizenType::Programmer;
	}
	if (str == "Teacher") {
		return type = CitizenType::Teacher;
	}
	if (str == "Unemployed") {
		return type = CitizenType::Unemployed;
	}
	throw std::invalid_argument("Invalid citizen job\n");
}

void runCommandInterface()
{
	std::string line;
	City* city = nullptr;

	while (std::getline(std::cin, line))
	{
		std::istringstream iss(line);
		std::string command;
		iss >> command;

		if (command == "stop") {
			break;
		}

		if (!city && command != "generate") {
			std::cerr << "City is not generated. Use command 'generate <rows> <cols>'.\n";
			continue;
		}

		if (command == "generate") {
			size_t n, m;
			if (iss >> n >> m) {
				delete city;
				city = new City(n, m);
				generateCity(n, m, city);
			}
			else {
				std::cerr << "Invalid arguments for generating City\n";
			}
		}
		else if (command == "add") {
			int x, y, happiness, money, life, salary;
			std::string name, job;
			if (iss >> x >> y >> name >> job >> happiness >> money >> life >> salary) {
				CitizenType type = setCitizenTypeFromString(job);
				bool success = city->addCitizen(x, y, type, name, happiness, money, life, salary);
				std::cout << (success ? "Added successfully\n" : "Failed to add\n");
			}
			else {
				std::cerr << "Invalid arguments for add\n";
			}
		}
		else if (command == "remove") {
			int x, y;
			std::string name;
			if (iss >> x >> y >> name) {
				bool success = city->removeCitizen(x, y, name);
				std::cout << (success ? "Removed successfully\n" : "Failed to remove\n");
			}
			else {
				std::cerr << "Invalid arguments for remove\n";
			}
		}
		else if (command == "step") {
			int n = 1;
			if (!(iss >> n)) n = 1;
			city->liveNdays(n);
		}
		else if (command == "info") {
			int x, y;
			std::string name;
			if (iss >> x >> y) {
				if (iss >> name) {
					city->infoForCitizenOnLocation(x, y, name);
				}
				else {
					city->infoOnLocation(x, y);
				}
			}
			else {
				city->fullInfo();
			}
		}
		else if (command == "save") {
			std::string filename;
			if (iss >> filename) {
				if (city->save(filename))
					std::cout << "Saved successfully\n";
				else
					std::cerr << "Failed to save\n";
			}
		}
		else if (command == "load") {
			std::string filename;
			if (iss >> filename) {
				if (city->load(filename))
					std::cout << "Loaded successfully\n";
				else
					std::cerr << "Failed to load\n";
			}
		}
		else {
			std::cerr << "Unknown command\n";
		}
	}
}