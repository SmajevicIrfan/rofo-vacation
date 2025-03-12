#include "PDFLayout.h"

#include <sstream>
#include <vector>

// Helper function that wraps text into lines no wider than maxWidth.
// It uses the provided font and fontSize to calculate the width.
std::vector<std::string> wrapText(const std::string &text,
                                  PDFUsedFont *font,
                                  double fontSize,
                                  double maxWidth)
{
    std::vector<std::string> lines;
    std::istringstream iss(text);
    std::string word;
    std::string currentLine;

    while (iss >> word)
    {
        if (currentLine.empty())
        {
            currentLine = word;
            continue;
        }

        // Test if appending the new word exceeds maxWidth.
        std::string testLine = currentLine + " " + word;
        PDFUsedFont::TextMeasures dims = font->CalculateTextDimensions(testLine, fontSize);
        if (dims.width <= maxWidth)
        {
            currentLine = testLine;
        }
        else
        {
            lines.push_back(currentLine);
            currentLine = word;
        }
    }

    if (!currentLine.empty())
        lines.push_back(currentLine);

    return lines;
}

void PDFLayout::drawBlock(PageContentContext *ctx,
                          double x, double y,
                          const std::string &text,
                          PDFUsedFont *font,
                          double fontSize)
{
    ctx->BT();
    if (font && fontSize > 0.00)
        ctx->Tf(font, fontSize);
    ctx->Td(x, y);
    ctx->Tj(text);
    ctx->ET();
}

void PDFLayout::drawCenteredBlock(PageContentContext *ctx,
                                  double x, double y,
                                  const std::string &text,
                                  PDFUsedFont *font,
                                  double fontSize)
{
    PDFUsedFont::TextMeasures dims = font->CalculateTextDimensions(text, fontSize);
    drawBlock(ctx, x - dims.width / 2.0, y, text);
}

void PDFLayout::drawRightAlignedBlock(PageContentContext *ctx,
                                      double x, double y,
                                      const std::string &text,
                                      PDFUsedFont *font,
                                      double fontSize)
{
    PDFUsedFont::TextMeasures dims = font->CalculateTextDimensions(text, fontSize);
    drawBlock(ctx, x - dims.width, y, text);
}

void PDFLayout::drawParagraph(PageContentContext *ctx,
                              double x, double y,
                              const std::string &text,
                              PDFUsedFont *font,
                              double fontSize,
                              double maxWidth)
{
    std::vector<std::string> lines = wrapText(text, font, fontSize, maxWidth);
    if (lines.empty())
        return;

    ctx->Td(x, y);
    ctx->Tj(lines[0]);
    for (size_t i = 1; i < lines.size(); ++i)
        ctx->Quote(lines[i]);
}
