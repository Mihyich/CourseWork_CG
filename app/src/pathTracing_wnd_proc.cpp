#include "pathTracing_wnd_proc.h"

LRESULT CALLBACK PathTracingWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}