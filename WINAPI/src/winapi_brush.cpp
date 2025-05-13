#include "winapi_brush.h"

WinApiBrush::WinApiBrush()
{

}

WinApiBrush::WinApiBrush(HDC hDc)
{
    this->hDc = hDc;
}

void WinApiBrush::init(HDC hDc)
{
    this->hDc = hDc;
}

bool WinApiBrush::select(HBRUSH NewBrush)
{
    if (!hDc || !NewBrush)
        return EXIT_FAILURE;

    if (CurBrush)
    {
        DestroyBrush();
        SelectObject(hDc, (HBRUSH)NewBrush);
    }
    else
    {
        OldBrush = (HBRUSH)SelectObject(hDc, (HBRUSH)NewBrush);
    }

    CurBrush = NewBrush;

    return EXIT_SUCCESS;
}

bool WinApiBrush::select_solid(COLORREF color)
{
    HBRUSH NewBrush = CreateSolidBrush(color);
    return select(NewBrush);
}

bool WinApiBrush::select_hatch(int iHatch, COLORREF color)
{
    HBRUSH NewBrush = CreateHatchBrush(iHatch, color);
    return select(NewBrush);
}

bool WinApiBrush::select_pattern(HBITMAP hbm)
{
    if (!hbm)
        return EXIT_FAILURE;

    HBRUSH NewBrush = CreatePatternBrush(hbm);
    return select(NewBrush);
}

bool WinApiBrush::select(WinApiBrushSolidStruct_p bssp)
{
    if (!bssp)
    {
        return EXIT_FAILURE;
    }
    else
    {
        return select_solid(bssp->color);
    }
}

bool WinApiBrush::select(WinApiBrushHatchStruct_p bhsp)
{
    if (!bhsp)
    {
        return EXIT_FAILURE;
    }
    else
    {
        return select_hatch(bhsp->iHatch, bhsp->color);
    }
}

bool WinApiBrush::select(WinApiBrushPatternStruct_p bpsp)
{
    if (!bpsp)
    {
        return EXIT_FAILURE;
    }
    else
    {
        return select_pattern(bpsp->hbm);
    }
}

bool WinApiBrush::select(WinApiBrushType type, WinApiBrushUnion_p bup)
{
    if (!bup)
        return EXIT_FAILURE;

    bool err;

    switch (type)
    {
        case BRUSH_TYPE_SOLID:
        {
            select(&bup->Solid);
            break;
        }

        case BRUSH_TYPE_HATCH:
        {
            select(&bup->Hatch);
            break;
        }

        case BRUSH_TYPE_PATTERN:
        {
            select(&bup->Pattern);
            break;
        }
        
        case BRUSH_TYPE_UNDEF:
        default:
        {
            err = EXIT_FAILURE;
            break;
        }
    }

    return err;
}

bool WinApiBrush::select(WinApiBrushStruct_p bsp)
{   
    if (!bsp)
    {
        return EXIT_FAILURE;
    }
    else
    {
        return select(bsp->type, &bsp->brush);
    }
}

void WinApiBrush::DestroyBrush()
{
    if (CurBrush)
    {
        DeleteObject((HBRUSH)CurBrush);
        CurBrush = nullptr;
    }
}

WinApiBrush::~WinApiBrush()
{
    DestroyBrush();

    if (hDc && OldBrush)
        SelectObject(hDc, (HBRUSH)OldBrush);
}