#ifndef WINAPI_FONT_H
#define WINAPI_FONT_H

#include <windows.h>
#include <map>
#include <string>
#include <iostream>
#include "winapi_font_struct.h"

class WinApiFont
{
private:

    bool is_copy(const wchar_t *font_name) const;

public:

    static HFONT create_font(FontParam_ct fp);

    HFONT create_font(int cHeight, const wchar_t *FaceName) const;

    HFONT create_font(
        int cHeight,
        int cWidth,
        int cEscapement,
        int cOrientation,
        int cWeight,
        DWORD bItalic,
        DWORD bUnderline,
        DWORD bStrikeOut,
        DWORD iCharSet,
        DWORD iOutPrecision,
        DWORD iClipPrecision,
        DWORD iQuality,
        DWORD iPitchAndFamily,
        LPCWSTR pszFaceName
    ) const;

    DWORD load_font(FontParam_ct fp, const wchar_t *font_name);

    DWORD load_font(
        int cHeight,
        int cWidth,
        int cEscapement,
        int cOrientation,
        int cWeight,
        DWORD bItalic,
        DWORD bUnderline,
        DWORD bStrikeOut,
        DWORD iCharSet,
        DWORD iOutPrecision,
        DWORD iClipPrecision,
        DWORD iQuality,
        DWORD iPitchAndFamily,
        LPCWSTR pszFaceName,
        const wchar_t *font_name);    

    DWORD load_font(int cHeight, const wchar_t *FaceName, const wchar_t *font_name);

    HFONT get_font(const wchar_t *font_name) const;

    void destroy_font(const wchar_t *font_name);

    void destroy(void);

    ~WinApiFont();

private:
    std::map<std::wstring, HFONT> fonts;
};

#endif // WINAPI_FONT_H