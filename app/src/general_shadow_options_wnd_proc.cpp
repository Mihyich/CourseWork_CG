#include "general_shadow_options_wnd_proc.h"

LRESULT CALLBACK GeneralShadowOptionsWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}