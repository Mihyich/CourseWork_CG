#include "FpsSetterDialogProc.h"

LRESULT CALLBACK FpsSetterDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    static RECT rect;

    static HWND StaticFpsHwnd = nullptr;
    static HWND EditFpsHwnd = nullptr;

    static HWND ButtonCancelHwnd = nullptr;
    static HWND ButtonSetHwnd = nullptr;

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

            StaticFpsHwnd = GetDlgItem(hDlg, IDC_FPS_STATIC);
            EditFpsHwnd = GetDlgItem(hDlg, IDC_FPS_EDIT);

            ButtonCancelHwnd = GetDlgItem(hDlg, IDC_FPS_CANCEL);
            ButtonSetHwnd = GetDlgItem(hDlg, IDC_FPS_SET);

            posX = 5;
            posY = 5;
            tmp_width = (width - 15) * 0.75f;
            tmp_height = 24;    

            SetWindowPos(StaticFpsHwnd, HWND_TOP, posX, posY, tmp_width, tmp_height, SWP_SHOWWINDOW);

            posX += tmp_width + 5;
            tmp_width = width - posX - 5;

            SetWindowPos(EditFpsHwnd, HWND_TOP, posX, posY, tmp_width, tmp_height, SWP_SHOWWINDOW);

            tmp_width = (width - 10) / 4;
            tmp_height = 24;
            posX = 5;
            posY = height - 5 - tmp_height;

            SetWindowPos(ButtonCancelHwnd, HWND_TOP, posX, posY, tmp_width, tmp_height, SWP_SHOWWINDOW);

            posX = width - 5 - tmp_width;

            SetWindowPos(ButtonSetHwnd, HWND_TOP, posX, posY, tmp_width, tmp_height, SWP_SHOWWINDOW);

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

            GetWindowRect(StaticFpsHwnd, &tmp_rect);
            GetWindowText(StaticFpsHwnd, tmpText, MAX_PATH);
            fp.cHeight = 1;
            fp.cHeight = increase_font_height_for_fitting_height(hDc, &fp, tmpText, 16);
            hFont = WinApiFont::create_font(&fp);
            if (hFont) SendMessage(StaticFpsHwnd, WM_SETFONT, (WPARAM)hFont, TRUE);

            GetWindowRect(ButtonCancelHwnd, &tmp_rect);
            GetWindowText(ButtonCancelHwnd, tmpText, MAX_PATH);
            fp.cHeight = 1;
            fp.cHeight = increase_font_height_for_fitting(hDc, &fp, tmpText, get_rect_width(tmp_rect), 16);
            hFont = WinApiFont::create_font(&fp);
            if (hFont) SendMessage(ButtonCancelHwnd, WM_SETFONT, (WPARAM)hFont, TRUE);

            GetWindowRect(ButtonSetHwnd, &tmp_rect);
            GetWindowText(ButtonSetHwnd, tmpText, MAX_PATH);
            fp.cHeight = 1;
            fp.cHeight = increase_font_height_for_fitting(hDc, &fp, tmpText, get_rect_width(tmp_rect), 16);
            hFont = WinApiFont::create_font(&fp);
            if (hFont) SendMessage(ButtonSetHwnd, WM_SETFONT, (WPARAM)hFont, TRUE);

            ReleaseDC(hDlg, hDc);
            SetFocus(hDlg);
            return TRUE;
        }

        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
                case IDC_FPS_SET:
                {
                    SetFocus(hDlg);
                    
                    if (EditFpsHwnd)
                    {
                        GetWindowText(EditFpsHwnd, tmpText, MAX_PATH);
                        long fps;
                        if (convert_str_to_long(tmpText, &fps))
                        {
                            SendMessage(app::MainWnd.getHwnd(), WM_SET_FRAME_PER_SECOND, (WPARAM)&fps, (LPARAM)0);
                        }
                    }

                    break;
                }

                case IDC_ML_CANCEL:
                {
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