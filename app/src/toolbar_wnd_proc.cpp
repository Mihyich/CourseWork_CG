#include "toolbar_wnd_proc.h"
    
LRESULT CALLBACK ToolbarWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static bool resizing = false;
    static POINT lastMousePos;
    static RECT originalRect;

    switch(uMsg)
    {
        case WM_CREATE:
        {
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
            int maxWidth;

            if (resizing)
            {
                GetCursorPos(&pt);
                ScreenToClient(hWnd, &pt);
                GetWindowRect(app::MainWnd.getHwnd(), &MainRect);
                dx = pt.x - lastMousePos.x;
                app::ToolbarWidth = std::min(std::max(originalRect.right - originalRect.left + dx, app::ToolbarMinWidth), get_rect_width(MainRect));
                SendMessage(app::MainWnd.getHwnd(), WM_SIZE, 0, 0);
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