#pragma once
#include "Building.h"

class Dormitory : public Building
{
public:
	Dormitory(int row, int col, size_t capacity);

	Dormitory(Dormitory&&) noexcept = default;
	Dormitory& operator=(Dormitory&&) noexcept = default;

	std::string getBuildingType() const override;

	void save(std::ostream& out) const override;
	static Building* load(std::istream& in);
};

