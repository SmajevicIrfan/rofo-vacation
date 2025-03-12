#pragma once

#include <string>

#include "PDFLayout.h"

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

    // Constructor
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
        std::string substitute_)
        : year(year_),
          fullName(std::move(fullName_)),
          jobTitle(std::move(jobTitle_)),
          businessUnit(std::move(businessUnit_)),
          legalVacationDays(legalVacationDays_),
          experienceVacationDays(experienceVacationDays_),
          armyVacationDays(armyVacationDays_),
          startDate(std::move(startDate_)),
          endDate(std::move(endDate_)),
          firstDayBack(std::move(firstDayBack_)),
          firstPartDays(firstPartDays_),
          secondPartDays(secondPartDays_),
          substitute(std::move(substitute_))
    {
    }
};

struct RoFoVacationLayout : PDFLayout
{
    PDFUsedFont *timesFont, *timesBoldFont;

    bool loadAssets(PDFWriter &pdfWriter) override;
    EStatusCode render(PDFWriter &pdfWriter, PDFLayoutData &data) override;
};
