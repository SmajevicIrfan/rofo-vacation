#include <xlnt/xlnt.hpp>
#include "RoFoVacationLayoutData.h"

static const std::string headers[]{
    "Godina za koju se odnosi rješenje",
    "Ime i prezime radnika",
    "Radno mjesto radnika",
    "Poslovnica poslodavca radnika",
    "Dužina trajanja godišnjeg odmora - zakonski minimum",
    "Dužina trajanja godišnjeg odmora - dužina radnog staža",
    "Dužina trajanja godišnjeg odmora - učešće u odbrambeno-oslobodilačkom ratu",
    "Trajanje godišnjeg odmora - prvi dio",
    "Trajanje godišnjeg odmora - drugi dio",
    "Datum početka prvog dijela godišnjeg odmora",
    "Datum kraja prvog dijela godišnjeg odmora",
    "Datum javljanja na posao nakon prvog dijela godišnjeg odmora",
    "Zamjena za radnika"};
static const size_t headers_size = sizeof(headers) / sizeof(headers[0]);

RoFoVacationLayoutData::RoFoVacationLayoutData(
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

std::vector<struct RoFoVacationLayoutData> loadFromXlsx(const std::string &path)
{
    int mapping[headers_size]{0};
    xlnt::workbook wb;
    wb.load(path);

    xlnt::worksheet ws = wb.active_sheet();
    xlnt::range rows = ws.rows();
    for (size_t i = 0; i < headers_size; i++)
    {
        for (auto cell : rows.front())
        {
            if (cell.to_string() == headers[i])
            {
                mapping[i] = cell.column_index() - 1;
                break;
            }
        }
    }

    size_t num_rows = rows.length();
    std::vector<struct RoFoVacationLayoutData> data;
    for (size_t i = 1; i < num_rows; i++)
    {
        auto row = rows[i];

        data.push_back(RoFoVacationLayoutData(
            row[mapping[0]].value<int>(),
            row[mapping[1]].to_string(),
            row[mapping[2]].to_string(),
            row[mapping[3]].to_string(),
            row[mapping[4]].value<int>(),
            row[mapping[5]].value<int>(),
            row[mapping[6]].value<int>(),
            row[mapping[9]].to_string(),
            row[mapping[10]].to_string(),
            row[mapping[11]].to_string(),
            row[mapping[7]].value<int>(),
            row[mapping[8]].value<int>(),
            row[mapping[12]].to_string()));
    }

    return data;
}

std::vector<struct RoFoVacationLayoutData> loadFromXls(const std::string &path)
{
    std::cout << "Path: " << path << std::endl;
    throw std::runtime_error("Not implemented");
}