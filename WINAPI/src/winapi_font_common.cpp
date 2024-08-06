#include "winapi_font_common.h"

int increase_font_height_for_fitting_width(HDC hDc, FontParam_t fpt, const WCHAR *text, int fit_width)
{
    if (!hDc || !fpt || !text)
        return 0;

    HFONT OldFont = nullptr;
    HFONT CurFont = nullptr;

    FontParam fp = *fpt; ++fp.cHeight;
    WinApiFont Font;
    SIZE text_size;
    const size_t text_lenght = wcslen(text);

    do
    {
        --fp.cHeight;
        CurFont = Font.create_font(&fp);
        OldFont = (HFONT)SelectObject(hDc, (HFONT)CurFont);
        GetTextExtentPoint32(hDc, text, text_lenght, &text_size);
        DeleteObject((HFONT)SelectObject(hDc, (HFONT)OldFont));

    } while (text_size.cx >= fit_width && fp.cHeight > 0);

    return fp.cHeight;
}

int increase_font_height_for_fitting_height(HDC hDc, FontParam_t fpt, const WCHAR *text, int fit_height)
{
    if (!hDc || !fpt || !text)
        return 0;

    HFONT OldFont = nullptr;
    HFONT CurFont = nullptr;

    FontParam fp = *fpt; ++fp.cHeight;
    WinApiFont Font;
    SIZE text_size;
    const size_t text_lenght = wcslen(text);

    do
    {
        --fp.cHeight;
        CurFont = Font.create_font(&fp);
        OldFont = (HFONT)SelectObject(hDc, (HFONT)CurFont);
        GetTextExtentPoint32(hDc, text, text_lenght, &text_size);
        DeleteObject((HFONT)SelectObject(hDc, (HFONT)OldFont));

    } while (text_size.cy >= fit_height && fp.cHeight > 0);

    return fp.cHeight;
}

int increase_font_height_for_fitting(HDC hDc, FontParam_t fpt, const WCHAR *text, int fit_width, int fit_height)
{
    int height_for_fit_width = increase_font_height_for_fitting_width(hDc, fpt, text, fit_width);
    int height_for_fit_height = increase_font_height_for_fitting_height(hDc, fpt, text, fit_height);
    return (height_for_fit_width < height_for_fit_height) ? height_for_fit_width : height_for_fit_height;
}