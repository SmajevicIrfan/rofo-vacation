#include "RoFoVacationLayout.h"
#include "RoFoVacationLayoutData.h"

static const std::string scFontsPath = "./resources/fonts/";\

enum Case
{
    NOMINATIVE,
    GENITIVE
};

std::string getDeclension(int days, Case c)
{
    if (days % 100 >= 11 && days % 100 <= 19)
        return "radnih dana";

    switch (days % 10)
    {
    case 1:
        return c == NOMINATIVE ? "radni dan" : "radnog dana";
    case 2:
    case 3:
    case 4:
        return "radna dana";
    default:
        return "radnih dana";
    }
}

std::string getNominative(int days)
{
    return getDeclension(days, NOMINATIVE);
}

std::string getGenitive(int days)
{
    return getDeclension(days, GENITIVE);
}

bool RoFoVacationLayout::loadAssets(PDFWriter &pdfWriter)
{
    timesFont = pdfWriter.GetFontForFile(scFontsPath + "times.ttf");
    timesBoldFont = pdfWriter.GetFontForFile(scFontsPath + "timesbd.ttf");

    return timesFont && timesBoldFont;
}

EStatusCode RoFoVacationLayout::render(PDFWriter &pdfWriter, const PDFLayoutData &data)
{
    const RoFoVacationLayoutData *vacationData = dynamic_cast<const RoFoVacationLayoutData *>(&data);
    if (!vacationData)
        return PDFHummus::eFailure;

    static const double startX = 70.80;
    static const double maxWidth = 435.40;
    static const double lineHeight = 13.80;

    int totalVacationDays = vacationData->legalVacationDays +
                            vacationData->experienceVacationDays +
                            vacationData->armyVacationDays;

    EStatusCode status;

    // Create PDF page and set page dimensions (A4 in points)
    PDFPage *pdfPage = new PDFPage();
    pdfPage->SetMediaBox(PDFRectangle(0, 0, 595, 842));

    PageContentContext *ctx = pdfWriter.StartPageContentContext(pdfPage);

    // Set font color to black
    ctx->k(0, 0, 0, 1);
    
    ctx->TL(lineHeight);

    // --- Section 1: Header ---
    ctx->BT();
    ctx->Tf(timesBoldFont, 12.00);
    ctx->Td(startX, 760.01);
    ctx->Tj("Royal Food d.o.o. Sarajevo");
    ctx->Tf(timesFont, 12.00);
    ctx->Quote("Broj: ___ / __");
    ctx->Quote("Sarajevo, __. __. ____. godine");
    ctx->ET();

    // --- Section 2: Legal Statement ---
    {
        std::string legalText =
            "Na osnovu člana od 47. do 52. Zakona o radu (Sl.novine FBiH br.26/16 i 89/18), "
            "odredbi Pravilnika o radu „Royal Food“ d.o.o i plana korištenja godišnjeg odmora, "
            "direktor društva, donosi:";

        ctx->BT();
        drawParagraph(ctx, startX, 704.81, legalText, timesFont, 12.00, maxWidth);
        ctx->ET();
    }

    // --- Section 3: Title ---
    ctx->Tf(timesBoldFont, 14.00);
    drawCenteredBlock(ctx, 297.5, 648.21, "R J E Š E NJ E", timesBoldFont, 14.00);

    // --- Section 4: Vacation Year Subtitle ---
    ctx->Tf(timesFont, 12.00);
    drawCenteredBlock(ctx, 297.5, 634.41,
                      "o korištenju godišnjeg odmora za " + std::to_string(vacationData->year) + ". godinu",
                      timesFont, 12.00);

    // --- Section 5: Worker Details ---
    {
        std::string details =
            "Radniku " + vacationData->fullName + ", raspoređenom na radno mjesto \"" +
            vacationData->jobTitle + "\" u okviru poslovnice poslodavca u " + vacationData->businessUnit +
            ", utvrđuje se pravo na godišnji odmor za " + std::to_string(vacationData->year) +
            ". godinu u trajanju od " + std::to_string(totalVacationDays) + " " +
            getGenitive(totalVacationDays) + " dana.";

        ctx->BT();
        drawParagraph(ctx, startX, 592.00, details, timesFont, 12.00, maxWidth);
        ctx->ET();
    }

    // --- Section 6: Vacation Details ---
    {
        ctx->BT();
        ctx->Td(startX, 536.80);
        ctx->TL(lineHeight * 2.00);
        ctx->Tj("Dužina godišnjeg odmora utvrđena je po osnovama i kriterijima:");

        ctx->Quote("Zakonski minimum");
        ctx->Td(97.00, 0.00);
        ctx->Tj("..........................................");
        ctx->Td(129.00, 0.00);
        ctx->Tj(std::to_string(vacationData->legalVacationDays) + " " +
                getNominative(vacationData->legalVacationDays));

        ctx->Td(-226.00, 0.00);
        ctx->Quote("Dužina radnog staža");
        ctx->Td(100.00, 0.00);
        ctx->Tj(".........................................");
        ctx->Td(126.00, 0.00);
        ctx->Tj(std::to_string(vacationData->experienceVacationDays) + " " +
                getNominative(vacationData->experienceVacationDays));

        ctx->Td(-226.00, 0.00);
        ctx->Quote("Učešće u odbrambeno-oslobodilačkom ratu");
        ctx->Td(211.00, 0.00);
        ctx->Tj("....");
        ctx->Td(15.00, 0.00);
        ctx->Tj(std::to_string(vacationData->armyVacationDays) + " " +
                getNominative(vacationData->armyVacationDays));
        ctx->ET();
    }

    ctx->TL(lineHeight);

    // --- Section 7: Total Vacation Days ---
    {
        ctx->BT();
        ctx->Td(230.00, 426.40);
        ctx->Tj("UKUPNO");
        ctx->Td(51.80, 0.00);
        ctx->Tj("....");
        ctx->Td(15.00, 0.00);
        ctx->Tj(std::to_string(totalVacationDays) + " " + getNominative(totalVacationDays));
        ctx->ET();
    }

    // --- Section 9: Vacation Parts Details ---

    {
        std::string part1 =
            "Prvi dio u trajanju od " + std::to_string(vacationData->firstPartDays) + " radnih dana, od " +
            vacationData->startDate + " godine do " + vacationData->endDate +
            " godine, s tim da se na posao javi " + vacationData->firstDayBack + " godine.";

        std::string part2 =
            "Drugi dio u trajanju od " + std::to_string(vacationData->secondPartDays) + " " +
            getGenitive(vacationData->secondPartDays) +
            " dana, od __. __. ____. godine do __. __. ____. godine, s tim da se na posao "
            "javi __. __. ____. godine.";

        ctx->BT();
        ctx->Td(startX, 398.80);
        ctx->Tj("Radnik će koristiti godišnji odmor u dva dijela:");

        ctx->Td(0.00, -lineHeight * 2.00);
        ctx->Tj("1.");
        drawParagraph(ctx, 18.00, 0.00, part1, timesFont, 12.00, maxWidth - 18.00);

        ctx->Td(-18.00, -lineHeight * 2.00);
        ctx->Tj("2.");
        drawParagraph(ctx, 18.00, 0.00, part2, timesFont, 12.00, maxWidth - 18.00);
        ctx->ET();
    }

    // --- Section 10: Additional Remarks ---
    {
        std::string remarks1 = "U slučaju potreba posla poslodavac može pozvati radnika da prekine godišnji "
                               "odmor i javi se na posao, u kom slučaju će se radniku odrediti novi termin "
                               "korištenja preostalog dijela godišnjeg odmora.";
        std::string remarks2 = "Za vrijeme korištenja godišnjeg odmora radnika će zamjenjivati radnik " +
                               vacationData->substitute + ". Protiv ovog Rješenja radnik može uložiti prigovor " +
                               "poslodavcu, u roku od 30 (trideset) dana od prijema istog.";

        ctx->BT();
        drawParagraph(ctx, startX, 274.60, remarks1, timesFont, 12.00, maxWidth);
        drawParagraph(ctx, 0.00, -lineHeight * 2.00, remarks2, timesFont, 12.00, maxWidth);
        ctx->ET();
    }

    // --- Section 11: Footer ---
    {
        ctx->BT();
        ctx->Td(startX, 164.20);
        ctx->Tj("Dostavljeno");
        ctx->Quote("Radniku");
        ctx->Quote("Računovodstvu");
        ctx->Quote("Dosjeu");
        ctx->ET();
    }

    // --- Section 12: Signature ---
    {
        ctx->BT();
        std::string title = "D I R E K T O R";
        PDFUsedFont::TextMeasures dims = timesFont->CalculateTextDimensions(title, 12.0);
        ctx->Td(357.00, 154.40);
        ctx->Tj(title);
        ctx->ET();

        // Signature line
        ctx->w(0.25);
        ctx->m(357.00 - 25.00, 110.40);
        ctx->l(357.00 + dims.width + 25.00, 110.40);
        ctx->S();
    }

    status = pdfWriter.EndPageContentContext(ctx);
    if (PDFHummus::eSuccess != status)
        return status;

    status = pdfWriter.WritePageAndRelease(pdfPage);
    if (PDFHummus::eSuccess != status)
        return status;

    return PDFHummus::eSuccess;
}
