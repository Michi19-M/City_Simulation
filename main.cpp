#include "SimulationGenerator.h"

int main()
{
	// TESTING CITIZENS - First Test
	{
		/*Citizen** citizens = new Citizen * [4];
		citizens[0] = new Teacher("Dimitar Stoilov", 5, 3500, 8, 1300);
		citizens[1] = new Programmer("Petar Armyanov", 9, 5000, 15, 3300);
		citizens[2] = new Miner("Ivan Pavlov", 2, 2350, 2, 2800);
		citizens[3] = new Unemployed("Martin", 20, 900, 20);

		for (size_t i = 0; i < 4; i++)
		{
			citizens[i]->print();
			std::cout << std::endl;
		}

		for (size_t i = 0; i < 4; i++)
		{
			citizens[i]->liveOneDay(true);
			std::cout << std::endl;
		}
		std::cout << "----------------------------\n";
		for (size_t i = 0; i < 4; i++)
		{
			citizens[i]->print();
			std::cout << std::endl;
		}

		for (size_t i = 0; i < 4; i++)
		{
			delete citizens[i];
		}
		delete[] citizens;*/
	}

	// TESTING BUILDINGS - First test
	{
		/*Building** buildings = new Building * [3];
		buildings[0] = new ModernBuilding(1, 2, 8);
		buildings[1] = new PanelBuilding(2, 4, 30);
		//buildings[2] = buildings[0]; // STILL WORKING :(
		//buildings[2] = std::move(buildings[0]); // TO CHECK

		Citizen* teacher = new Teacher("Stoyan", 4, 2, 3, 200);
		teacher->liveOneDay(true);

		Citizen* programmger = new Programmer("Petur Armqnov", 8, 8, 8, 2500);
		programmger->liveOneDay(true);+

		buildings[0]->addResident(teacher);
		buildings[0]->addResident(programmger);

		teacher->getBuilding()->print();
		std::cout << "\n *******************************************\n";
		try
		{
			buildings[0]->removeResidentAtIndex(0);
		}
		catch (const std::out_of_range& ex)
		{
			std::cout << ex.what() << '\n';
		}

		for (size_t i = 0; i < 3; i++)
		{
			buildings[i]->print();
			for (size_t p = 0; p < buildings[i]->getPeopleCount(); p++)
			{
				std::cout << "------------------\nResident:\n";
				buildings[i]->getCitizen(p).print();
			}
			std::cout << std::endl;
		}

		for (size_t i = 0; i < 3; i++)
		{
			delete buildings[i];
		}
		delete[] buildings;
		delete teacher;
		delete programmer;*/
	}

	// TESTING CITY - First test
	{
		/*City city(5, 5);

		Building* b1 = new PanelBuilding(0, 0, 5);
		Building* b2 = new ModernBuilding(1, 2, 15);
		Building* b3 = new Dormitory(3, 3, 40);
		city.addBuilding(b1, 0, 0);
		city.addBuilding(b2, 1, 2);
		city.addBuilding(b3, 3, 3);

		city.addCitizen(0, 0, CitizenType::Miner, "Traqn", 4, 10, 3, 2000);
		city.addCitizen(1, 2, CitizenType::Programmer, "Petar", 8, 8, 5, 2500);
		city.addCitizen(3, 3, CitizenType::Unemployed, "Martin", 10, 2, 10);

		Citizen* c1 = new Teacher("Teodora", 20, 5, 10, 1500);
		city.getBuildingAt(0, 0)->addResident(c1);

		city.liveNdays(30);

		city.fullInfo();//
		std::cout << std::endl;

		city.removeCitizen(0, 0, "Teodora");

		city.fullInfo();

		delete c1;*/
	}

	// TEST SERIALIZATION - First test
	{
		/*City city(5, 5);

		Building* b1 = new PanelBuilding(0, 0, 5);
		Building* b2 = new ModernBuilding(1, 2, 15);
		Building* b3 = new Dormitory(3, 3, 40);
		city.addBuilding(b1, 0, 0);
		city.addBuilding(b2, 1, 2);
		city.addBuilding(b3, 3, 3);

		city.addCitizen(0, 0, CitizenType::Miner, "Traqn", 4, 10, 3, 2000);
		city.addCitizen(1, 2, CitizenType::Programmer, "Petar", 8, 8, 5, 2500);
		city.addCitizen(3, 3, CitizenType::Unemployed, "Martin", 10, 2, 10);

		city.save("city_test.txt");

		city.load("city_test.txt");
		city.fullInfo();*/
	}

	// TEST INTERFACE
	{
		runCommandInterface();
	}


	return 0;
}