#include "toolbar_wnd_proc.h"
    
LRESULT CALLBACK ToolbarWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static bool isResizing = false;
    static RECT resizeRect; // Прямоугольник, определяющий зону для захвата изменения размера
    static int resizeBorderWidth = 30; // Ширина области для изменения размера
    static POINT lastMousePos;
    static HWND hResizeWnd = nullptr; // Окно, которое мы изменяем в данный момент

    switch(uMsg)
    {
        case WM_CREATE:
        {
            return EXIT_SUCCESS;
        }

        case WM_MOUSEMOVE:
        {
            if (isResizing && wParam == MK_LBUTTON)
            {
                POINT pt;
                GetCursorPos(&pt);
                ScreenToClient(hWnd, &pt);

                int dx = pt.x - lastMousePos.x;
                int dy = pt.y - lastMousePos.y;

                int newWidth = resizeRect.right - resizeRect.left + dx;
                int newHeight = resizeRect.bottom - resizeRect.top + dy;

                // Убедимся, что окно не становится слишком маленьким
                const int minWidth = 100;
                const int minHeight = 100;

                if (newWidth < minWidth) newWidth = minWidth;
                if (newHeight < minHeight) newHeight = minHeight;

                app::ToolbarWidth = newWidth;
                lastMousePos = pt;

                SendMessage(app::MainWnd.getHwnd(), WM_SIZE, 0, 0);
            }
            return EXIT_SUCCESS;
        }

        case WM_NCHITTEST:
        {
            LRESULT hit = DefWindowProc(hWnd, uMsg, wParam, lParam);

            if (hit == HTCLIENT)
            {
                POINT pt;
                GetCursorPos(&pt);
                ScreenToClient(hWnd, &pt);
                GetClientRect(hWnd, &resizeRect);

                if (pt.x >= resizeRect.right - resizeBorderWidth)
                {
                    pt.x = resizeRect.right - resizeBorderWidth / 2;
                    lastMousePos = pt;
                    isResizing = true;
                }
                else
                {
                    isResizing = false;
                }
            }

            return hit;
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