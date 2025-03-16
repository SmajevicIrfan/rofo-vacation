#pragma once

#include <string>

#include "PDFLayout.h"

struct RoFoVacationLayout : PDFLayout
{
    PDFUsedFont *timesFont, *timesBoldFont;

    bool loadAssets(PDFWriter &pdfWriter) override;
    EStatusCode render(PDFWriter &pdfWriter, const PDFLayoutData &data) override;
};
