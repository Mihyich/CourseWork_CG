#include "winapi_pen.h"

WinApiPen::WinApiPen()
{

}

WinApiPen::WinApiPen(HDC hDc)
{
    this->hDc = hDc;
}

void WinApiPen::init(HDC hDc)
{
    this->hDc = hDc;
}

bool WinApiPen::select(HPEN NewPen)
{
    if (!hDc || !NewPen)
        return EXIT_FAILURE;

    if (CurPen)
    {
        DestroyPen();
        SelectObject(hDc, (HPEN)NewPen);
    }
    else
    {
        OldPen = (HPEN)SelectObject(hDc, (HPEN)NewPen);
    }

    CurPen = NewPen;

    return EXIT_SUCCESS;
}

bool WinApiPen::select(int iStyle, int cWidth, COLORREF color)
{
    HPEN NewPen = CreatePen(iStyle, cWidth, color);
    return select(NewPen);
}

bool WinApiPen::select(WinApiPenStruct_p psp)
{
    if (!psp)
    {
        return EXIT_FAILURE;
    }
    else
    {
        return this->select(psp->iStyle, psp->cWidth, psp->color);
    }
}

void WinApiPen::DestroyPen()
{
    if (CurPen)
    {
        DeleteObject(CurPen);
        CurPen = nullptr;
    }
}

WinApiPen::~WinApiPen()
{
    DestroyPen();

    if (this->hDc && this->OldPen)
        SelectObject(this->hDc, (HPEN)this->OldPen);
}