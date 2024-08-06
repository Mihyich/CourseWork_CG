#ifndef WINAPI_PEN_H
#define WINAPI_PEN_H

#include <windows.h>
#include "winapi_pen_struct.h"

class WinApiPen
{
public:

    WinApiPen();

    WinApiPen(HDC hDc);

    void init(HDC hDc);

    bool select(HPEN NewPen);

    bool select(int iStyle, int cWidth, COLORREF color);

    bool select(WinApiPenStruct_p psp);

private:

    void DestroyPen();

public:

    ~WinApiPen();

private:
    HDC hDc = nullptr;
    HPEN CurPen = nullptr;
    HPEN OldPen = nullptr;
};

#endif // WINAPI_PEN_H