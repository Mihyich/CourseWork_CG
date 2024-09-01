#include "shadowMap_wnd_proc.h"

#define IDB_COMBOBOX_ALGORITM 1

#define IDB_EDIT_RES_X 2
#define IDB_EDIT_RES_Y 3
#define IDB_BUTTON_RES 4

#define IDB_EDIT_BIAS 5
#define IDB_EDIT_PCF_RADIUS 6
#define IDB_EDIT_EXP_K 7

#define IDB_TAB_RENDER_DEBUG 8
#define IDB_TAB_RENDER_RELEASE 9

LRESULT CALLBACK ShadowMapWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static RECT rect;

    static FontParam fp;

    static HWND StaticAlgoritmHwnd = NULL;
    static HWND ComboBoxAlgoritnHwnd = NULL;

    static HWND StaticResolutionHwnd = NULL;
    static HWND StaticResolutionXHwnd = NULL;
    static HWND EditResolutionXHwnd = NULL;
    static HWND StaticResolutionYHwnd = NULL;
    static HWND EditResolutionYHwnd = NULL;
    static HWND ButtonResolutionHwnd = NULL;

    static HWND StaticBiasHwnd = NULL;
    static HWND StaticBiasValHwnd = NULL;
    static HWND EditBiasValHwnd = NULL;

    static HWND StaticPcfRadiusHwnd = NULL;
    static HWND StaticPcfRadiusValHwnd = NULL;
    static HWND EditPcfRadiusValHwnd = NULL;

    static HWND StaticExpKHwnd = NULL;
    static HWND StaticExpKValHwnd = NULL;
    static HWND EditExpKValHwnd = NULL;

    static HWND StaticProjectionHwnd = NULL;
    static HWND ComboBoxProjectionHwnd = NULL;

    static HWND StaticRenderHwnd = NULL;
    static HWND TabRenderDebugHwnd = NULL;
    static HWND TabRenderReleaseHwnd = NULL;

    switch(uMsg)
    {
        case WM_CREATE:
        {
            StaticAlgoritmHwnd = CreateWindow(
                L"STATIC", L"Алгоритм:", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            ComboBoxAlgoritnHwnd = CreateWindow(
                L"COMBOBOX", L"",
                WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_HASSTRINGS,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_COMBOBOX_ALGORITM, app::hInst, nullptr
            );

            StaticResolutionHwnd = CreateWindow(
                L"STATIC", L"Разрешение:", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            StaticResolutionXHwnd = CreateWindow(
                L"STATIC", L"X", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            EditResolutionXHwnd = CreateWindow(
                L"EDIT", L"1920",
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_EDIT_RES_X, app::hInst, nullptr
            );

            StaticResolutionYHwnd = CreateWindow(
                L"STATIC", L"Y", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            EditResolutionYHwnd = CreateWindow(
                L"EDIT", L"1080",
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_EDIT_RES_Y, app::hInst, nullptr
            );

            ButtonResolutionHwnd = CreateWindow(
                L"BUTTON", L"Обновить",
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHLIKE | BS_CENTER | BS_VCENTER,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_BUTTON_RES, app::hInst, nullptr
            );

            StaticBiasHwnd = CreateWindow(
                L"STATIC", L"Смещение:", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            StaticBiasValHwnd = CreateWindow(
                L"STATIC", L"B", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            EditBiasValHwnd = CreateWindow(
                L"EDIT", L"0.005",
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_EDIT_BIAS, app::hInst, nullptr
            );

            StaticPcfRadiusHwnd = CreateWindow(
                L"STATIC", L"Радиус PCF:", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            StaticPcfRadiusValHwnd = CreateWindow(
                L"STATIC", L"R", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            EditPcfRadiusValHwnd = CreateWindow(
                L"EDIT", L"1.5",
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_EDIT_EXP_K, app::hInst, nullptr
            );

            StaticExpKHwnd = CreateWindow(
                L"STATIC", L"Коэф. ExpK:", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            StaticExpKValHwnd = CreateWindow(
                L"STATIC", L"E", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            EditExpKValHwnd = CreateWindow(
                L"EDIT", L"1.0",
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_EDIT_EXP_K, app::hInst, nullptr
            );

            StaticProjectionHwnd = CreateWindow(
                L"STATIC", L"Алгоритм:", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            ComboBoxProjectionHwnd = CreateWindow(
                L"COMBOBOX", L"",
                WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_HASSTRINGS,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_COMBOBOX_ALGORITM, app::hInst, nullptr
            );

            StaticRenderHwnd = CreateWindow(
                L"STATIC", L"Рендер:", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            TabRenderDebugHwnd = CreateWindow(
                L"BUTTON", L"Отладка", 
                WS_VISIBLE | WS_CHILD | BS_PUSHLIKE | BS_CHECKBOX,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_TAB_RENDER_DEBUG, app::hInst, NULL
            );

            TabRenderReleaseHwnd = CreateWindow(
                L"BUTTON", L"Релиз", 
                WS_VISIBLE | WS_CHILD | BS_PUSHLIKE | BS_CHECKBOX,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_TAB_RENDER_RELEASE, app::hInst, NULL
            );

            // Окно общих настроек
            app::GeneralShadowOptionsWnd.Create(
                nullptr, app::hInst, SW_SHOWNORMAL,
                GeneralShadowOptionsWndProc, L"GeneralShadowOption", nullptr,
                0, 0,
                CS_HREDRAW | CS_VREDRAW,
                WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPCHILDREN,
                WS_EX_COMPOSITED,
                hWnd
            );

            SendMessage(ComboBoxAlgoritnHwnd, CB_ADDSTRING, (WPARAM)0, (LPARAM)L"ShadowMap");
            SendMessage(ComboBoxAlgoritnHwnd, CB_ADDSTRING, (WPARAM)0, (LPARAM)L"ShadowMap PCF");
            SendMessage(ComboBoxAlgoritnHwnd, CB_ADDSTRING, (WPARAM)0, (LPARAM)L"ShadowMap ESM");
            SendMessage(ComboBoxAlgoritnHwnd, CB_ADDSTRING, (WPARAM)0, (LPARAM)L"ShadowMap VSM");
            SendMessage(ComboBoxAlgoritnHwnd, CB_SETCURSEL, (WPARAM)0, 0);
            // SendMessage(hWnd, WM_COMMAND, MAKEWPARAM(CBN_SELCHANGE, IDB_COMBOBOX_ALGORITM), (LPARAM)ComboBoxAlgoritnHwnd);

            fp.cWidth = 0;
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

            return EXIT_SUCCESS;
        }

        case WM_SIZE:
        {
            HDC hDc = GetDC(hWnd);
            HFONT hFont;
            RECT tmp_rect;
            FontParam tmpFp;
            int mainH = 24;

            GetClientRect(hWnd, &rect);

            int hgap = 2;
            int posX = 0;
            int posY = 0;
            int w = get_rect_width(rect) / 4;
            int h = std::min(30, std::max(((int)get_rect_height(rect) - 9 * hgap - 5 - 5 - 30) / 10, 20));

            MoveWindow(
                StaticAlgoritmHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = get_rect_width(rect) - w;

            MoveWindow(
                ComboBoxAlgoritnHwnd,
                posX, posY, w, h + 200,
                FALSE);

            posX = 0;
            posY += h + hgap + 5;
            w = get_rect_width(rect) / 4;

            MoveWindow(
                StaticResolutionHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = std::min((int)get_rect_width(rect) / 4 * 3 / 3 / 4, h);

            MoveWindow(
                StaticResolutionXHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = (int)get_rect_width(rect) / 4 * 3 / 3 - w;

            MoveWindow(
                EditResolutionXHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = std::min((int)get_rect_width(rect) / 4 * 3 / 3 / 4, h);

            MoveWindow(
                StaticResolutionYHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = (int)get_rect_width(rect) / 4 * 3 / 3 - w;

            MoveWindow(
                EditResolutionYHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = (int)get_rect_width(rect) / 4 * 3 / 3;

            MoveWindow(
                ButtonResolutionHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX = 0;
            posY += h + hgap;
            w = get_rect_width(rect) / 4;

            MoveWindow(
                StaticBiasHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = std::min((int)get_rect_width(rect) / 4 * 3 / 3 / 4, h);

            MoveWindow(
                StaticBiasValHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = (int)get_rect_width(rect) / 4 * 3 / 3 - w;

            MoveWindow(
                EditBiasValHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX = 0;
            posY += h + hgap;
            w = get_rect_width(rect) / 4;

            MoveWindow(
                StaticPcfRadiusHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = std::min((int)get_rect_width(rect) / 4 * 3 / 3 / 4, h);

            MoveWindow(
                StaticPcfRadiusValHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = (int)get_rect_width(rect) / 4 * 3 / 3 - w;

            MoveWindow(
                EditPcfRadiusValHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX = 0;
            posY += h + hgap;
            w = get_rect_width(rect) / 4;

            MoveWindow(
                StaticExpKHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = std::min((int)get_rect_width(rect) / 4 * 3 / 3 / 4, h);

            MoveWindow(
                StaticExpKValHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = (int)get_rect_width(rect) / 4 * 3 / 3 - w;

            MoveWindow(
                EditExpKValHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX = 0;
            posY += h + hgap;
            w = get_rect_width(rect) / 4;

            MoveWindow(
                StaticRenderHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = get_rect_width(rect) * 3 / 8;

            MoveWindow(
                TabRenderDebugHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;

            MoveWindow(
                TabRenderReleaseHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX = 0;
            posY += h + hgap;
            w = get_rect_width(rect);
            h = get_rect_height(rect) - posY;

            MoveWindow(
                app::GeneralShadowOptionsWnd.getHwnd(),
                posX, posY, w, h,
                TRUE
            );

            ReleaseDC(hWnd, hDc);
            return EXIT_SUCCESS;
        }

        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}