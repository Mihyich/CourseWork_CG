#include "lighting_wnd_proc.h"

#define IDB_COMBOBOX_LIGHT 1

LRESULT CALLBACK LightingWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static FontParam fp;

    static HWND StaticLightTypeHwnd = NULL;
    static HWND ComboBoxLightHwnd = NULL;

    static WCHAR tmpText[MAX_PATH];

    switch(uMsg)
    {
        case WM_CREATE:
        {
            HDC hDc;
            HFONT hFont;

            StaticLightTypeHwnd = CreateWindow(
                L"BUTTON", L"Источник", 
                WS_VISIBLE | WS_CHILD | BS_PUSHLIKE | BS_CHECKBOX,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            ComboBoxLightHwnd = CreateWindowEx(
                0, L"COMBOBOX", L"", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_HASSTRINGS,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_COMBOBOX_LIGHT, app::hInst, nullptr);


            fp.cWidth = 0;
            fp.cHeight = 24;
            fp.cEscapement = 0;
            fp.cOrientation = 0;
            fp.cWeight = FW_NORMAL,
            fp.bItalic = FALSE;
            fp.bUnderline = FALSE;
            fp.bStrikeOut = FALSE;
            fp.iCharSet = DEFAULT_CHARSET,
            fp.iOutPrecision = OUT_OUTLINE_PRECIS,
            fp.iClipPrecision = CLIP_DEFAULT_PRECIS,
            fp.iQuality = CLEARTYPE_QUALITY,
            fp.iPitchAndFamily = VARIABLE_PITCH,
            fp.pszFaceName = L"Arial";

            hFont = WinApiFont::create_font(&fp);

            if (hFont)
            {
                SendMessage(StaticLightTypeHwnd, WM_SETFONT, (WPARAM)hFont, TRUE);
                SendMessage(ComboBoxLightHwnd, WM_SETFONT, (WPARAM)hFont, TRUE);

                hDc = GetDC(hWnd);
                DeleteObject((HFONT)SelectObject(hDc, (HFONT)hFont));
                ReleaseDC(hWnd, hDc);
            }

            return EXIT_SUCCESS;
        }

        case WM_SIZE:
        {
            HDC hDc = GetDC(hWnd);
            HFONT hFont;
            RECT tmp_rect;
            FontParam tmpFp;
            int mainH = fp.cHeight;

            int posX = 0;
            int posY = 0;
            int w = app::ToolbarWidth / 3;
            int h = 20;

            ReleaseDC(hWnd, hDc);

            return EXIT_SUCCESS;
        }

        case WM_COMMAND:
        {                
            switch (LOWORD(wParam))
            {
                default:
                    return EXIT_SUCCESS;
            }
        }

        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}