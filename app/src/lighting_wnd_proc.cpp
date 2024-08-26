#include "lighting_wnd_proc.h"

#define IDB_COMBOBOX_LIGHT 1

LRESULT CALLBACK LightingWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static RECT rect;
    static FontParam fp;

    static HWND StaticLightTypeHwnd = NULL;
    static HWND ComboBoxLightHwnd = NULL;

    static HWND StaticPositionHwnd = NULL;
    static HWND StaticPosXHwnd = NULL;
    static HWND StaticPosYHwnd = NULL;
    static HWND StaticPosZHwnd = NULL;

    static HWND StaticDirectionHwnd = NULL;

    static HWND StaticColor = NULL;

    static HWND StaticRadius = NULL;

    static HWND StaticIntensity = NULL;

    static HWND StaticInnerCutoff = NULL;

    static HWND StaticOuterCutoff = NULL;


    static WCHAR tmpText[MAX_PATH];

    switch(uMsg)
    {
        case WM_CREATE:
        {
            HDC hDc;
            HFONT hFont;

            StaticLightTypeHwnd = CreateWindow(
                L"STATIC", L"Источник:", 
                WS_VISIBLE | WS_CHILD,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            ComboBoxLightHwnd = CreateWindowEx(
                0, L"COMBOBOX", L"",
                WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_HASSTRINGS,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_COMBOBOX_LIGHT, app::hInst, nullptr
            );

            StaticPositionHwnd = CreateWindow(
                L"STATIC", L"Позиция:", 
                WS_VISIBLE | WS_CHILD,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            StaticPosXHwnd = CreateWindow(
                L"STATIC", L"X", 
                WS_VISIBLE | WS_CHILD,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            StaticPosYHwnd = CreateWindow(
                L"STATIC", L"Y", 
                WS_VISIBLE | WS_CHILD,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            StaticPosZHwnd = CreateWindow(
                L"STATIC", L"Z", 
                WS_VISIBLE | WS_CHILD,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            StaticDirectionHwnd = CreateWindow(
                L"STATIC", L"Направление:", 
                WS_VISIBLE | WS_CHILD,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            StaticColor = CreateWindow(
                L"STATIC", L"Цвет:", 
                WS_VISIBLE | WS_CHILD,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            StaticRadius = CreateWindow(
                L"STATIC", L"Радиус:", 
                WS_VISIBLE | WS_CHILD,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            StaticIntensity = CreateWindow(
                L"STATIC", L"Интенсивность:", 
                WS_VISIBLE | WS_CHILD,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            StaticInnerCutoff = CreateWindow(
                L"STATIC", L"Внутренний обод:", 
                WS_VISIBLE | WS_CHILD,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            StaticOuterCutoff = CreateWindow(
                L"STATIC", L"Внешний обод:", 
                WS_VISIBLE | WS_CHILD,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

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
            SIZE tmp_size;
            FontParam tmpFp;
            int mainH = fp.cHeight;

            GetClientRect(hWnd, &rect);

            int posX = 0;
            int posY = 0;
            int w = get_rect_width(rect) / 4;
            int h = 30;
            int hgap = 2;

            MoveWindow(
                StaticLightTypeHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = get_rect_width(rect) - w;

            SetWindowPos(
                ComboBoxLightHwnd, nullptr,
                posX, posY, w, h + 200,
                SWP_NOZORDER | SWP_NOACTIVATE);

            posX = 0;
            posY += h + hgap + 5;
            w = get_rect_width(rect) / 4;

            MoveWindow(
                StaticPositionHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX = 0;
            posY += h + hgap;
            w = get_rect_width(rect) / 4;

            MoveWindow(
                StaticDirectionHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX = 0;
            posY += h + hgap;
            w = get_rect_width(rect) / 4;

            MoveWindow(
                StaticColor,
                posX, posY, w, h,
                TRUE
            );

            posX = 0;
            posY += h + hgap;
            w = get_rect_width(rect) / 4;

            MoveWindow(
                StaticRadius,
                posX, posY, w, h,
                TRUE
            );

            posX = 0;
            posY += h + hgap;
            w = get_rect_width(rect) / 4;

            MoveWindow(
                StaticIntensity,
                posX, posY, w, h,
                TRUE
            );

            posX = 0;
            posY += h + hgap;
            w = get_rect_width(rect) / 4;

            MoveWindow(
                StaticInnerCutoff,
                posX, posY, w, h,
                TRUE
            );

            posX = 0;
            posY += h + hgap;
            w = get_rect_width(rect) / 4;

            MoveWindow(
                StaticOuterCutoff,
                posX, posY, w, h,
                TRUE
            );

            GetWindowRect(StaticLightTypeHwnd, &tmp_rect);
            // GetWindowText(StaticLightTypeHwnd, tmpText, MAX_PATH);
            tmpFp = fp;
            tmpFp.cHeight = decrease_font_height_for_fitting(hDc, &tmpFp, L"Внутренний обод:", get_rect_width(tmp_rect), 20);
            hFont = WinApiFont::create_font(&tmpFp);
            if (hFont)
            {
                mainH = std::min(tmpFp.cHeight, mainH);
                DeleteObject((HFONT)SelectObject(hDc, (HFONT)hFont));
            }

            tmpFp.cHeight = mainH;
            hFont = WinApiFont::create_font(&tmpFp);
            if (hFont)
            {
                SendMessage(StaticLightTypeHwnd, WM_SETFONT, (WPARAM)hFont, TRUE);
                SendMessage(ComboBoxLightHwnd, WM_SETFONT, (WPARAM)hFont, TRUE);

                SendMessage(StaticPositionHwnd, WM_SETFONT, (WPARAM)hFont, TRUE);
                // SendMessage(StaticPosXHwnd, WM_SETFONT, (WPARAM)hFont, TRUE);
                // SendMessage(StaticPosYHwnd, WM_SETFONT, (WPARAM)hFont, TRUE);
                // SendMessage(StaticPosZHwnd, WM_SETFONT, (WPARAM)hFont, TRUE);
                SendMessage(StaticDirectionHwnd, WM_SETFONT, (WPARAM)hFont, TRUE);
                SendMessage(StaticColor, WM_SETFONT, (WPARAM)hFont, TRUE);
                SendMessage(StaticRadius, WM_SETFONT, (WPARAM)hFont, TRUE);
                SendMessage(StaticIntensity, WM_SETFONT, (WPARAM)hFont, TRUE);
                SendMessage(StaticInnerCutoff, WM_SETFONT, (WPARAM)hFont, TRUE);
                SendMessage(StaticOuterCutoff, WM_SETFONT, (WPARAM)hFont, TRUE);

                DeleteObject((HFONT)SelectObject(hDc, (HFONT)hFont));
            }

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