#pragma once
#include "Building.h"

class ModernBuilding : public Building
{
public:
	ModernBuilding(int row, int col, size_t capacity);

	ModernBuilding(ModernBuilding&&) noexcept = default;
	ModernBuilding& operator=(ModernBuilding&&) noexcept = default;

	std::string getBuildingType() const override;

	 void save(std::ostream& out) const override;
	 static Building* load(std::istream& in);
};

