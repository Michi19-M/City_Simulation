#pragma once
#include "Building.h"

class PanelBuilding : public Building
{
public:
	PanelBuilding(int row, int col, size_t capacity);

	std::string getBuildingType() const override;

	void save(std::ostream& out) const override;
	static Building* load(std::istream& in);
};

