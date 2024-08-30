#include "shadow_wnd_proc.h"

void repos_shadow_child_wnds()
{
    if (!app::ShadowWnd.getHwnd())
        return;

    RECT rect;
    LONG width;
    LONG height;
    LONG posX = 0;
    LONG posY = 30;
    LONG tmp_width = 0;
    LONG tmp_height = 0;

    HWND hwnd1 = app::ShadowMapWnd.getHwnd();
    HWND hwnd2 = app::RayTracingWnd.getHwnd();
    HWND hwnd3 = app::PathTracingWnd.getHwnd();

    GetClientRect(app::ShadowWnd.getHwnd(), &rect);
    width = get_rect_width(rect);
    height = get_rect_height(rect);

    if (hwnd1 && hwnd2 && hwnd3)
    {
        tmp_width = width;
        tmp_height = height;

        MoveWindow(
            hwnd1,
            posX, posY,
            tmp_width, tmp_height,
            TRUE
        );

        MoveWindow(
            hwnd2,
            posX, posY,
            tmp_width, tmp_height,
            TRUE
        );

        MoveWindow(
            hwnd3,
            posX, posY,
            tmp_width, tmp_height,
            TRUE
        );
    }
}

#define IDB_TAB_SHADOW_MAP_OPTION 1
#define IDB_TAB_RAY_TRACING_OPTION 2
#define IDB_TAB_PATH_TRACING_OPTION 3

LRESULT CALLBACK ShadowWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static FontParam fp;
    static HFONT font = NULL;

    static HWND TabShadowMapOptionHwnd = NULL;
    static HWND TabRayTracingOptionHwnd = NULL;
    static HWND TabPathTracingOptionHwnd = NULL;

    switch(uMsg)
    {
        case WM_CREATE:
        {
            TabShadowMapOptionHwnd = CreateWindow(
                L"BUTTON", L"Теневые карты", 
                WS_VISIBLE | WS_CHILD | BS_PUSHLIKE | BS_CHECKBOX,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_TAB_SHADOW_MAP_OPTION, app::hInst, NULL
            );

            TabRayTracingOptionHwnd = CreateWindow(
                L"BUTTON", L"Трассировка лучей", 
                WS_VISIBLE | WS_CHILD | BS_PUSHLIKE | BS_CHECKBOX,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_TAB_RAY_TRACING_OPTION, app::hInst, NULL
            );

            TabPathTracingOptionHwnd = CreateWindow(
                L"BUTTON", L"Трассировка путей", 
                WS_VISIBLE | WS_CHILD | BS_PUSHLIKE | BS_CHECKBOX,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_TAB_PATH_TRACING_OPTION, app::hInst, NULL
            );

            // Создать окно настройки ShadowMap
            app::ShadowMapWnd.Create(
                nullptr, app::hInst, SW_SHOWNORMAL,
                ShadowMapWndProc, L"ShadowMaping", nullptr,
                0, 0,
                CS_HREDRAW | CS_VREDRAW,
                WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPCHILDREN,
                WS_EX_COMPOSITED,
                hWnd
            );

            // Создать окно настройки RayTracing
            app::RayTracingWnd.Create(
                nullptr, app::hInst, SW_HIDE,
                RayTracingWndProc, L"RayTracing", nullptr,
                0, 0,
                CS_HREDRAW | CS_VREDRAW,
                WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPCHILDREN,
                WS_EX_COMPOSITED,
                hWnd
            );

            // Создать окно настройки PathTracing
            app::PathTracingWnd.Create(
                nullptr, app::hInst, SW_HIDE,
                PathTracingWndProc, L"PathTracing", nullptr,
                0, 0,
                CS_HREDRAW | CS_VREDRAW,
                WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPCHILDREN,
                WS_EX_COMPOSITED,
                hWnd
            );

            // По умолчанию вкладка - ShadowMap
            SendMessage(hWnd, WM_COMMAND, MAKEWPARAM(IDB_TAB_SHADOW_MAP_OPTION, 0), 0);

            fp.cWidth = 0;
            fp.cHeight = 24;
            fp.cEscapement = 0;
            fp.cOrientation = 0;
            fp.cWeight = FW_NORMAL;
            fp.bItalic = FALSE;
            fp.bUnderline = FALSE;
            fp.bStrikeOut = FALSE;
            fp.iCharSet = DEFAULT_CHARSET;
            fp.iOutPrecision = OUT_OUTLINE_PRECIS;
            fp.iClipPrecision = CLIP_DEFAULT_PRECIS;
            fp.iQuality = CLEARTYPE_QUALITY;
            fp.iPitchAndFamily = FIXED_PITCH;
            fp.pszFaceName = L"Arial";

            return EXIT_SUCCESS;
        }

        case WM_SIZE:
        {
            HDC hDc = GetDC(hWnd);
            HFONT hFont;
            RECT tmp_rect;
            FontParam tmpFp;

            GetClientRect(hWnd, &tmp_rect);

            int posX = 0;
            int posY = 0;
            int w = get_rect_width(tmp_rect) / 3;
            int h = 20;

            MoveWindow(
                TabShadowMapOptionHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;

            MoveWindow(
                TabRayTracingOptionHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;

            MoveWindow(
                TabPathTracingOptionHwnd,
                posX, posY, w, h,
                TRUE
            );

            GetWindowRect(TabShadowMapOptionHwnd, &tmp_rect);
            tmpFp = fp;
            tmpFp.cHeight = decrease_font_height_for_fitting(hDc, &tmpFp, L"Трассировка путей", get_rect_width(tmp_rect), 20);
            hFont = WinApiFont::create_font(&tmpFp);
            if (hFont)
            {
                font = hFont;

                SendMessage(TabShadowMapOptionHwnd, WM_SETFONT, (WPARAM)font, TRUE);
                SendMessage(TabRayTracingOptionHwnd, WM_SETFONT, (WPARAM)font, TRUE);
                SendMessage(TabPathTracingOptionHwnd, WM_SETFONT, (WPARAM)font, TRUE);
            }

            ReleaseDC(hWnd, hDc);
            repos_shadow_child_wnds();
            return EXIT_SUCCESS;
        }

        case WM_COMMAND:
        {                
            switch (LOWORD(wParam))
            {
                case IDB_TAB_SHADOW_MAP_OPTION:
                {
                    SetFocus(hWnd);

                    SendMessage(TabShadowMapOptionHwnd, BM_SETCHECK, BST_CHECKED, 0);
                    SendMessage(TabRayTracingOptionHwnd, BM_SETCHECK, BST_UNCHECKED, 0);
                    SendMessage(TabPathTracingOptionHwnd, BM_SETCHECK, BST_UNCHECKED, 0);

                    ShowWindow(app::ShadowMapWnd.getHwnd(), SW_SHOW);
                    ShowWindow(app::RayTracingWnd.getHwnd(), SW_HIDE);
                    ShowWindow(app::PathTracingWnd.getHwnd(), SW_HIDE);

                    return EXIT_SUCCESS;
                }

                case IDB_TAB_RAY_TRACING_OPTION:
                {
                    SetFocus(hWnd);

                    SendMessage(TabShadowMapOptionHwnd, BM_SETCHECK, BST_UNCHECKED, 0);
                    SendMessage(TabRayTracingOptionHwnd, BM_SETCHECK, BST_CHECKED, 0);
                    SendMessage(TabPathTracingOptionHwnd, BM_SETCHECK, BST_UNCHECKED, 0);

                    ShowWindow(app::ShadowMapWnd.getHwnd(), SW_HIDE);
                    ShowWindow(app::RayTracingWnd.getHwnd(), SW_SHOW);
                    ShowWindow(app::PathTracingWnd.getHwnd(), SW_HIDE);

                    return EXIT_SUCCESS;
                }

                case IDB_TAB_PATH_TRACING_OPTION:
                {
                    SetFocus(hWnd);

                    SendMessage(TabShadowMapOptionHwnd, BM_SETCHECK, BST_UNCHECKED, 0);
                    SendMessage(TabRayTracingOptionHwnd, BM_SETCHECK, BST_UNCHECKED, 0);
                    SendMessage(TabPathTracingOptionHwnd, BM_SETCHECK, BST_CHECKED, 0);

                    ShowWindow(app::ShadowMapWnd.getHwnd(), SW_HIDE);
                    ShowWindow(app::RayTracingWnd.getHwnd(), SW_HIDE);
                    ShowWindow(app::PathTracingWnd.getHwnd(), SW_SHOW);

                    return EXIT_SUCCESS;
                }

                default:
                    return EXIT_SUCCESS;
            }
        }

        case WM_DESTROY:
        {
            HDC hDc = GetDC(hWnd);

            if (font) DeleteObject((HFONT)SelectObject(hDc, (HFONT)font));

            ReleaseDC(hWnd, hDc);

            return DefWindowProc(hWnd, uMsg, wParam, lParam);    
        }

        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}