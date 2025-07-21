#include "PanelBuilding.h"
#include <fstream>

PanelBuilding::PanelBuilding(int row, int col, size_t capacity)
	: Building(row, col, 500, capacity)
{}

std::string PanelBuilding::getBuildingType() const
{
	return "Panel";
}

void PanelBuilding::save(std::ostream& out) const
{
	out << "Panel" << ' ';
	Building::saveBase(out);
}

Building* PanelBuilding::load(std::istream& in)
{
	size_t row, col, rent;
	in >> row >> col >> rent;

	auto* mod = new PanelBuilding(row, col, rent);
	mod->loadBase(in);
	return mod;
}
