#include "winapi_choose_color_dialog.h"

bool choose_color_dialog(HWND hwnd, COLORREF *rs)
{
    if (!hwnd || !rs)
        return false;

    bool rt;
    CHOOSECOLOR cc;
    COLORREF acrCustClr[16];

    // Заполнение структуры CHOOSECOLOR
    ZeroMemory(&cc, sizeof(cc));
    cc.lStructSize = sizeof(cc);
    cc.hwndOwner = hwnd; // Дескриптор родительского окна
    cc.lpCustColors = (LPDWORD)acrCustClr;
    cc.rgbResult = *rs;
    cc.Flags = CC_RGBINIT | CC_ANYCOLOR; // Устанавливаем только флаг CC_RGBINIT

    // Открытие диалога выбора цвета
    if (ChooseColor(&cc) == TRUE)
    {
        *rs = cc.rgbResult & 0x00FFFFFF;
        rt = true;
    }
    else
    {
        rt = false;
    }

    return rt;
}