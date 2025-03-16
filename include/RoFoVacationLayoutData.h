#pragma once

#include <string>
#include <vector>
#include "PDFLayoutData.h"

struct RoFoVacationLayoutData : public PDFLayoutData
{
    int year;
    std::string fullName;
    std::string jobTitle;
    std::string businessUnit;
    int legalVacationDays;
    int experienceVacationDays;
    int armyVacationDays;
    std::string startDate;
    std::string endDate;
    std::string firstDayBack;
    int firstPartDays;
    int secondPartDays;
    std::string substitute;

    RoFoVacationLayoutData(
        int year_,
        std::string fullName_,
        std::string jobTitle_,
        std::string businessUnit_,
        int legalVacationDays_,
        int experienceVacationDays_,
        int armyVacationDays_,
        std::string startDate_,
        std::string endDate_,
        std::string firstDayBack_,
        int firstPartDays_,
        int secondPartDays_,
        std::string substitute_);
};

std::vector<struct RoFoVacationLayoutData> loadFromXlsx(const std::string &path);
std::vector<struct RoFoVacationLayoutData> loadFromXls(const std::string &path);
