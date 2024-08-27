#include "lighting_wnd_proc.h"

#define IDB_COMBOBOX_LIGHT 1

#define IDB_EDIT_POS_X 2
#define IDB_EDIT_POS_Y 3
#define IDB_EDIT_POS_Z 4

#define IDB_EDIT_DIR_X 5
#define IDB_EDIT_DIR_Y 6
#define IDB_EDIT_DIR_Z 7

#define IDB_BTN_CHOOSE_COLOR 8

#define IDB_EDIT_RADIUS 9
#define IDB_EDIT_INTENSITY 10
#define IDB_EDIT_INNER_CUTOFF 11
#define IDB_EDIT_OUTER_CUTOFF 12

LRESULT CALLBACK LightingWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static RECT rect;
    static WINBOOL firstSize = true;

    static FontParam fp;
    static HFONT LeftStaticOptionHfont = NULL;
    static HFONT VectorHfont = NULL;
    static HFONT HeaderHfont = NULL;

    static HWND StaticLightTypeHwnd = NULL;
    static HWND ComboBoxLightHwnd = NULL;

    static HWND StaticPositionHwnd = NULL;
    static HWND StaticPosXHwnd = NULL;
    static HWND EditPosXHwnd = NULL;
    static HWND StaticPosYHwnd = NULL;
    static HWND EditPosYHwnd = NULL;
    static HWND StaticPosZHwnd = NULL;
    static HWND EditPosZHwnd = NULL;

    static HWND StaticDirectionHwnd = NULL;
    static HWND StaticDirXHwnd = NULL;
    static HWND EditDirXHwnd = NULL;
    static HWND StaticDirYHwnd = NULL;
    static HWND EditDirYHwnd = NULL;
    static HWND StaticDirZHwnd = NULL;
    static HWND EditDirZHwnd = NULL;

    static HWND StaticColorHwnd = NULL;
    static HWND BtnChooseColorHwnd = NULL;

    static HWND StaticRadiusHwnd = NULL;
    static HWND StaticRadiusValHwnd = NULL;
    static HWND EditRadiusValHwnd = NULL;

    static HWND StaticIntensityHwnd = NULL;
    static HWND StaticIntensityValHwnd = NULL;
    static HWND EditIntensityValHwnd = NULL;

    static HWND StaticCutoffHwnd = NULL;

    static HWND StaticInnerCutoffHwnd = NULL;
    static HWND StaticInnerCutoffValHwnd = NULL;
    static HWND EditInnerCutoffValHwnd = NULL;

    static HWND StaticOuterCutoffHwnd = NULL;
    static HWND StaticOuterCutoffValHwnd = NULL;
    static HWND EditOuterCutoffValHwnd = NULL;

    static WCHAR tmpText[MAX_PATH];

    static LightType lightType = LIGHT_POINT;
    static vec3 msgVec;
    static float msgFloat;

    static RECT lightColorRect = {0, 0, 0, 0};
    static COLORREF lightColor = RGB(255, 255, 255);

    switch(uMsg)
    {
        case WM_CREATE:
        {
            StaticLightTypeHwnd = CreateWindow(
                L"STATIC", L"Источник:", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            ComboBoxLightHwnd = CreateWindow(
                L"COMBOBOX", L"",
                WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_HASSTRINGS,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_COMBOBOX_LIGHT, app::hInst, nullptr
            );

            StaticPositionHwnd = CreateWindow(
                L"STATIC", L"Позиция:", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            StaticPosXHwnd = CreateWindow(
                L"STATIC", L"X", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            EditPosXHwnd = CreateWindow(
                L"EDIT", L"0",
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_CENTER | WS_BORDER,
                0, 0, 100, 30,
                hWnd, (HMENU)IDB_EDIT_POS_X, app::hInst, nullptr
            );

            StaticPosYHwnd = CreateWindow(
                L"STATIC", L"Y", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            EditPosYHwnd = CreateWindow(
                L"EDIT", L"0",
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_EDIT_POS_Y, app::hInst, nullptr
            );

            StaticPosZHwnd = CreateWindow(
                L"STATIC", L"Z", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            EditPosZHwnd = CreateWindow(
                L"EDIT", L"0",
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_EDIT_POS_Z, app::hInst, nullptr
            );

            StaticDirectionHwnd = CreateWindow(
                L"STATIC", L"Направление:", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            StaticDirXHwnd = CreateWindow(
                L"STATIC", L"X", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            EditDirXHwnd = CreateWindow(
                L"EDIT", L"0",
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_CENTER | WS_BORDER,
                0, 0, 100, 30,
                hWnd, (HMENU)IDB_EDIT_DIR_X, app::hInst, nullptr
            );

            StaticDirYHwnd = CreateWindow(
                L"STATIC", L"Y", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            EditDirYHwnd = CreateWindow(
                L"EDIT", L"0",
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_EDIT_DIR_Y, app::hInst, nullptr
            );

            StaticDirZHwnd = CreateWindow(
                L"STATIC", L"Z", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            EditDirZHwnd = CreateWindow(
                L"EDIT", L"0",
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_EDIT_DIR_Z, app::hInst, nullptr
            );

            StaticColorHwnd = CreateWindow(
                L"STATIC", L"Цвет:", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            BtnChooseColorHwnd = CreateWindow(
                L"BUTTON", L"Выбрать",
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHLIKE | BS_CENTER | BS_VCENTER,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_BTN_CHOOSE_COLOR, app::hInst, nullptr
            );

            StaticRadiusHwnd = CreateWindow(
                L"STATIC", L"Радиус:", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            StaticRadiusValHwnd = CreateWindow(
                L"STATIC", L"R", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            EditRadiusValHwnd = CreateWindow(
                L"EDIT", L"0",
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_EDIT_RADIUS, app::hInst, nullptr
            );

            StaticIntensityHwnd = CreateWindow(
                L"STATIC", L"Интенсивность:", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            StaticIntensityValHwnd = CreateWindow(
                L"STATIC", L"I", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            EditIntensityValHwnd = CreateWindow(
                L"EDIT", L"0",
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_EDIT_INTENSITY, app::hInst, nullptr
            );

            StaticCutoffHwnd = CreateWindow(
                L"STATIC", L"Угол раствора в градусах", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | ES_CENTER,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            StaticInnerCutoffHwnd = CreateWindow(
                L"STATIC", L"Внутренний:", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | ES_CENTER,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            StaticInnerCutoffValHwnd = CreateWindow(
                L"STATIC", L"I", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            EditInnerCutoffValHwnd = CreateWindow(
                L"EDIT", L"0",
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_EDIT_INNER_CUTOFF, app::hInst, nullptr
            );

            StaticOuterCutoffHwnd = CreateWindow(
                L"STATIC", L"Внешний:", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | ES_CENTER,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            StaticOuterCutoffValHwnd = CreateWindow(
                L"STATIC", L"O", 
                WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)NULL, app::hInst, NULL
            );

            EditOuterCutoffValHwnd = CreateWindow(
                L"EDIT", L"0",
                WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_CENTER | WS_BORDER,
                0, 0, 0, 0,
                hWnd, (HMENU)IDB_EDIT_OUTER_CUTOFF, app::hInst, nullptr
            );

            SendMessage(ComboBoxLightHwnd, CB_ADDSTRING, (WPARAM)0, (LPARAM)L"Точечный");
            SendMessage(ComboBoxLightHwnd, CB_ADDSTRING, (WPARAM)0, (LPARAM)L"Прожекторный");
            SendMessage(ComboBoxLightHwnd, CB_SETCURSEL, (WPARAM)0, 0);
            SendMessage(hWnd, WM_COMMAND, MAKEWPARAM(CBN_SELCHANGE, IDB_COMBOBOX_LIGHT), (LPARAM)ComboBoxLightHwnd);

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
            int h = std::min(30, ((int)get_rect_height(rect) - 7 * hgap - 5) / 9);

            MoveWindow(
                StaticLightTypeHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = get_rect_width(rect) - w;

            MoveWindow(
                ComboBoxLightHwnd,
                posX, posY, w, h + 200,
                FALSE);

            posX = 0;
            posY += h + hgap + 5;
            w = get_rect_width(rect) / 4;

            MoveWindow(
                StaticPositionHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = std::min((int)get_rect_width(rect) / 4 * 3 / 3 / 4, h);

            MoveWindow(
                StaticPosXHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = (int)get_rect_width(rect) / 4 * 3 / 3 - w;

            MoveWindow(
                EditPosXHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = std::min((int)get_rect_width(rect) / 4 * 3 / 3 / 4, h);

            MoveWindow(
                StaticPosYHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = (int)get_rect_width(rect) / 4 * 3 / 3 - w;

            MoveWindow(
                EditPosYHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = std::min((int)get_rect_width(rect) / 4 * 3 / 3 / 4, h);

            MoveWindow(
                StaticPosZHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = (int)get_rect_width(rect) / 4 * 3 / 3 - w;

            MoveWindow(
                EditPosZHwnd,
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

            posX += w;
            w = std::min((int)get_rect_width(rect) / 4 * 3 / 3 / 4, h);

            MoveWindow(
                StaticDirXHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = (int)get_rect_width(rect) / 4 * 3 / 3 - w;

            MoveWindow(
                EditDirXHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = std::min((int)get_rect_width(rect) / 4 * 3 / 3 / 4, h);

            MoveWindow(
                StaticDirYHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = (int)get_rect_width(rect) / 4 * 3 / 3 - w;

            MoveWindow(
                EditDirYHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = std::min((int)get_rect_width(rect) / 4 * 3 / 3 / 4, h);

            MoveWindow(
                StaticDirZHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = (int)get_rect_width(rect) / 4 * 3 / 3 - w;

            MoveWindow(
                EditDirZHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX = 0;
            posY += h + hgap;
            w = get_rect_width(rect) / 4;

            MoveWindow(
                StaticColorHwnd,
                posX, posY, w, h,
                TRUE
            );

            lightColorRect = {0, posY, get_rect_width(rect), posY + h};
            InvalidateRect(hWnd, NULL, TRUE);
            lightColorRect = {w, posY, w + h, posY + h};
            if (!firstSize) UpdateWindow(hWnd);

            posX += w + h + h / 4;
            w = std::min((INT)get_rect_width(rect) / 4, std::min((INT)get_rect_width(rect) - posX, h * 5));

            MoveWindow(
                BtnChooseColorHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX = 0;
            posY += h + hgap;
            w = get_rect_width(rect) / 4;

            MoveWindow(
                StaticRadiusHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = std::min((INT)get_rect_width(rect) / 4 * 3 / 3 / 4, h);

            MoveWindow(
                StaticRadiusValHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = (int)get_rect_width(rect) / 4 * 3 / 3 - w;

            MoveWindow(
                EditRadiusValHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX = 0;
            posY += h + hgap;
            w = get_rect_width(rect) / 4;

            MoveWindow(
                StaticIntensityHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = std::min((INT)get_rect_width(rect) / 4 * 3 / 3 / 4, h);

            MoveWindow(
                StaticIntensityValHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = (int)get_rect_width(rect) / 4 * 3 / 3 - w;

            MoveWindow(
                EditIntensityValHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX = 0;
            posY += h + hgap;
            w = get_rect_width(rect);

            MoveWindow(
                StaticCutoffHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX = 0;
            posY += h + hgap;
            w = get_rect_width(rect) / 2;

            MoveWindow(
                StaticInnerCutoffHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;

            MoveWindow(
                StaticOuterCutoffHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX = 0;
            posY += h + hgap;
            w = std::min((INT)get_rect_width(rect) / 4 * 3 / 3 / 4, h);

            MoveWindow(
                StaticInnerCutoffValHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = (int)get_rect_width(rect) / 4 * 3 / 3 - w;

            MoveWindow(
                EditInnerCutoffValHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX = get_rect_width(rect) / 2;
            w = std::min((INT)get_rect_width(rect) / 4 * 3 / 3 / 4, h);

            MoveWindow(
                StaticOuterCutoffValHwnd,
                posX, posY, w, h,
                TRUE
            );

            posX += w;
            w = (int)get_rect_width(rect) / 4 * 3 / 3 - w;

            MoveWindow(
                EditOuterCutoffValHwnd,
                posX, posY, w, h,
                TRUE
            );

            // Расчет высоты шрифта
            GetWindowRect(StaticLightTypeHwnd, &tmp_rect);
            // GetWindowText(StaticLightTypeHwnd, tmpText, MAX_PATH);
            tmpFp = fp;
            tmpFp.cHeight = 24;
            tmpFp.pszFaceName = L"Arial";
            tmpFp.cHeight = decrease_font_height_for_fitting(hDc, &tmpFp, L"Интенсивность:", get_rect_width(tmp_rect), h);
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
                if (LeftStaticOptionHfont) DeleteObject((HFONT)SelectObject(hDc, (HFONT)LeftStaticOptionHfont));
                LeftStaticOptionHfont = hFont;

                SendMessage(StaticLightTypeHwnd, WM_SETFONT, (WPARAM)LeftStaticOptionHfont, FALSE);
                SendMessage(StaticPositionHwnd, WM_SETFONT, (WPARAM)LeftStaticOptionHfont, FALSE);
                SendMessage(StaticDirectionHwnd, WM_SETFONT, (WPARAM)LeftStaticOptionHfont, FALSE);

                SendMessage(StaticColorHwnd, WM_SETFONT, (WPARAM)LeftStaticOptionHfont, FALSE);
                SendMessage(BtnChooseColorHwnd, WM_SETFONT, (WPARAM)LeftStaticOptionHfont, FALSE);

                SendMessage(StaticRadiusHwnd, WM_SETFONT, (WPARAM)LeftStaticOptionHfont, FALSE);
                SendMessage(StaticIntensityHwnd, WM_SETFONT, (WPARAM)LeftStaticOptionHfont, FALSE);
                SendMessage(StaticInnerCutoffHwnd, WM_SETFONT, (WPARAM)LeftStaticOptionHfont, FALSE);
                SendMessage(StaticOuterCutoffHwnd, WM_SETFONT, (WPARAM)LeftStaticOptionHfont, FALSE);
            }

            tmpFp.cHeight = 0.85 * h;
            tmpFp.pszFaceName = L"Consolas";
            hFont = WinApiFont::create_font(&tmpFp);
            if (hFont)
            {
                if (VectorHfont) DeleteObject((HFONT)SelectObject(hDc, (HFONT)VectorHfont));
                VectorHfont = hFont;

                SendMessage(ComboBoxLightHwnd, WM_SETFONT, (WPARAM)VectorHfont, FALSE);

                SendMessage(StaticPosXHwnd, WM_SETFONT, (WPARAM)VectorHfont, FALSE);
                SendMessage(StaticPosYHwnd, WM_SETFONT, (WPARAM)VectorHfont, FALSE);
                SendMessage(StaticPosZHwnd, WM_SETFONT, (WPARAM)VectorHfont, FALSE);

                SendMessage(EditPosXHwnd, WM_SETFONT, (WPARAM)VectorHfont, FALSE);
                SendMessage(EditPosYHwnd, WM_SETFONT, (WPARAM)VectorHfont, FALSE);
                SendMessage(EditPosZHwnd, WM_SETFONT, (WPARAM)VectorHfont, FALSE);

                SendMessage(StaticDirXHwnd, WM_SETFONT, (WPARAM)VectorHfont, FALSE);
                SendMessage(StaticDirYHwnd, WM_SETFONT, (WPARAM)VectorHfont, FALSE);
                SendMessage(StaticDirZHwnd, WM_SETFONT, (WPARAM)VectorHfont, FALSE);

                SendMessage(EditDirXHwnd, WM_SETFONT, (WPARAM)VectorHfont, FALSE);
                SendMessage(EditDirYHwnd, WM_SETFONT, (WPARAM)VectorHfont, FALSE);
                SendMessage(EditDirZHwnd, WM_SETFONT, (WPARAM)VectorHfont, FALSE);

                SendMessage(StaticRadiusValHwnd, WM_SETFONT, (WPARAM)VectorHfont, FALSE);
                SendMessage(EditRadiusValHwnd, WM_SETFONT, (WPARAM)VectorHfont, FALSE);

                SendMessage(StaticIntensityValHwnd, WM_SETFONT, (WPARAM)VectorHfont, FALSE);
                SendMessage(EditIntensityValHwnd, WM_SETFONT, (WPARAM)VectorHfont, FALSE);

                SendMessage(StaticInnerCutoffValHwnd, WM_SETFONT, (WPARAM)VectorHfont, FALSE);
                SendMessage(EditInnerCutoffValHwnd, WM_SETFONT, (WPARAM)VectorHfont, FALSE);

                SendMessage(StaticOuterCutoffValHwnd, WM_SETFONT, (WPARAM)VectorHfont, FALSE);
                SendMessage(EditOuterCutoffValHwnd, WM_SETFONT, (WPARAM)VectorHfont, FALSE);
            }

            GetWindowRect(StaticCutoffHwnd, &tmp_rect);
            GetWindowText(StaticCutoffHwnd, tmpText, MAX_PATH);
            tmpFp = fp;
            tmpFp.cHeight = 30;
            tmpFp.pszFaceName = L"Times New Roman";
            tmpFp.cHeight = decrease_font_height_for_fitting(hDc, &tmpFp, tmpText, get_rect_width(tmp_rect), h);
            hFont = WinApiFont::create_font(&tmpFp);
            if (hFont)
            {
                if (HeaderHfont) DeleteObject((HFONT)SelectObject(hDc, (HFONT)HeaderHfont));
                HeaderHfont = hFont;

                SendMessage(StaticCutoffHwnd, WM_SETFONT, (WPARAM)HeaderHfont, FALSE);
            }

            ReleaseDC(hWnd, hDc);
            firstSize = false;
            if (!firstSize) make_wnd_redraw(hWnd);
            return EXIT_SUCCESS;
        }

        case WM_COMMAND:
        {                
            switch (LOWORD(wParam))
            {
                case IDB_COMBOBOX_LIGHT:
                {
                    switch (HIWORD(wParam))
                    {
                        case CBN_SELCHANGE:
                        {
                            SetFocus(hWnd);
                            lightType = (LightType)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
                            WINBOOL enable = lightType == LIGHT_SPOT;

                            EnableWindow(StaticDirectionHwnd, enable);
                            EnableWindow(StaticDirXHwnd, enable);
                            EnableWindow(StaticDirYHwnd, enable);
                            EnableWindow(StaticDirZHwnd, enable);
                            EnableWindow(EditDirXHwnd, enable);
                            EnableWindow(EditDirYHwnd, enable);
                            EnableWindow(EditDirZHwnd, enable);
                            EnableWindow(StaticCutoffHwnd, enable);
                            EnableWindow(StaticInnerCutoffHwnd, enable);
                            EnableWindow(StaticInnerCutoffValHwnd, enable);
                            EnableWindow(StaticOuterCutoffHwnd, enable);
                            EnableWindow(StaticOuterCutoffValHwnd, enable);
                            EnableWindow(EditInnerCutoffValHwnd, enable);
                            EnableWindow(EditOuterCutoffValHwnd, enable);

                            SendMessage(app::RenderWnd.getHwnd(), WM_SET_LIGHT_TYPE, (WPARAM)&lightType, (LPARAM)0);
                            return EXIT_SUCCESS;
                        }

                        case CBN_CLOSEUP:
                        {
                            SetFocus(hWnd);
                            return EXIT_SUCCESS;
                        }

                        default:
                            return DefWindowProc(hWnd, uMsg, wParam, lParam);
                    }
                }

                case IDB_EDIT_POS_X:
                case IDB_EDIT_POS_Y:
                case IDB_EDIT_POS_Z:
                {
                    switch (HIWORD(wParam))
                    {
                        case EN_CHANGE:
                        {
                            GetWindowText(EditPosXHwnd, tmpText, MAX_PATH);
                            if (convert_str_to_float(tmpText, &msgVec.x))
                            {
                                GetWindowText(EditPosYHwnd, tmpText, MAX_PATH);
                                if (convert_str_to_float(tmpText, &msgVec.y))
                                {
                                    GetWindowText(EditPosZHwnd, tmpText, MAX_PATH);
                                    if (convert_str_to_float(tmpText, &msgVec.z))
                                    {
                                        SendMessage(app::RenderWnd.getHwnd(), WM_SET_LIGHT_POSITION, (WPARAM)&msgVec, (LPARAM)0);
                                    }
                                }
                            }


                            return EXIT_SUCCESS;
                        }

                        default:
                            return DefWindowProc(hWnd, uMsg, wParam, lParam);
                    }
                }

                case IDB_EDIT_DIR_X:
                case IDB_EDIT_DIR_Y:
                case IDB_EDIT_DIR_Z:
                {
                    switch (HIWORD(wParam))
                    {
                        case EN_CHANGE:
                        {
                            GetWindowText(EditDirXHwnd, tmpText, MAX_PATH);
                            if (convert_str_to_float(tmpText, &msgVec.x))
                            {
                                GetWindowText(EditDirYHwnd, tmpText, MAX_PATH);
                                if (convert_str_to_float(tmpText, &msgVec.y))
                                {
                                    GetWindowText(EditDirZHwnd, tmpText, MAX_PATH);
                                    if (convert_str_to_float(tmpText, &msgVec.z))
                                    {
                                        SendMessage(app::RenderWnd.getHwnd(), WM_SET_LIGHT_DIRECTION, (WPARAM)&msgVec, (LPARAM)0);
                                    }
                                }
                            }


                            return EXIT_SUCCESS;
                        }

                        default:
                            return DefWindowProc(hWnd, uMsg, wParam, lParam);
                    }
                }

                case IDB_BTN_CHOOSE_COLOR:
                {
                    SetFocus(hWnd);

                    if (choose_color_dialog(hWnd, &lightColor))
                    {
                        vec3_set(&msgVec, GetRValue(lightColor), GetGValue(lightColor), GetBValue(lightColor));
                        vec3_divide(&msgVec, 255.f);

                        SendMessage(app::RenderWnd.getHwnd(), WM_SET_LIGHT_COLOR, (WPARAM)&msgVec, (LPARAM)0);

                        InvalidateRect(hWnd, NULL, TRUE);
                        UpdateWindow(hWnd);
                    }
 
                    return EXIT_SUCCESS;
                }

                case IDB_EDIT_RADIUS:
                {
                    switch (HIWORD(wParam))
                    {
                        case EN_CHANGE:
                        {
                            GetWindowText(EditRadiusValHwnd, tmpText, MAX_PATH);
                            if (convert_str_to_float(tmpText, &msgFloat))
                            {
                                SendMessage(app::RenderWnd.getHwnd(), WM_SET_LIGHT_RADIUS, (WPARAM)&msgFloat, (LPARAM)0);
                            }

                            return EXIT_SUCCESS;
                        }

                        default:
                            return DefWindowProc(hWnd, uMsg, wParam, lParam);
                    }
                }

                case IDB_EDIT_INTENSITY:
                {
                    switch (HIWORD(wParam))
                    {
                        case EN_CHANGE:
                        {
                            GetWindowText(EditIntensityValHwnd, tmpText, MAX_PATH);
                            if (convert_str_to_float(tmpText, &msgFloat))
                            {
                                SendMessage(app::RenderWnd.getHwnd(), WM_SET_LIGHT_INTENSITY, (WPARAM)&msgFloat, (LPARAM)0);
                            }

                            return EXIT_SUCCESS;
                        }

                        default:
                            return DefWindowProc(hWnd, uMsg, wParam, lParam);
                    }
                }

                case IDB_EDIT_INNER_CUTOFF:
                {
                    switch (HIWORD(wParam))
                    {
                        case EN_CHANGE:
                        {
                            GetWindowText(EditInnerCutoffValHwnd, tmpText, MAX_PATH);
                            if (convert_str_to_float(tmpText, &msgFloat))
                            {
                                msgFloat = degrees_to_radians(msgFloat);
                                SendMessage(app::RenderWnd.getHwnd(), WM_SET_LIGHT_INNER_CUTOFF, (WPARAM)&msgFloat, (LPARAM)0);
                            }

                            return EXIT_SUCCESS;
                        }

                        default:
                            return DefWindowProc(hWnd, uMsg, wParam, lParam);
                    }
                }

                case IDB_EDIT_OUTER_CUTOFF:
                {
                    switch (HIWORD(wParam))
                    {
                        case EN_CHANGE:
                        {
                            GetWindowText(EditOuterCutoffValHwnd, tmpText, MAX_PATH);
                            if (convert_str_to_float(tmpText, &msgFloat))
                            {
                                msgFloat = degrees_to_radians(msgFloat);
                                SendMessage(app::RenderWnd.getHwnd(), WM_SET_LIGHT_OUTER_CUTOFF, (WPARAM)&msgFloat, (LPARAM)0);
                            }

                            return EXIT_SUCCESS;
                        }

                        default:
                            return DefWindowProc(hWnd, uMsg, wParam, lParam);
                    }
                }

                default:
                    return EXIT_SUCCESS;
            }
        }

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hDc = BeginPaint(hWnd, &ps);

            WinApiBrush Brush(hDc);

            Brush.select_solid(lightColor);
            Ellipse(
                hDc,
                lightColorRect.left, lightColorRect.top,
                lightColorRect.right, lightColorRect.bottom
            );

            EndPaint(hWnd, &ps);
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }

        case WM_DESTROY:
        {
            HDC hDc = GetDC(hWnd);

            if (LeftStaticOptionHfont) DeleteObject((HFONT)SelectObject(hDc, (HFONT)LeftStaticOptionHfont));
            if (VectorHfont) DeleteObject((HFONT)SelectObject(hDc, (HFONT)VectorHfont));
            if (HeaderHfont) DeleteObject((HFONT)SelectObject(hDc, (HFONT)HeaderHfont));

            ReleaseDC(hWnd, hDc);

            return DefWindowProc(hWnd, uMsg, wParam, lParam);    
        }

        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}