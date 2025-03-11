#include <iostream>
#include "PDFWriter.h"
#include "PDFPage.h"
#include "PageContentContext.h"

#ifdef _WIN32
static const std::string scBasePath = ".\\build\\";
static const std::string scFontsPath = ".\\Resources\\Fonts\\";
#else
static const std::string scBasePath = "./build/";
static const std::string scFontsPath = "./Resources/Fonts/";
#endif

int main(void)
{
    PDFWriter pdfWriter;
    EStatusCode status;

    do
    {
        status = pdfWriter.StartPDF(scBasePath + "PDFWriterTest.pdf", ePDFVersion15);

        if (PDFHummus::eSuccess != status)
            break;

        PDFPage *pdfPage = new PDFPage();
        pdfPage->SetMediaBox(PDFRectangle(0, 0, 595, 842));

        PageContentContext *pageContentContext = pdfWriter.StartPageContentContext(pdfPage);

        PDFUsedFont *font = pdfWriter.GetFontForFile(scFontsPath + "times.ttf");
        if (NULL == font)
        {
            status = PDFHummus::eFailure;
            break;
        }

        pageContentContext->k(0, 0, 0, 1);

        pageContentContext->BT();
        pageContentContext->Tf(font, 1);
        pageContentContext->Tm(30, 0, 0, 30, 20, 20);
        pageContentContext->Tj("Hello World");
        pageContentContext->ET();

        status = pdfWriter.EndPageContentContext(pageContentContext);
        if (PDFHummus::eSuccess != status)
            break;

        status = pdfWriter.WritePageAndRelease(pdfPage);
        if (PDFHummus::eSuccess != status)
            break;

        pdfWriter.EndPDF();
    } while (false);

    if (PDFHummus::eSuccess == status)
        std::cout << "Succeeded in creating PDF writer" << std::endl;
    else
    {
        std::cout << "Failed in creating PDF writer" << std::endl;
        return 1;
    }

    return 0;
}