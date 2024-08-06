#include "winapi_pen_common.h"

COLORREF GetPenColorFromDC(HDC hDC)
{
    if (!hDC)
        return RGB(0, 0, 0);

    COLORREF color = RGB(0, 0, 0);
    LOGPEN lp;
    HPEN hPen = (HPEN)GetCurrentObject(hDC, OBJ_PEN);

    if (hPen)
    {
        GetObject(hPen, sizeof(LOGPEN), &lp);
        color = lp.lopnColor;
    }

    return color;
}