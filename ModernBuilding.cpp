#include "ModernBuilding.h"
#include <fstream>

ModernBuilding::ModernBuilding(int row, int col, size_t capacity)
	: Building(row, col, 1000, capacity)
{}

std::string ModernBuilding::getBuildingType() const
{
	return "Modern";
}

void ModernBuilding::save(std::ostream& out) const
{
	out << "Modern" << ' ';
	Building::saveBase(out);
}

Building* ModernBuilding::load(std::istream& in)
{
	size_t row, col, rent;
	in >> row >> col >> rent;

	auto* mod = new ModernBuilding(row, col, rent);
	mod->loadBase(in);
	return mod;
}

