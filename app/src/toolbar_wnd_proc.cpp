#include "toolbar_wnd_proc.h"
    
LRESULT CALLBACK ToolbarWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_CREATE:
        {
            return EXIT_SUCCESS;
        }

        case WM_COMMAND:
        {                
            switch (LOWORD(wParam))
            {
                default:
                    return EXIT_SUCCESS;
            }
        }

        case WM_PAINT:
        {
            // PAINTSTRUCT ps;
            // HDC hDc = BeginPaint(hWnd, &ps);
            // // отрисовка
            // EndPaint(hWnd, &ps);

            // Отработать другие отрисовки, за которые я не ручаюсь
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }

        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}