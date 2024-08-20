#include "winapi_font.h"

bool WinApiFont::is_copy(const wchar_t *font_name) const
{
    return fonts.find(font_name) != fonts.end();
}

HFONT WinApiFont::create_font(FontParam_ct fp)
{
    if (!fp)
        return nullptr;

    return CreateFont(
        fp->cHeight, fp->cWidth,
        fp->cEscapement, fp->cOrientation,
        fp->cWeight, fp->bItalic, fp->bUnderline,
        fp->bStrikeOut, fp->iCharSet,
        fp->iOutPrecision, fp->iClipPrecision,
        fp->iQuality, fp->iPitchAndFamily, fp->pszFaceName
    );
}

HFONT WinApiFont::create_font(int cHeight, const wchar_t *FaceName) const
{
    FontParam fp = 
    {
        cHeight,
        0,
        0,
        0,
        FW_NORMAL,
        FALSE,
        FALSE,
        FALSE,
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS,
        FaceName
    };

    return WinApiFont::create_font(&fp);
}

HFONT WinApiFont::create_font(
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
    ) const
{
    FontParam fp = 
    {
        cHeight,
        cWidth,
        cEscapement,
        cOrientation,
        cWeight,
        bItalic,
        bUnderline,
        bStrikeOut,
        iCharSet,
        iOutPrecision,
        iClipPrecision,
        iQuality,
        iPitchAndFamily,
        pszFaceName
    };

    return WinApiFont::create_font(&fp);
}

DWORD WinApiFont::load_font(FontParam_ct fp, const wchar_t *font_name)
{
    if (is_copy(font_name))
    {
        destroy_font(font_name);
        fonts.erase(font_name);
    }

    DWORD err = ERROR_SUCCESS;
    HFONT hfont = create_font(fp);

    if (!hfont)
        err = GetLastError();

    if (!err)
        this->fonts.insert(std::make_pair(font_name, hfont));

    return err;
}

DWORD WinApiFont::load_font(
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
        const wchar_t *font_name)
{
    FontParam fp = 
    {
        cHeight,
        cWidth,
        cEscapement,
        cOrientation,
        cWeight,
        bItalic,
        bUnderline,
        bStrikeOut,
        iCharSet,
        iOutPrecision,
        iClipPrecision,
        iQuality,
        iPitchAndFamily,
        pszFaceName
    };

    return load_font(&fp, font_name);
}

DWORD WinApiFont::load_font(int cHeight, const wchar_t *FaceName, const wchar_t *font_name)
{
    FontParam fp = 
    {
        cHeight,
        0,
        0,
        0,
        FW_NORMAL,
        FALSE,
        FALSE,
        FALSE,
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS,
        FaceName
    };

    return load_font(&fp, font_name);
}

HFONT WinApiFont::get_font(const wchar_t *font_name) const
{
    HFONT hfont;

    try
    {   
        hfont = fonts.at(font_name);
    }
    catch (const std::out_of_range& e)
    {
        hfont = nullptr;
    }

    return hfont;
}

void WinApiFont::destroy_font(const wchar_t *font_name)
{
    HFONT hFont = get_font(font_name);

    if (hFont)
    {
        DeleteObject((HFONT)hFont);
        hFont = nullptr;
    }
}

void WinApiFont::destroy(void)
{
    for (const auto& pair : fonts)
        if (pair.second)
            DeleteObject(pair.second);
}

WinApiFont::~WinApiFont()
{
    this->destroy();
}