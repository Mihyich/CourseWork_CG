#include "winapi_color_common.h"

COLORREF color_interpolation(COLORREF c1, COLORREF c2, float k)
{
    const short R1 = GetRValue(c1);
    const short G1 = GetGValue(c1);
    const short B1 = GetBValue(c1);

    const short R2 = GetRValue(c2);
    const short G2 = GetGValue(c2);
    const short B2 = GetBValue(c2);

    const short dR = R2 - R1;
    const short dG = G2 - G1;
    const short dB = B2 - B1;

    const short nR = R1 + (short)roundf(dR * k);
    const short nG = G1 + (short)roundf(dG * k);
    const short nB = B1 + (short)roundf(dB * k);

    COLORREF color = RGB(nR, nG, nB);

    return color;
}

COLORREF color_reverse(COLORREF color)
{
    BYTE r = GetRValue(color);
    BYTE g = GetGValue(color);
    BYTE b = GetBValue(color);
    return RGB(b, g, r);
}

void reverse_color(COLORREF &color)
{
    BYTE r = GetRValue(color);
    BYTE g = GetGValue(color);
    BYTE b = GetBValue(color);
    color = RGB(b, g, r);
}

void reverse_color_str(COLORREF *sc, COLORREF *ec)
{
    if (!sc || ! ec)
        return;

    while (sc < ec)
    {
        reverse_color(*sc);
        ++sc;
    }
}