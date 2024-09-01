#include "general_shadow_options_wnd_proc.h"

#define IDB_COMBOBOX_PROJECTION 1

#define IDB_EDIT_PROJ_ORTHO_LEFT   2
#define IDB_EDIT_PROJ_ORTHO_RIGHT  3
#define IDB_EDIT_PROJ_ORTHO_BOTTOM 4
#define IDB_EDIT_PROJ_ORTHO_TOP    5
#define IDB_EDIT_PROJ_NEAR   6
#define IDB_EDIT_PROJ_FAR    7

#define IDB_EDIT_FOV 8

LRESULT CALLBACK GeneralShadowOptionsWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static RECT rect;

    static HWND StaticProjectionHwnd = NULL;
    static HWND ComboBoxProjectionHwnd = NULL;

    // Орготональная проекция

    // Границы: левая и правая =======================
    static HWND StaticSideLeftRightHwnd = NULL;
    static HWND StaticSideLeftHwnd = NULL;
    static HWND EditSideLeftHwnd = NULL;
    static HWND StaticSideRightHwnd = NULL;
    static HWND EditSideRightHwnd = NULL;
    // Границы: нижняя и верхняя =====================
    static HWND StaticSideBottomTopHwnd = NULL;
    static HWND StaticSideBottomHwnd = NULL;
    static HWND EditSideBottomHwnd = NULL;
    static HWND StaticSideTopHwnd = NULL;
    static HWND EditSideTopHwnd = NULL;

    // Ортогональная и Перспективная проекции
    
    // Границы: ближняя и дальняя ====================
    static HWND StaticSideNearFarHwnd = NULL;
    static HWND StaticSideNearHwnd = NULL;
    static HWND EditSideNearHwnd = NULL;
    static HWND StaticSideFarHwnd = NULL;
    static HWND EditSideFarHwnd = NULL;

    // Перспективная проекция

    // Угол обзора ===================================
    static HWND StaticFovHwnd = NULL;
    static HWND StaticFovValHwnd = NULL;
    static HWND EditFovValHwnd = NULL;

    switch(uMsg)
    {
        case WM_CREATE:
        {
            StaticProjectionHwnd = CreateWindow(
                L"STATIC", L"Проецирование:", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            ComboBoxProjectionHwnd = CreateWindow(
                L"COMBOBOX", L"",
                WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_HASSTRINGS,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_COMBOBOX_PROJECTION, app::hInst, nullptr
            );

            // Орготональная проекция

            // Границы: левая и правая =======================
            StaticSideLeftRightHwnd = CreateWindow(
                L"STATIC", L"Границы Л.П.:", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            StaticSideLeftHwnd = CreateWindow(
                L"STATIC", L"L", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            EditSideLeftHwnd = CreateWindow(
                L"EDIT", L"-10",
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_EDIT_PROJ_ORTHO_LEFT, app::hInst, nullptr
            );

            StaticSideRightHwnd = CreateWindow(
                L"STATIC", L"R", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            EditSideRightHwnd = CreateWindow(
                L"EDIT", L"10",
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_EDIT_PROJ_ORTHO_RIGHT, app::hInst, nullptr
            );

            // Границы: нижняя и верхняя =====================
            StaticSideBottomTopHwnd = CreateWindow(
                L"STATIC", L"Границы Н.В.:", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            StaticSideBottomHwnd = CreateWindow(
                L"STATIC", L"B", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            EditSideBottomHwnd = CreateWindow(
                L"EDIT", L"-10",
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_EDIT_PROJ_ORTHO_BOTTOM, app::hInst, nullptr
            );

            StaticSideTopHwnd = CreateWindow(
                L"STATIC", L"T", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            EditSideTopHwnd = CreateWindow(
                L"EDIT", L"10",
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_EDIT_PROJ_ORTHO_TOP, app::hInst, nullptr
            );

            // Ортогональная и Перспективная проекции

            // Границы: ближняя и дальняя ====================
            StaticSideNearFarHwnd = CreateWindow(
                L"STATIC", L"Границы Б.Д.:", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            StaticSideNearHwnd = CreateWindow(
                L"STATIC", L"N", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            EditSideNearHwnd = CreateWindow(
                L"EDIT", L"-10",
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_EDIT_PROJ_NEAR, app::hInst, nullptr
            );

            StaticSideFarHwnd = CreateWindow(
                L"STATIC", L"F", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            EditSideFarHwnd = CreateWindow(
                L"EDIT", L"10",
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_EDIT_PROJ_FAR, app::hInst, nullptr
            );

            // Перспективная проекция

            // Угол обзора ===================================
            StaticFovHwnd = CreateWindow(
                L"STATIC", L"Угол обзора:", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            StaticFovValHwnd = CreateWindow(
                L"STATIC", L"F\u00B0", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            EditFovValHwnd = CreateWindow(
                L"EDIT", L"60",
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_EDIT_FOV, app::hInst, nullptr
            );

            SendMessage(ComboBoxProjectionHwnd, CB_ADDSTRING, (WPARAM)0, (LPARAM)L"Ортогональное");
            SendMessage(ComboBoxProjectionHwnd, CB_ADDSTRING, (WPARAM)0, (LPARAM)L"Перспективное");
            SendMessage(ComboBoxProjectionHwnd, CB_SETCURSEL, (WPARAM)0, 0);

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
            int h = std::min(30, std::max(((int)get_rect_height(rect) - 3 * hgap - 5) / 4, 20));

            MoveWindow(
                StaticProjectionHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = get_rect_width(rect) - w;

            MoveWindow(
                ComboBoxProjectionHwnd,
                posX, posY, w, h + 200,
                FALSE);

            posX = 0;
            posY += h + hgap + 5;

            if (SendMessage(ComboBoxProjectionHwnd, CB_GETCURSEL, 0, 0) == 0)
            {
                w = get_rect_width(rect) / 4;

                MoveWindow(
                    StaticSideLeftRightHwnd,
                    posX, posY, w, h,
                    TRUE
                );

                posX += w;
                w = std::min((int)get_rect_width(rect) / 4 * 3 / 3 / 4, h);

                MoveWindow(
                    StaticSideLeftHwnd,
                    posX, posY, w, h,
                    TRUE
                );

                posX += w;
                w = (int)get_rect_width(rect) / 4 * 3 / 3 - w;

                MoveWindow(
                    EditSideLeftHwnd,
                    posX, posY, w, h,
                    TRUE
                );

                posX += w;
                w = std::min((int)get_rect_width(rect) / 4 * 3 / 3 / 4, h);

                MoveWindow(
                    StaticSideRightHwnd,
                    posX, posY, w, h,
                    TRUE
                );

                posX += w;
                w = (int)get_rect_width(rect) / 4 * 3 / 3 - w;

                MoveWindow(
                    EditSideRightHwnd,
                    posX, posY, w, h,
                    TRUE
                );

                posX = 0;
                posY += h + hgap;
                w = get_rect_width(rect) / 4;

                MoveWindow(
                    StaticSideBottomTopHwnd,
                    posX, posY, w, h,
                    TRUE
                );

                posX += w;
                w = std::min((int)get_rect_width(rect) / 4 * 3 / 3 / 4, h);

                MoveWindow(
                    StaticSideBottomHwnd,
                    posX, posY, w, h,
                    TRUE
                );

                posX += w;
                w = (int)get_rect_width(rect) / 4 * 3 / 3 - w;

                MoveWindow(
                    EditSideBottomHwnd,
                    posX, posY, w, h,
                    TRUE
                );

                posX += w;
                w = std::min((int)get_rect_width(rect) / 4 * 3 / 3 / 4, h);

                MoveWindow(
                    StaticSideTopHwnd,
                    posX, posY, w, h,
                    TRUE
                );

                posX += w;
                w = (int)get_rect_width(rect) / 4 * 3 / 3 - w;

                MoveWindow(
                    EditSideTopHwnd,
                    posX, posY, w, h,
                    TRUE
                );
            }
            else
            {
                w = get_rect_width(rect) / 4;

                MoveWindow(
                    StaticFovHwnd,
                    posX, posY, w, h,
                    TRUE
                );

                posX += w;
                w = std::min((int)get_rect_width(rect) / 4 * 3 / 3 / 4, h);

                MoveWindow(
                    StaticFovValHwnd,
                    posX, posY, w, h,
                    TRUE
                );

                posX += w;
                w = (int)get_rect_width(rect) / 4 * 3 / 3 - w;

                MoveWindow(
                    EditFovValHwnd,
                    posX, posY, w, h,
                    TRUE
                );
            }
            
            posX = 0;
            posY += h + hgap;
            w = get_rect_width(rect) / 4;

            MoveWindow(
                StaticSideNearFarHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = std::min((int)get_rect_width(rect) / 4 * 3 / 3 / 4, h);

            MoveWindow(
                StaticSideNearHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = (int)get_rect_width(rect) / 4 * 3 / 3 - w;

            MoveWindow(
                EditSideNearHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = std::min((int)get_rect_width(rect) / 4 * 3 / 3 / 4, h);

            MoveWindow(
                StaticSideFarHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = (int)get_rect_width(rect) / 4 * 3 / 3 - w;

            MoveWindow(
                EditSideFarHwnd,
                posX, posY, w, h,
                TRUE
            );

            return EXIT_SUCCESS;
        }

        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
                case IDB_COMBOBOX_PROJECTION:
                {
                    switch (HIWORD(wParam))
                    {
                        case CBN_SELCHANGE:
                        {
                            SetFocus(hWnd);

                            // Ortho
                            if (SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0) == 0)
                            {
                                set_wnd_showmode(
                                    SW_HIDE, 3,
                                    StaticFovHwnd,
                                    StaticFovValHwnd,
                                    EditFovValHwnd
                                );

                                set_wnd_showmode(
                                    SW_SHOW, 10,
                                    // Границы: левая и правая =======================
                                    StaticSideLeftRightHwnd,
                                    StaticSideLeftHwnd,
                                    EditSideLeftHwnd,
                                    StaticSideRightHwnd,
                                    EditSideRightHwnd,
                                    // Границы: нижняя и верхняя =====================
                                    StaticSideBottomTopHwnd,
                                    StaticSideBottomHwnd,
                                    EditSideBottomHwnd,
                                    StaticSideTopHwnd,
                                    EditSideTopHwnd
                                );
                            }
                            // Perspective
                            else
                            {
                                set_wnd_showmode(
                                    SW_SHOW, 3,
                                    StaticFovHwnd,
                                    StaticFovValHwnd,
                                    EditFovValHwnd
                                );

                                set_wnd_showmode(
                                    SW_HIDE, 10,
                                    // Границы: левая и правая =======================
                                    StaticSideLeftRightHwnd,
                                    StaticSideLeftHwnd,
                                    EditSideLeftHwnd,
                                    StaticSideRightHwnd,
                                    EditSideRightHwnd,
                                    // Границы: нижняя и верхняя =====================
                                    StaticSideBottomTopHwnd,
                                    StaticSideBottomHwnd,
                                    EditSideBottomHwnd,
                                    StaticSideTopHwnd,
                                    EditSideTopHwnd
                                );
                            }

                            SendMessage(hWnd, WM_SIZE, 0, 0);
                            
                            return EXIT_SUCCESS;
                        }

                        case CBN_CLOSEUP:
                        {
                            SetFocus(hWnd);
                            return EXIT_SUCCESS;
                        }

                        default:
                            return EXIT_SUCCESS;
                    }
                }

                default:
                {
                    return EXIT_SUCCESS;
                }
            }
        }

        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}