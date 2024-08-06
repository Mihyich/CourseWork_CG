#include "drawareainfo_wnd_poc.h"

void repos_child_wnds_in_drawareainfo_wnd(void)
{
    RECT rect;
    LONG width;

    GetClientRect(app::DrawAreaInfoWnd.hWnd, &rect);
    width = rect.right - rect.left;

    MoveWindow(
        app::scale_info_hwnd,
        width - 130 - 5, 2,
        130, 25,
        TRUE
    );
}

LRESULT CALLBACK DrawAreaInfoWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // шрифтец
    const static HFONT font = app::Fonts.get_font(L"Consolas20");

    switch(uMsg)
    {
        case WM_CREATE:
        {
            // Создание окна информации о позиции X
            app::coordX_info_hwnd = CreateWindowEx(
                0, L"STATIC", L"x: undefine", WS_CHILD | WS_VISIBLE | WS_BORDER,
                5, 2, 140, 25, hWnd, nullptr, app::hInst, nullptr);

            // Создание окна информации о позиции Y
            app::coordY_info_hwnd = CreateWindowEx(
                0, L"STATIC", L"y: undefine", WS_CHILD | WS_VISIBLE | WS_BORDER,
                150, 2, 140, 25, hWnd, nullptr, app::hInst, nullptr);

            // Создание окна информации о scale
            app::scale_info_hwnd = CreateWindowEx(
                0, L"STATIC", L"scale: 1.000", WS_CHILD | WS_VISIBLE | WS_BORDER,
                295, 2, 130, 25, hWnd, nullptr, app::hInst, nullptr);

            // установить шрифт в окна
            if (font)
            {
                SendMessage(app::coordX_info_hwnd, WM_SETFONT, (WPARAM)font, TRUE);
                SendMessage(app::coordY_info_hwnd, WM_SETFONT, (WPARAM)font, TRUE);
                SendMessage(app::scale_info_hwnd, WM_SETFONT, (WPARAM)font, TRUE);
            }

            return EXIT_SUCCESS;
        }

        case WM_SIZE:
        {
            repos_child_wnds_in_drawareainfo_wnd();
            return EXIT_SUCCESS;
        }

        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}