#include "model_wnd_proc.h"

LRESULT CALLBACK ModelWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}