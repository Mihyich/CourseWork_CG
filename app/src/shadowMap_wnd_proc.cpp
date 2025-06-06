#include "shadowMap_wnd_proc.h"

#define IDB_COMBOBOX_ALGORITM 1
#define ALG_SM 0
#define ALG_SM_PCF 1
#define ALG_SM_NOISE 2
#define ALG_SM_PCSS 3
#define ALG_SM_PCSS_NOISE 4
#define ALG_SM_ESM 5
#define ALG_SM_VSM 6

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

    static WCHAR tmpText[MAX_PATH];
    static float tmpFloat = 0.f;

    static HWND StaticAlgoritmHwnd = NULL;
    static HWND ComboBoxAlgoritmHwnd = NULL;

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

            ComboBoxAlgoritmHwnd = CreateWindow(
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
                L"EDIT", L"0.0005",
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
                hWnd, (HMENU)IDB_EDIT_PCF_RADIUS, app::hInst, nullptr
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
                800, 600,
                CS_HREDRAW | CS_VREDRAW,
                WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPCHILDREN,
                WS_EX_COMPOSITED,
                hWnd
            );

            SendMessage(ComboBoxAlgoritmHwnd, CB_ADDSTRING, (WPARAM)0, (LPARAM)L"ShadowMap");
            SendMessage(ComboBoxAlgoritmHwnd, CB_ADDSTRING, (WPARAM)0, (LPARAM)L"ShadowMap PCF");
            SendMessage(ComboBoxAlgoritmHwnd, CB_ADDSTRING, (WPARAM)0, (LPARAM)L"ShadowMap NOISE");
            SendMessage(ComboBoxAlgoritmHwnd, CB_ADDSTRING, (WPARAM)0, (LPARAM)L"ShadowMap PCSS");
            SendMessage(ComboBoxAlgoritmHwnd, CB_ADDSTRING, (WPARAM)0, (LPARAM)L"ShadowMap PCSS_NOISE");
            SendMessage(ComboBoxAlgoritmHwnd, CB_ADDSTRING, (WPARAM)0, (LPARAM)L"ShadowMap ESM");
            SendMessage(ComboBoxAlgoritmHwnd, CB_ADDSTRING, (WPARAM)0, (LPARAM)L"ShadowMap VSM");
            SendMessage(ComboBoxAlgoritmHwnd, CB_SETCURSEL, (WPARAM)ALG_SM_PCF, 0);
            SendMessage(hWnd, WM_COMMAND, MAKEWPARAM(CBN_SELCHANGE, ALG_SM_PCF), (LPARAM)ComboBoxAlgoritmHwnd);

            // По умолчанию режим - Release
            SendMessage(hWnd, WM_COMMAND, MAKEWPARAM(IDB_TAB_RENDER_RELEASE, 0), 0);

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
                ComboBoxAlgoritmHwnd,
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

        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
                case IDB_COMBOBOX_ALGORITM:
                {
                    switch (HIWORD(wParam))
                    {
                        case CBN_SELCHANGE:
                        {
                            SetFocus(hWnd);

                            const int alg = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
                            const WINBOOL bias = (alg == ALG_SM) || (alg == ALG_SM_PCF) || (alg == ALG_SM_NOISE) || (alg == ALG_SM_PCSS) || (alg == ALG_SM_PCSS_NOISE) || (alg == ALG_SM_ESM);
                            const WINBOOL pcf = (alg == ALG_SM_PCF) || (alg == ALG_SM_NOISE) || (alg == ALG_SM_PCSS) || (alg == ALG_SM_PCSS_NOISE);
                            const WINBOOL expK = (alg == ALG_SM_ESM);

                            EnableWindow(StaticBiasHwnd, bias);
                            EnableWindow(StaticBiasValHwnd, bias);
                            EnableWindow(EditBiasValHwnd, bias);

                            EnableWindow(StaticPcfRadiusHwnd, pcf);
                            EnableWindow(StaticPcfRadiusValHwnd, pcf);
                            EnableWindow(EditPcfRadiusValHwnd, pcf);
                            
                            EnableWindow(StaticExpKHwnd, expK);
                            EnableWindow(StaticExpKValHwnd, expK);
                            EnableWindow(EditExpKValHwnd, expK);

                            switch (alg)
                            {
                                case ALG_SM:
                                {
                                    ProjecitonType type = *reinterpret_cast<ProjecitonType*>(SendMessage(app::GeneralShadowOptionsWnd.getHwnd(), WM_GET_PROJ_TYPE, 0, 0));
                                    WINBOOL RenderDebug = SendMessage(TabRenderDebugHwnd, BM_GETCHECK, 0, 0) == BST_CHECKED;

                                    if (type == PROJ_ORTHO)
                                    {
                                        if (RenderDebug)
                                        {
                                            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOW_ALG, SHADOW_MAP_ORTHOGONAL_DEBUG, 0);
                                        }
                                        else
                                        {
                                            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOW_ALG, SHADOW_MAP_ORTHOGONAL, 0);
                                        }
                                    }
                                    else
                                    {
                                        if (RenderDebug)
                                        {
                                            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOW_ALG, SHADOW_MAP_PERSPECTIVE_DEBUG, 0);
                                        }
                                        else
                                        {
                                            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOW_ALG, SHADOW_MAP_PERSPECTIVE, 0);
                                        }
                                    }

                                    break;
                                }

                                case ALG_SM_PCF:
                                {
                                    ProjecitonType type = *reinterpret_cast<ProjecitonType*>(SendMessage(app::GeneralShadowOptionsWnd.getHwnd(), WM_GET_PROJ_TYPE, 0, 0));
                                    WINBOOL RenderDebug = SendMessage(TabRenderDebugHwnd, BM_GETCHECK, 0, 0) == BST_CHECKED;

                                    if (type == PROJ_ORTHO)
                                    {
                                        if (RenderDebug)
                                        {
                                            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOW_ALG, SHADOW_MAP_ORTHOGONAL_PCF_DEBUG, 0);
                                        }
                                        else
                                        {
                                            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOW_ALG, SHADOW_MAP_ORTHOGONAL_PCF, 0);
                                        }
                                    }
                                    else
                                    {
                                        if (RenderDebug)
                                        {
                                            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOW_ALG, SHADOW_MAP_PERSPECTIVE_PCF_DEBUG, 0);
                                        }
                                        else
                                        {
                                            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOW_ALG, SHADOW_MAP_PERSPECTIVE_PCF, 0);
                                        }
                                    }

                                    break;
                                }

                                case ALG_SM_NOISE:
                                {
                                    ProjecitonType type = *reinterpret_cast<ProjecitonType*>(SendMessage(app::GeneralShadowOptionsWnd.getHwnd(), WM_GET_PROJ_TYPE, 0, 0));
                                    WINBOOL RenderDebug = SendMessage(TabRenderDebugHwnd, BM_GETCHECK, 0, 0) == BST_CHECKED;

                                    if (type == PROJ_ORTHO)
                                    {
                                        if (RenderDebug)
                                        {
                                            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOW_ALG, SHADOW_MAP_ORTHOGONAL_NOISE_DEBUG, 0);
                                        }
                                        else
                                        {
                                            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOW_ALG, SHADOW_MAP_ORTHOGONAL_NOISE, 0);
                                        }
                                    }
                                    else
                                    {
                                        if (RenderDebug)
                                        {
                                            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOW_ALG, SHADOW_MAP_PERSPECTIVE_NOISE_DEBUG, 0);
                                        }
                                        else
                                        {
                                            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOW_ALG, SHADOW_MAP_PERSPECTIVE_NOISE, 0);
                                        }
                                    }

                                    break;
                                }

                                case ALG_SM_PCSS:
                                {
                                    ProjecitonType type = *reinterpret_cast<ProjecitonType*>(SendMessage(app::GeneralShadowOptionsWnd.getHwnd(), WM_GET_PROJ_TYPE, 0, 0));
                                    WINBOOL RenderDebug = SendMessage(TabRenderDebugHwnd, BM_GETCHECK, 0, 0) == BST_CHECKED;

                                    if (type == PROJ_ORTHO)
                                    {
                                        if (RenderDebug)
                                        {
                                            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOW_ALG, SHADOW_MAP_ORTHOGONAL_PCSS_DEBUG, 0);
                                        }
                                        else
                                        {
                                            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOW_ALG, SHADOW_MAP_ORTHOGONAL_PCSS, 0);
                                        }
                                    }
                                    else
                                    {
                                        if (RenderDebug)
                                        {
                                            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOW_ALG, SHADOW_MAP_PERSPECTIVE_PCSS_DEBUG, 0);
                                        }
                                        else
                                        {
                                            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOW_ALG, SHADOW_MAP_PERSPECTIVE_PCSS, 0);
                                        }
                                    }

                                    break;
                                }

                                case ALG_SM_PCSS_NOISE:
                                {
                                    ProjecitonType type = *reinterpret_cast<ProjecitonType*>(SendMessage(app::GeneralShadowOptionsWnd.getHwnd(), WM_GET_PROJ_TYPE, 0, 0));
                                    WINBOOL RenderDebug = SendMessage(TabRenderDebugHwnd, BM_GETCHECK, 0, 0) == BST_CHECKED;

                                    if (type == PROJ_ORTHO)
                                    {
                                        if (RenderDebug)
                                        {
                                            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOW_ALG, SHADOW_MAP_ORTHOGONAL_PCSS_NOISE_DEBUG, 0);
                                        }
                                        else
                                        {
                                            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOW_ALG, SHADOW_MAP_ORTHOGONAL_PCSS_NOISE, 0);
                                        }
                                    }
                                    else
                                    {
                                        if (RenderDebug)
                                        {
                                            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOW_ALG, SHADOW_MAP_PERSPECTIVE_PCSS_NOISE_DEBUG, 0);
                                        }
                                        else
                                        {
                                            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOW_ALG, SHADOW_MAP_PERSPECTIVE_PCSS_NOISE, 0);
                                        }
                                    }

                                    break;
                                }

                                case ALG_SM_ESM:
                                {
                                    ProjecitonType type = *reinterpret_cast<ProjecitonType*>(SendMessage(app::GeneralShadowOptionsWnd.getHwnd(), WM_GET_PROJ_TYPE, 0, 0));
                                    WINBOOL RenderDebug = SendMessage(TabRenderDebugHwnd, BM_GETCHECK, 0, 0) == BST_CHECKED;

                                    if (type == PROJ_ORTHO)
                                    {
                                        if (RenderDebug)
                                        {
                                            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOW_ALG, SHADOW_MAP_ORTHOGONAL_ESM_DEBUG, 0);
                                        }
                                        else
                                        {
                                            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOW_ALG, SHADOW_MAP_ORTHOGONAL_ESM, 0);
                                        }
                                    }
                                    else
                                    {
                                        if (RenderDebug)
                                        {
                                            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOW_ALG, SHADOW_MAP_PERSPECTIVE_ESM_DEBUG, 0);
                                        }
                                        else
                                        {
                                            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOW_ALG, SHADOW_MAP_PERSPECTIVE_ESM, 0);
                                        }
                                    }

                                    break;
                                }

                                case ALG_SM_VSM:
                                {
                                    ProjecitonType type = *reinterpret_cast<ProjecitonType*>(SendMessage(app::GeneralShadowOptionsWnd.getHwnd(), WM_GET_PROJ_TYPE, 0, 0));
                                    WINBOOL RenderDebug = SendMessage(TabRenderDebugHwnd, BM_GETCHECK, 0, 0) == BST_CHECKED;

                                    if (type == PROJ_ORTHO)
                                    {
                                        if (RenderDebug)
                                        {
                                            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOW_ALG, SHADOW_MAP_ORTHOGONAL_VSM_DEBUG, 0);
                                        }
                                        else
                                        {
                                            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOW_ALG, SHADOW_MAP_ORTHOGONAL_VSM, 0);
                                        }
                                    }
                                    else
                                    {
                                        if (RenderDebug)
                                        {
                                            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOW_ALG, SHADOW_MAP_PERSPECTIVE_VSM_DEBUG, 0);
                                        }
                                        else
                                        {
                                            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOW_ALG, SHADOW_MAP_PERSPECTIVE_VSM, 0);
                                        }
                                    }

                                    break;
                                }
                                
                                default:
                                    break;
                            }

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

                case IDB_BUTTON_RES:
                {
                    SetFocus(hWnd);
                    if (EditResolutionXHwnd && EditResolutionYHwnd)
                    {
                        long resX;
                        long resY;

                        GetWindowText(EditResolutionXHwnd, tmpText, MAX_PATH);
                        if (convert_str_to_long(tmpText, &resX))
                        {
                            GetWindowText(EditResolutionYHwnd, tmpText, MAX_PATH);
                            if (convert_str_to_long(tmpText, &resY))
                            {
                                SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOWMAP_RESOLUTION, (WPARAM)&resX, (LPARAM)&resY);
                            }
                        }
                    }
                    return EXIT_SUCCESS;
                }

                case IDB_EDIT_BIAS:
                {
                    switch (HIWORD(wParam))
                    {
                    case EN_CHANGE:
                        if (EditBiasValHwnd)
                        {
                            GetWindowText(EditBiasValHwnd, tmpText, MAX_PATH);
                            if (convert_str_to_float(tmpText, &tmpFloat))
                            {
                                SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOWMAP_BIAS, (WPARAM)&tmpFloat, 0);
                            }
                        }
                        return EXIT_SUCCESS;
                    
                    default:
                        return EXIT_SUCCESS;
                    }
                }   

                case IDB_EDIT_PCF_RADIUS:
                {
                    switch (HIWORD(wParam))
                    {
                    case EN_CHANGE:
                        if (EditPcfRadiusValHwnd)
                        {
                            GetWindowText(EditPcfRadiusValHwnd, tmpText, MAX_PATH);
                            if (convert_str_to_float(tmpText, &tmpFloat))
                            {
                                SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOWMAP_PCF_RADIUS, (WPARAM)&tmpFloat, 0);
                            }
                        }
                        return EXIT_SUCCESS;
                    
                    default:
                        return EXIT_SUCCESS;
                    }
                }

                case IDB_EDIT_EXP_K:
                {
                    switch (HIWORD(wParam))
                    {
                    case EN_CHANGE:
                        if (EditExpKValHwnd)
                        {
                            GetWindowText(EditExpKValHwnd, tmpText, MAX_PATH);
                            if (convert_str_to_float(tmpText, &tmpFloat))
                            {
                                SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOWMAP_EXP_K, (WPARAM)&tmpFloat, 0);
                            }
                        }
                        return EXIT_SUCCESS;
                    
                    default:
                        return EXIT_SUCCESS;
                    }
                }

                case IDB_TAB_RENDER_DEBUG:
                {
                    SetFocus(hWnd);
                    SendMessage(TabRenderDebugHwnd, BM_SETCHECK, BST_CHECKED, 0);
                    SendMessage(TabRenderReleaseHwnd, BM_SETCHECK, BST_UNCHECKED, 0);
                    SendMessage(hWnd, WM_COMMAND, MAKEWPARAM(IDB_COMBOBOX_ALGORITM, CBN_SELCHANGE), (LPARAM)ComboBoxAlgoritmHwnd);
                    return EXIT_SUCCESS;
                }

                case IDB_TAB_RENDER_RELEASE:
                {
                    SetFocus(hWnd);
                    SendMessage(TabRenderDebugHwnd, BM_SETCHECK, BST_UNCHECKED, 0);
                    SendMessage(TabRenderReleaseHwnd, BM_SETCHECK, BST_CHECKED, 0);
                    SendMessage(hWnd, WM_COMMAND, MAKEWPARAM(IDB_COMBOBOX_ALGORITM, CBN_SELCHANGE), (LPARAM)ComboBoxAlgoritmHwnd);
                    return EXIT_SUCCESS;
                }

                default:
                {
                    return EXIT_SUCCESS;
                }
            }
        }

        case WM_UPDATE_PROJ_TYPE:
        {
            SendMessage(hWnd, WM_COMMAND, MAKEWPARAM(IDB_COMBOBOX_ALGORITM, CBN_SELCHANGE), (LPARAM)ComboBoxAlgoritmHwnd);
            return EXIT_SUCCESS;
        }

        case WM_UPDATE_SIDE_LEFT:
        {
            tmpFloat = *reinterpret_cast<float*>(SendMessage(app::GeneralShadowOptionsWnd.getHwnd(), WM_GET_SIDE_LEFT, 0, 0));
            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOWMAP_SIDE_LEFT, (WPARAM)&tmpFloat, 0);
            return EXIT_SUCCESS;
        }

        case WM_UPDATE_SIDE_RIGHT:
        {
            tmpFloat = *reinterpret_cast<float*>(SendMessage(app::GeneralShadowOptionsWnd.getHwnd(), WM_GET_SIDE_RIGHT, 0, 0));
            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOWMAP_SIDE_RIGHT, (WPARAM)&tmpFloat, 0);
            return EXIT_SUCCESS;
        }

        case WM_UPDATE_SIDE_BOTTOM:
        {
            tmpFloat = *reinterpret_cast<float*>(SendMessage(app::GeneralShadowOptionsWnd.getHwnd(), WM_GET_SIDE_BOTTOM, 0, 0));
            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOWMAP_SIDE_BOTTOM, (WPARAM)&tmpFloat, 0);
            return EXIT_SUCCESS;
        }

        case WM_UPDATE_SIDE_TOP:
        {
            tmpFloat = *reinterpret_cast<float*>(SendMessage(app::GeneralShadowOptionsWnd.getHwnd(), WM_GET_SIDE_TOP, 0, 0));
            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOWMAP_SIDE_TOP, (WPARAM)&tmpFloat, 0);
            return EXIT_SUCCESS;
        }

        case WM_UPDATE_SIDE_NEAR:
        {
            tmpFloat = *reinterpret_cast<float*>(SendMessage(app::GeneralShadowOptionsWnd.getHwnd(), WM_GET_SIDE_NEAR, 0, 0));
            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOWMAP_SIDE_NEAR, (WPARAM)&tmpFloat, 0);
            return EXIT_SUCCESS;
        }

        case WM_UPDATE_SIDE_FAR:
        {
            tmpFloat = *reinterpret_cast<float*>(SendMessage(app::GeneralShadowOptionsWnd.getHwnd(), WM_GET_SIDE_FAR, 0, 0));
            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOWMAP_SIDE_FAR, (WPARAM)&tmpFloat, 0);
            return EXIT_SUCCESS;
        }

        case WM_UPDATE_FOV:
        {
            tmpFloat = *reinterpret_cast<float*>(SendMessage(app::GeneralShadowOptionsWnd.getHwnd(), WM_GET_FOV, 0, 0));
            SendMessage(app::RenderWnd.getHwnd(), WM_SET_SHADOWMAP_FOV, (WPARAM)&tmpFloat, 0);
            return EXIT_SUCCESS;
        }

        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}