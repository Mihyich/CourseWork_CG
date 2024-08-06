#include "app_args.h"

namespace app
{
    HINSTANCE hInst = nullptr;
    PSTR lpCmdLine = nullptr;
    
    WinApiWindow MainWnd;
    const POINT MinMainWndSize = { 850, 425 };
    
    WinApiWindow ToolbarWnd;
    const LONG ToolbarWidth = 400;

    WinApiWindow clipper_set_wnd;
    HWND clipper_add_hwnd = nullptr;
    HWND clipper_del_hwnd = nullptr;
    HWND clipper_erase_hwnd = nullptr;
    std::vector<HWND> clipper_nomer_hwnd_arr;
    std::vector<HWND> clipper_input_hwnd_arr;

    WinApiWindow poly_set_wnd;
    HWND poly_add_hwnd = nullptr;
    HWND poly_del_hwnd = nullptr;
    HWND poly_erase_hwnd = nullptr;
    std::vector<HWND> poly_nomer_hwnd_arr;
    std::vector<HWND> poly_input_hwnd_arr;

    WinApiWindow DrawAreaWnd;

    WinApiWindow DrawAreaInfoWnd;
    const LONG DrawAreaInfoHeight = 30;
    HWND coordX_info_hwnd = nullptr;
    HWND coordY_info_hwnd = nullptr;
    HWND scale_info_hwnd = nullptr;

    WinApiFont Fonts;
}