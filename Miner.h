#pragma once
#include "Citizen.h"

class Miner : public Citizen
{
public:
	Miner(const std::string& name, int happines, int money, int lifePoints, int salary);

	void monthlyUpdate() override;

	void save(std::ostream& out) const override;
	static Citizen* load(std::istream& in);

private:
	void setSalary(int salary) override;
};

