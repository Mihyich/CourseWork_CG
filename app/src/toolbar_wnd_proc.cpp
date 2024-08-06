#include "toolbar_wnd_proc.h"
    
LRESULT CALLBACK ToolbarWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // регионы обновления квадратиков
    static RECT rect_surface_color = {0, 0, 0, 0};

    // шрифты
    const static HFONT math_font = app::Fonts.get_font(L"Calibri25");
    const static HFONT header_font = app::Fonts.get_font(L"Arial30");
    const static HFONT caption_font = app::Fonts.get_font(L"Consolas25");

    // окна ...

    static HWND SurfaceHeaderHwnd = nullptr; // Заголовок функции поверхности
    static HWND SurfaceInputHwnd = nullptr; // Ввод функции поверхности

    static HWND LimitsHeaderHwnd = nullptr; // Заголовок ограничений функции

    static HWND XLimitCaptionHwnd = nullptr;
    static HWND XLimitInputHwnd = nullptr;

    static HWND ZLimiCaptionHwnd = nullptr;
    static HWND ZLimitInputHwnd = nullptr;

    static HWND XStepCaptionHwnd = nullptr;
    static HWND XStepInputHwnd = nullptr;

    static HWND ZStepCaptionHwnd = nullptr;
    static HWND ZStepInputHwnd = nullptr;

    static HWND SurfaceColorSelecterHeaderHwnd = nullptr; // Заголовок выбора цвета поверхности
    static HWND SurfaceColorSelecterCaptionHwnd = nullptr; // Содержание выбора цвета поверхности
    static HWND SurfaceColorSelecterBtnHwnd = nullptr; // кнопка выбора цвета поверхности

    static HWND BuildSurfaceBtnHwnd = nullptr; // кнопка запуска рисования поверхности

    switch(uMsg)
    {
        case WM_CREATE:
        {
            LONG height = 5;

            SurfaceHeaderHwnd = CreateWindowEx(
                0, L"STATIC", L"Функция поверхности", WS_CHILD | WS_VISIBLE | ES_CENTER,
                0, height, app::ToolbarWidth, 30,
                hWnd, (HMENU)NULL, app::hInst, nullptr);

            height += 35;

            SurfaceInputHwnd = CreateWindowEx(
                0, L"COMBOBOX", L"", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_HASSTRINGS,
                5, height, app::ToolbarWidth - 10, 30 * 8,
                hWnd, (HMENU)IDB_SURFACE_FUNC, app::hInst, nullptr);

            // =======================================

            height += 35;

            LimitsHeaderHwnd = CreateWindowEx(
                0, L"STATIC", L"Ограничения функции", WS_CHILD | WS_VISIBLE | ES_CENTER,
                0, height, app::ToolbarWidth, 30,
                hWnd, (HMENU)NULL, app::hInst, nullptr);

            height += 35;

            XLimitCaptionHwnd = CreateWindowEx(
                0, L"STATIC", L"Диапазон X:", WS_CHILD | WS_VISIBLE | ES_LEFT,
                5 , height, 140, 30,
                hWnd, (HMENU)NULL, app::hInst, nullptr);

            XLimitInputHwnd = CreateWindowEx(
                0, L"EDIT", L"-3.1415 3.1415", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_CENTER | WS_BORDER,
                150, height, app::ToolbarWidth - 150 - 5, 30,
                hWnd, (HMENU)IDB_X_LIMIT, app::hInst, nullptr);

            height += 35;

            ZLimiCaptionHwnd = CreateWindowEx(
                0, L"STATIC", L"Диапазон Z:", WS_CHILD | WS_VISIBLE | ES_LEFT,
                5 , height, 140, 30,
                hWnd, (HMENU)NULL, app::hInst, nullptr);

            
            ZLimitInputHwnd = CreateWindowEx(
                0, L"EDIT", L"-3.1415 3.1415", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_CENTER | WS_BORDER,
                150, height, app::ToolbarWidth - 150 - 5, 30,
                hWnd, (HMENU)IDB_Z_LIMIT, app::hInst, nullptr);

            height += 35;

            XStepCaptionHwnd = CreateWindowEx(
                0, L"STATIC", L"Шаг X:", WS_CHILD | WS_VISIBLE | ES_LEFT,
                5 , height, 140, 30,
                hWnd, (HMENU)NULL, app::hInst, nullptr);

            XStepInputHwnd = CreateWindowEx(
                0, L"EDIT", L"0.1", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_CENTER | WS_BORDER,
                150, height, app::ToolbarWidth - 150 - 5, 30,
                hWnd, (HMENU)IDB_X_STEP, app::hInst, nullptr);

            height += 35;

            ZStepCaptionHwnd = CreateWindowEx(
                0, L"STATIC", L"Шаг Z:", WS_CHILD | WS_VISIBLE | ES_LEFT,
                5 , height, 140, 30,
                hWnd, (HMENU)NULL, app::hInst, nullptr);

            ZStepInputHwnd = CreateWindowEx(
                0, L"EDIT", L"0.1", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_CENTER | WS_BORDER,
                150, height, app::ToolbarWidth - 150 - 5, 30,
                hWnd, (HMENU)IDB_Z_STEP, app::hInst, nullptr);

            // =======================================

            height += 35;

            SurfaceColorSelecterHeaderHwnd = CreateWindowEx(
                0, L"STATIC", L"Цвет поверхности", WS_CHILD | WS_VISIBLE | ES_CENTER,
                0, height, app::ToolbarWidth, 30,
                hWnd, (HMENU)NULL, app::hInst, nullptr);

            height += 35;

            SurfaceColorSelecterCaptionHwnd = CreateWindowEx(
                0, L"STATIC", L"Текущий цвет:", WS_CHILD | WS_VISIBLE | ES_LEFT,
                5, height, 160, 30,
                hWnd, (HMENU)NULL, app::hInst, nullptr);

            rect_surface_color = {app::ToolbarWidth - 150, height, app::ToolbarWidth - 150 + 30, height + 30};
            
            SurfaceColorSelecterBtnHwnd = CreateWindowEx(
                0, L"BUTTON", L"Выбрать",
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHLIKE,
                app::ToolbarWidth - 115, height, 110, 30,
                hWnd, (HMENU)IDB_CHOOSE_SURFACE_COLOR, app::hInst, nullptr);

            height += 35;

            // =====================================

            BuildSurfaceBtnHwnd = CreateWindowEx(
                0, L"BUTTON", L"Построить",
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHLIKE,
                5, height, app::ToolbarWidth - 10, 30,
                hWnd, (HMENU)IDB_SURFACE_LAUNCH, app::hInst, nullptr);
        
            // установка шрифтов

            if (header_font)
            {
                SendMessage(SurfaceHeaderHwnd, WM_SETFONT, (WPARAM)header_font, TRUE);
                SendMessage(LimitsHeaderHwnd, WM_SETFONT, (WPARAM)header_font, TRUE);

                SendMessage(SurfaceColorSelecterHeaderHwnd, WM_SETFONT, (WPARAM)header_font, TRUE);
            }

            if (caption_font)
            {
                SendMessage(XLimitCaptionHwnd, WM_SETFONT, (WPARAM)caption_font, TRUE);
                SendMessage(ZLimiCaptionHwnd, WM_SETFONT, (WPARAM)caption_font, TRUE);

                SendMessage(SurfaceColorSelecterCaptionHwnd, WM_SETFONT, (WPARAM)caption_font, TRUE);
                SendMessage(SurfaceColorSelecterBtnHwnd, WM_SETFONT, (WPARAM)caption_font, TRUE);

                SendMessage(XStepCaptionHwnd, WM_SETFONT, (WPARAM)caption_font, TRUE);
                SendMessage(ZStepCaptionHwnd, WM_SETFONT, (WPARAM)caption_font, TRUE);

                SendMessage(BuildSurfaceBtnHwnd, WM_SETFONT, (WPARAM)caption_font, TRUE);
            }

            if (math_font)
            {
                SendMessage(SurfaceInputHwnd, WM_SETFONT, (WPARAM)math_font, TRUE);

                SendMessage(XLimitInputHwnd, WM_SETFONT, (WPARAM)math_font, TRUE);
                SendMessage(ZLimitInputHwnd, WM_SETFONT, (WPARAM)math_font, TRUE);

                SendMessage(XStepInputHwnd, WM_SETFONT, (WPARAM)math_font, TRUE);
                SendMessage(ZStepInputHwnd, WM_SETFONT, (WPARAM)math_font, TRUE);
            }

            SendMessage(SurfaceInputHwnd, CB_ADDSTRING, (WPARAM)0, (LPARAM)L"0");
            SendMessage(SurfaceInputHwnd, CB_ADDSTRING, (WPARAM)0, (LPARAM)L"x^2 + z^2");
            SendMessage(SurfaceInputHwnd, CB_ADDSTRING, (WPARAM)0, (LPARAM)L"sin(x) * sin(z)");
            SendMessage(SurfaceInputHwnd, CB_ADDSTRING, (WPARAM)0, (LPARAM)L"cos(x) * cos(z)");
            SendMessage(SurfaceInputHwnd, CB_ADDSTRING, (WPARAM)0, (LPARAM)L"acos(sin(x)) * asin(cos(z))");
            SendMessage(SurfaceInputHwnd, CB_ADDSTRING, (WPARAM)0, (LPARAM)L"tan(sin(x + PI / 2)) + exp(cos(2 * (x + PI / 2)))");

            SendMessage(SurfaceInputHwnd, CB_SETCURSEL, (WPARAM)vals::formula, 0);

            return EXIT_SUCCESS;
        }

        case WM_COMMAND:
        {                
            switch (LOWORD(wParam))
            {
                case IDB_SURFACE_FUNC:
                {
                    switch (HIWORD(wParam))
                    {
                        case CBN_SELCHANGE:
                        {
                            vals::formula = (Formula)SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
                            SetFocus(hWnd);
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

                case IDB_CHOOSE_SURFACE_COLOR:
                {
                    if (choose_color_dialog(hWnd, &vals::surface_color))
                    {
                        // перерисовать только квадратик
                        InvalidateRect(hWnd, &rect_surface_color, TRUE);
                        UpdateWindow(hWnd);

                        std::wstring err_msg;
                        if ((vals::need_resolve = check_input_data(XLimitInputHwnd, ZLimitInputHwnd, XStepInputHwnd, ZStepInputHwnd, err_msg)))
                        {
                            make_wnd_redraw(app::DrawAreaWnd.hWnd);
                        }
                    }

                    SetFocus(hWnd);   
                    return EXIT_SUCCESS;
                }

                case IDB_SURFACE_LAUNCH:
                {
                    std::wstring err_msg;

                    if ((vals::need_resolve = check_input_data(XLimitInputHwnd, ZLimitInputHwnd, XStepInputHwnd, ZStepInputHwnd, err_msg)))
                    {
                        get_wnd_point_input(XLimitInputHwnd, &vals::x_range);
                        get_wnd_point_input(ZLimitInputHwnd, &vals::z_range);

                        get_wnd_float_input(XStepInputHwnd, &vals::x_step);
                        get_wnd_float_input(ZStepInputHwnd, &vals::z_step);

                        make_wnd_redraw(app::DrawAreaWnd.hWnd);
                    }
                    else
                    {
                        MessageBox(
                            hWnd, err_msg.c_str(),
                            L"Ошибка форматирования",
                            MB_OK
                        );
                    }

                    SetFocus(hWnd);
                    return EXIT_SUCCESS;
                }

                default:
                {
                    return EXIT_SUCCESS;
                }
            }
        }

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hDc = BeginPaint(hWnd, &ps);
            WinApiBrush Brush(hDc);

            Brush.select_solid(vals::surface_color);
            Rectangle(
                hDc,
                rect_surface_color.left, rect_surface_color.top,
                rect_surface_color.right, rect_surface_color.bottom
            );

            EndPaint(hWnd, &ps);

            // Отработать другие отрисовки, за которые я не ручаюсь
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }

        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}