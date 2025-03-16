#include <iostream>
#include <string>
#include <vector>

#include "RoFoVacationLayout.h"
#include "RoFoVacationLayoutData.h"

int main(void)
{
    std::vector<struct RoFoVacationLayoutData> data = loadFromXlsx("resources/example/rofo_vacation_example.xlsx");
    for (const auto &d : data)
    {
        PDFWriter pdfWriter;
        RoFoVacationLayout layout;
        pdfWriter.StartPDF("build/rofo_vacation_" + d.fullName + "_" + std::to_string(d.year) + ".pdf", ePDFVersion13);
        layout.loadAssets(pdfWriter);
        layout.render(pdfWriter, d);
        pdfWriter.EndPDF();
    }

    return 0;
}
