#include "Dormitory.h"
#include <fstream>

Dormitory::Dormitory(int row, int col, size_t capacity)
	: Building(row, col, 40, capacity)
{}

std::string Dormitory::getBuildingType() const
{
	return "Dormitory";
}

void Dormitory::save(std::ostream& out) const
{
	out << "Dormitory" << ' ';
	Building::saveBase(out);
}

Building* Dormitory::load(std::istream& in)
{
	size_t row, col, rent;
	in >> row >> col >> rent;

	auto* mod = new Dormitory(row, col, rent);
	mod->loadBase(in);
	return mod;
}
