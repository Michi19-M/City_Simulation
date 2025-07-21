#pragma once
#include <string>
#include "Date.h"
#include "Citizen.h"
#include "City.h"

CitizenType getTypeFromJob(const std::string& job);

Date getCurrentDate();

int generateSalaryForJob(const std::string& job);

void generateCity(int n, int m, City* city);

CitizenType setCitizenTypeFromString(const std::string& str);

void runCommandInterface();