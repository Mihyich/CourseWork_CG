#include "toolbar_wnd_proc.h"

void repos_toolbar_child_wnds()
{
    if (!app::ToolbarWnd.getHwnd())
        return;

    RECT rect;
    LONG width;
    LONG height;
    LONG posX = HIT_BORDER_SIZE;
    LONG posY = 30;
    LONG tmp_width = 0;
    LONG tmp_height = 0;

    GetClientRect(app::ToolbarWnd.getHwnd(), &rect);
    width = get_rect_width(rect);
    height = get_rect_height(rect);

    if (app::LightingWnd.getHwnd())
    {
        tmp_width = width - HIT_BORDER_SIZE - HIT_BORDER_SIZE;
        tmp_height = height - 30 - HIT_BORDER_SIZE;

        MoveWindow(
            app::LightingWnd.getHwnd(),
            posX, posY,
            tmp_width, tmp_height,
            TRUE
        );
    }
}

#define IDB_TAB_SHADOW_OPTION 1
#define IDB_TAB_LIGHTING_OPTION 2
#define IDB_TAB_MODEL_OPTION 3
    
LRESULT CALLBACK ToolbarWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static bool resizing = false;
    static POINT lastMousePos;
    static RECT originalRect;

    static FontParam fp;

    static HWND TabShadowOptionHwnd = NULL;
    static HWND TabLightingOptionHwnd = NULL;
    static HWND TabModelOptionHwnd = NULL;

    switch(uMsg)
    {
        case WM_CREATE:
        {
            HDC hDc;
            HFONT hFont;

            TabShadowOptionHwnd = CreateWindow(
                L"BUTTON", L"Тень", 
                WS_VISIBLE | WS_CHILD | BS_PUSHLIKE | BS_CHECKBOX,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_TAB_SHADOW_OPTION, app::hInst, NULL
            );

            TabLightingOptionHwnd = CreateWindow(
                L"BUTTON", L"Освещение", 
                WS_VISIBLE | WS_CHILD | BS_PUSHLIKE | BS_CHECKBOX,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_TAB_LIGHTING_OPTION, app::hInst, NULL
            );

            TabModelOptionHwnd = CreateWindow(
                L"BUTTON", L"Модель", 
                WS_VISIBLE | WS_CHILD | BS_PUSHLIKE | BS_CHECKBOX,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_TAB_SHADOW_OPTION, app::hInst, NULL
            );

            // Создать окно настройки освещения
            app::LightingWnd.Create(
                nullptr, app::hInst, SW_SHOWNORMAL,
                LightingWndProc, L"Lighting", nullptr,
                0, 0,
                CS_HREDRAW | CS_VREDRAW,
                WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPCHILDREN,
                0,
                hWnd
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
                SendMessage(TabShadowOptionHwnd, WM_SETFONT, (WPARAM)hFont, TRUE);
                SendMessage(TabModelOptionHwnd, WM_SETFONT, (WPARAM)hFont, TRUE);

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

            MoveWindow(
                TabShadowOptionHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;

            MoveWindow(
                TabLightingOptionHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;

            MoveWindow(
                TabModelOptionHwnd,
                posX, posY, w, h,
                TRUE
            );

            GetWindowRect(TabShadowOptionHwnd, &tmp_rect);
            tmpFp = fp;
            tmpFp.cHeight = decrease_font_height_for_fitting(hDc, &tmpFp, L"Освещение", get_rect_width(tmp_rect), 20);
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
                SendMessage(TabShadowOptionHwnd, WM_SETFONT, (WPARAM)hFont, TRUE);
                SendMessage(TabLightingOptionHwnd, WM_SETFONT, (WPARAM)hFont, TRUE);
                SendMessage(TabModelOptionHwnd, WM_SETFONT, (WPARAM)hFont, TRUE);
                DeleteObject((HFONT)SelectObject(hDc, (HFONT)hFont));
            }

            ReleaseDC(hWnd, hDc);

            repos_toolbar_child_wnds();
            return EXIT_SUCCESS;
        }

        case WM_LBUTTONDOWN:
        {
            POINT pt;
            RECT rect;

            GetCursorPos(&pt);
            ScreenToClient(hWnd, &pt);
            GetClientRect(hWnd, &rect);

            if (pt.x >= rect.right - HIT_BORDER_SIZE)
            {
                SetCapture(hWnd);
                GetWindowRect(hWnd, &originalRect);
                resizing = true;
                lastMousePos = pt;
            }

            return EXIT_SUCCESS;
        }

        case WM_LBUTTONUP:
        {
            if (resizing)
            {
                ReleaseCapture();
                resizing = false;
            }

            return EXIT_SUCCESS;
        }

        case WM_MOUSEMOVE:
        {
            RECT MainRect;
            POINT pt;
            int dx;

            if (resizing)
            {
                GetCursorPos(&pt);
                ScreenToClient(hWnd, &pt);
                GetWindowRect(app::MainWnd.getHwnd(), &MainRect);
                dx = pt.x - lastMousePos.x;
                app::ToolbarWidth = std::min(std::max(originalRect.right - originalRect.left + dx, app::ToolbarMinWidth), get_rect_width(MainRect));
                SendMessage(app::MainWnd.getHwnd(), WM_SIZE, 0, 0);
                UpdateWindow(app::MainWnd.getHwnd());
            }

            return EXIT_SUCCESS;
        }

        case WM_SETCURSOR:
        {
            POINT pt;
            RECT rect;

            GetCursorPos(&pt);
            ScreenToClient(hWnd, &pt);
            GetClientRect(hWnd, &rect);

            if (pt.x >= rect.right - HIT_BORDER_SIZE)
            {
                SetCursor(LoadCursor(NULL, IDC_SIZEWE));
                return TRUE;
            }

            return DefWindowProc(hWnd, uMsg, wParam, lParam);
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