#include "winapi_font_common.h"

void measure_text_line(const WCHAR *text, HDC hDc, HFONT hFont, SIZE &rect)
{
    size_t text_lenght = wcslen(text);
    HFONT OldFont = (HFONT)SelectObject(hDc, (HFONT)hFont);
    GetTextExtentPoint32(hDc, text, text_lenght, &rect);
    SelectObject(hDc, (HFONT)OldFont);
}



int decrease_font_height_for_fitting_width(HDC hDc, FontParam_t fpt, const WCHAR *text, int fit_width)
{
    if (!hDc || !fpt || !text)
        return 0;

    HFONT OldFont = nullptr;
    HFONT CurFont = nullptr;

    FontParam fp = *fpt; ++fp.cHeight;
    SIZE text_size;
    const size_t text_lenght = wcslen(text);

    do
    {
        --fp.cHeight;
        CurFont = WinApiFont::create_font(&fp);
        OldFont = (HFONT)SelectObject(hDc, (HFONT)CurFont);
        GetTextExtentPoint32(hDc, text, text_lenght, &text_size);
        DeleteObject((HFONT)SelectObject(hDc, (HFONT)OldFont));

    } while (text_size.cx >= fit_width && fp.cHeight > 0);

    return fp.cHeight;
}

int decrease_font_height_for_fitting_height(HDC hDc, FontParam_t fpt, const WCHAR *text, int fit_height)
{
    if (!hDc || !fpt || !text)
        return 0;

    HFONT OldFont = nullptr;
    HFONT CurFont = nullptr;

    FontParam fp = *fpt; ++fp.cHeight;
    SIZE text_size;
    const size_t text_lenght = wcslen(text);

    do
    {
        --fp.cHeight;
        CurFont = WinApiFont::create_font(&fp);
        OldFont = (HFONT)SelectObject(hDc, (HFONT)CurFont);
        GetTextExtentPoint32(hDc, text, text_lenght, &text_size);
        DeleteObject((HFONT)SelectObject(hDc, (HFONT)OldFont));

    } while (text_size.cy >= fit_height && fp.cHeight > 0);

    return fp.cHeight;
}

int decrease_font_height_for_fitting(HDC hDc, FontParam_t fpt, const WCHAR *text, int fit_width, int fit_height)
{
    int height_for_fit_width = decrease_font_height_for_fitting_width(hDc, fpt, text, fit_width);
    int height_for_fit_height = decrease_font_height_for_fitting_height(hDc, fpt, text, fit_height);
    return std::min(height_for_fit_width, height_for_fit_height);
}


int increase_font_height_for_fitting_width(HDC hDc, FontParam_t fpt, const WCHAR *text, int fit_width)
{
    if (!hDc || !fpt || !text)
        return 0;

    HFONT OldFont = nullptr;
    HFONT CurFont = nullptr;

    FontParam fp = *fpt; --fp.cHeight;
    SIZE text_size;
    const size_t text_lenght = wcslen(text);

    do
    {
        ++fp.cHeight;
        CurFont = WinApiFont::create_font(&fp);
        OldFont = (HFONT)SelectObject(hDc, (HFONT)CurFont);
        GetTextExtentPoint32(hDc, text, text_lenght, &text_size);
        DeleteObject((HFONT)SelectObject(hDc, (HFONT)OldFont));

    } while (text_size.cx <= fit_width && fp.cHeight > 0);

    return fp.cHeight;
}

int increase_font_height_for_fitting_height(HDC hDc, FontParam_t fpt, const WCHAR *text, int fit_height)
{
    if (!hDc || !fpt || !text)
        return 0;

    HFONT OldFont = nullptr;
    HFONT CurFont = nullptr;

    FontParam fp = *fpt; --fp.cHeight;
    SIZE text_size;
    const size_t text_lenght = wcslen(text);

    do
    {
        ++fp.cHeight;
        CurFont = WinApiFont::create_font(&fp);
        OldFont = (HFONT)SelectObject(hDc, (HFONT)CurFont);
        GetTextExtentPoint32(hDc, text, text_lenght, &text_size);
        DeleteObject((HFONT)SelectObject(hDc, (HFONT)OldFont));

    } while (text_size.cy <= fit_height && fp.cHeight > 0);

    return fp.cHeight;
}

int increase_font_height_for_fitting(HDC hDc, FontParam_t fpt, const WCHAR *text, int fit_width, int fit_height)
{
    int height_for_fit_width = increase_font_height_for_fitting_width(hDc, fpt, text, fit_width);
    int height_for_fit_height = increase_font_height_for_fitting_height(hDc, fpt, text, fit_height);
    return std::min(height_for_fit_width, height_for_fit_height);
}