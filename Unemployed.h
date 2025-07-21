#pragma once
#include "Citizen.h"

class Unemployed : public Citizen
{
public:
	Unemployed(const std::string& name, int happines, int money, int lifePoints, int salary = 0);

	void monthlyUpdate() override;

	void save(std::ostream& out) const override;
	static Citizen* load(std::istream& in);

private:
	void setSalary(int salary) override;
};

