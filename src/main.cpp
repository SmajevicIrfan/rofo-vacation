#include <iostream>

// #include "PDFWriter.h"
// #include "PDFPage.h"
// #include "PageContentContext.h"
#include "xlnt/xlnt.hpp"

#include "RoFoVacationLayout.h"

#ifdef _WIN32
static const std::string scBasePath = ".\\build\\";
static const std::string scFontsPath = ".\\resources\\fonts\\";
#else
static const std::string scBasePath = "./build/";
static const std::string scFontsPath = "./resources/fonts/";
#endif

int main(void)
{
    // PDFWriter pdfWriter;
    // EStatusCode status;

    // std::cout << "Testing PDF library" << std::endl;

    // do
    // {
    //     status = pdfWriter.StartPDF(scBasePath + "PDFWriterTest.pdf",
    //                                 ePDFVersion15,
    //                                 LogConfiguration::DefaultLogConfiguration(),
    //                                 PDFCreationSettings(true, true));

    //     if (PDFHummus::eSuccess != status)
    //         break;

    //     struct RoFoVacationLayout layout;
    //     RoFoVacationLayoutData data(
    //         2025,
    //         "Neko Nekić",
    //         "Marketing",
    //         "Veleprodaja",
    //         20, 5, 1,
    //         "01.02.2025",
    //         "12.02.2025",
    //         "13.02.2025",
    //         12,
    //         14,
    //         "Nekalo Nekalić");

    //     if (!layout.loadAssets(pdfWriter))
    //     {
    //         fprintf(stderr, "[ERROR] Failed to load assets\n");
    //         status = PDFHummus::eFailure;
    //         break;
    //     }

    //     status = layout.render(pdfWriter, data);
    //     if (PDFHummus::eSuccess != status)
    //     {
    //         fprintf(stderr, "[ERROR] Failed to render layout\n");
    //         break;
    //     }

    //     pdfWriter.EndPDF();
    // } while (false);

    // if (PDFHummus::eSuccess == status)
    //     std::cout << "Succeeded in creating PDF file" << std::endl;
    // else
    // {
    //     std::cout << "Failed in creating PDF file" << std::endl;
    //     return 1;
    // }

    std::cout << "Testing Excel library" << std::endl;

    xlnt::workbook wb;
    xlnt::worksheet ws = wb.active_sheet();
    ws.cell("A1").value(5);
    ws.cell("B2").value("string data");
    ws.cell("C3").formula("=RAND()");
    wb.save(scBasePath + "xlnt_test.xlsx");

    return 0;
}
