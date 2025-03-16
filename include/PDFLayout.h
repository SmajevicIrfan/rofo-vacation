#pragma once

#include <string>

#include "PDFWriter.h"
#include "PDFPage.h"
#include "PageContentContext.h"
#include "PDFUsedFont.h"

#include "PDFLayoutData.h"

struct PDFLayout
{
    void drawBlock(PageContentContext *ctx,
                   double x, double y,
                   const std::string &text,
                   PDFUsedFont *font = nullptr,
                   double fontSize = 0.00);
    void drawCenteredBlock(PageContentContext *ctx,
                           double x, double y,
                           const std::string &text,
                           PDFUsedFont *font,
                           double fontSize);
    void drawRightAlignedBlock(PageContentContext *ctx,
                               double x, double y,
                               const std::string &text,
                               PDFUsedFont *font,
                               double fontSize);
    void drawParagraph(PageContentContext *ctx,
                       double x, double y,
                       const std::string &text,
                       PDFUsedFont *font,
                       double fontSize,
                       double maxWidth);

    virtual bool loadAssets(PDFWriter &pdfWriter) = 0;
    virtual EStatusCode render(PDFWriter &pdfWriter, const PDFLayoutData &data) = 0;
};
