#include "ModelLoaderDialogProc.h"

LRESULT CALLBACK ModelLoaderDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    static RECT rect;

    static HWND EditMLPathHwnd = nullptr;
    static HWND ButtonMLExploreHwnd = nullptr;

    static HWND CheckBoxMLInverseHwnd = nullptr;
    static HWND StaticMLInverseHwnd = nullptr;

    static HWND ButtonCancelHwnd = nullptr;
    static HWND ButtonLoadHwnd = nullptr;

    static WCHAR EditMLPathText[MAX_PATH];
    static float pathLinePart = 4.f / 5.f;
    static bool CCW;
    static WCHAR tmpText[MAX_PATH];

    switch (message)
    {
        case WM_INITDIALOG:
        {
            HDC hDc = GetDC(hDlg);

            FontParam fp;
            HFONT hFont;

            RECT tmp_rect;
            int tmp_width = 350;
            int tmp_height = 300;

            int width;
            int height;

            RECT mainRect;
            GetWindowRect(app::MainWnd.getHwnd(), &mainRect);

            int posX = mainRect.left + (get_rect_width(mainRect) - tmp_width) / 2;
            int posY = mainRect.top + (get_rect_height(mainRect) - tmp_height) / 2;

            SetWindowPos(hDlg, HWND_TOP, posX, posY, tmp_width, tmp_height, SWP_SHOWWINDOW);
            UpdateWindow(hDlg);
            GetClientRect(hDlg, &rect);

            width = get_rect_width(rect);
            height = get_rect_height(rect);

            EditMLPathHwnd = GetDlgItem(hDlg, IDC_ML_PATH);
            ButtonMLExploreHwnd = GetDlgItem(hDlg, IDC_ML_EXPLORE);

            CheckBoxMLInverseHwnd = GetDlgItem(hDlg, IDC_ML_INVERSE_CB);
            StaticMLInverseHwnd = GetDlgItem(hDlg, IDC_ML_INVERTSE_STATIC);

            ButtonCancelHwnd = GetDlgItem(hDlg, IDC_ML_CANCEL);
            ButtonLoadHwnd = GetDlgItem(hDlg, IDC_ML_LOAD);

            SendMessage(CheckBoxMLInverseHwnd, BM_SETCHECK, (WPARAM)BST_CHECKED, 0); 
            CCW = SendMessage(CheckBoxMLInverseHwnd, BM_GETCHECK, 0, 0) == BST_CHECKED;

            posX = 5;
            posY = 5;
            tmp_width = (width - 15) * pathLinePart;
            tmp_height = 24;    

            SetWindowPos(EditMLPathHwnd, HWND_TOP, posX, posY, tmp_width, tmp_height, SWP_SHOWWINDOW);

            posX += tmp_width + 5;
            tmp_width = width - posX - 5;

            SetWindowPos(ButtonMLExploreHwnd, HWND_TOP, posX, posY, tmp_width, tmp_height, SWP_SHOWWINDOW);

            posX = 5;
            posY += tmp_height + 5;
            tmp_width = 24;

            SetWindowPos(CheckBoxMLInverseHwnd, HWND_TOP, posX, posY, tmp_width, tmp_height, SWP_SHOWWINDOW);

            posX += tmp_width + 5;
            tmp_width = width - 5 - posX;

            SetWindowPos(StaticMLInverseHwnd, HWND_TOP, posX, posY, tmp_width, tmp_height, SWP_SHOWWINDOW);

            tmp_width = (width - 10) / 4;
            tmp_height = 24;
            posX = 5;
            posY = height - 5 - tmp_height;

            SetWindowPos(ButtonCancelHwnd, HWND_TOP, posX, posY, tmp_width, tmp_height, SWP_SHOWWINDOW);

            posX = width - 5 - tmp_width;

            SetWindowPos(ButtonLoadHwnd, HWND_TOP, posX, posY, tmp_width, tmp_height, SWP_SHOWWINDOW);

            fp.cWidth = 0;
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

            GetWindowRect(EditMLPathHwnd, &tmp_rect);
            GetWindowText(EditMLPathHwnd, EditMLPathText, MAX_PATH);
            fp.cHeight = 1;
            fp.cHeight = increase_font_height_for_fitting_height(hDc, &fp, EditMLPathText, 16);
            hFont = WinApiFont::create_font(&fp);
            if (hFont) SendMessage(EditMLPathHwnd, WM_SETFONT, (WPARAM)hFont, TRUE);

            GetWindowRect(ButtonMLExploreHwnd, &tmp_rect);
            GetWindowText(ButtonMLExploreHwnd, tmpText, MAX_PATH);
            fp.cHeight = 1;
            fp.cHeight = increase_font_height_for_fitting(hDc, &fp, tmpText, get_rect_width(tmp_rect), 16);
            hFont = WinApiFont::create_font(&fp);
            if (hFont) SendMessage(ButtonMLExploreHwnd, WM_SETFONT, (WPARAM)hFont, TRUE);

            GetWindowRect(StaticMLInverseHwnd, &tmp_rect);
            GetWindowText(StaticMLInverseHwnd, tmpText, MAX_PATH);
            fp.cHeight = 1;
            fp.cHeight = increase_font_height_for_fitting(hDc, &fp, tmpText, get_rect_width(tmp_rect), 16);
            hFont = WinApiFont::create_font(&fp);
            if (hFont) SendMessage(StaticMLInverseHwnd, WM_SETFONT, (WPARAM)hFont, TRUE);

            GetWindowRect(ButtonCancelHwnd, &tmp_rect);
            GetWindowText(ButtonCancelHwnd, tmpText, MAX_PATH);
            fp.cHeight = 1;
            fp.cHeight = increase_font_height_for_fitting(hDc, &fp, tmpText, get_rect_width(tmp_rect), 16);
            hFont = WinApiFont::create_font(&fp);
            if (hFont) SendMessage(ButtonCancelHwnd, WM_SETFONT, (WPARAM)hFont, TRUE);

            GetWindowRect(ButtonLoadHwnd, &tmp_rect);
            GetWindowText(ButtonLoadHwnd, tmpText, MAX_PATH);
            fp.cHeight = 1;
            fp.cHeight = increase_font_height_for_fitting(hDc, &fp, tmpText, get_rect_width(tmp_rect), 16);
            hFont = WinApiFont::create_font(&fp);
            if (hFont) SendMessage(ButtonLoadHwnd, WM_SETFONT, (WPARAM)hFont, TRUE);

            ReleaseDC(hDlg, hDc);

            // Прокрутка до начала строки
            SendMessage(EditMLPathHwnd, EM_SETSEL, 0, 0);

            SetFocus(hDlg);
            return TRUE;
        }

        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
                case IDC_ML_EXPLORE:
                {
                    if (ChooseFileDialog(hDlg, EditMLPathText, L"Models (*.obj)\0*.obj\0", L".\\"))
                    {
                        SendMessage(EditMLPathHwnd, WM_SETTEXT, 0, (LPARAM)EditMLPathText);
                    }

                    SetFocus(hDlg);
                    break;
                }

                case IDC_ML_INVERSE_CB:
                {
                    CCW = SendMessage(CheckBoxMLInverseHwnd, BM_GETCHECK, 0, 0) == BST_CHECKED;
                    SetFocus(hDlg);
                    break;
                }

                case IDC_ML_CANCEL:
                {
                    SendMessage(hDlg, WM_CLOSE, 0, 0);
                    break;
                }

                case IDC_ML_LOAD:
                {
                    if (!SendMessage(app::RenderWnd.getHwnd(), WM_LOAD_MODEL, (WPARAM)EditMLPathText, (LPARAM)CCW))
                        SetFocus(hDlg);
                    else
                        SendMessage(hDlg, WM_CLOSE, 0, 0);

                    break;
                }

                default:
                    break;
            }

            return TRUE;
        }

        case WM_CLOSE:
        {
            return EndDialog(hDlg, LOWORD(wParam));
        }

        case WM_DESTROY:
        {
            
            return FALSE;
        }
    }

    return FALSE;
}