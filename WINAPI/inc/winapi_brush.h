#ifndef WINAPI_BRUSH_H
#define WINAPI_BRUSH_H

#include <windows.h>
#include "winapi_brush_struct.h"

class WinApiBrush
{
public:

    WinApiBrush();

    WinApiBrush(HDC hDc);

    void init(HDC hDc);

public:

    bool select(HBRUSH NewBrush);

    bool select_solid(COLORREF color);

    bool select_hatch(int iHatch, COLORREF color);

    bool select_pattern(HBITMAP hbm);

    bool select(WinApiBrushSolidStruct_p bssp);

    bool select(WinApiBrushHatchStruct_p bhsp);

    bool select(WinApiBrushPatternStruct_p bpsp);

    bool select(WinApiBrushType type, WinApiBrushUnion_p bup);

    bool select(WinApiBrushStruct_p bsp);

private:

    void DestroyBrush();

public:

    ~WinApiBrush();

private:
    HDC hDc = nullptr;
    HBRUSH CurBrush = nullptr;
    HBRUSH OldBrush = nullptr;
};

#endif // WINAPI_BRUSH_H