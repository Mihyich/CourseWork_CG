#include "rayTracing_wnd_proc.h"

LRESULT CALLBACK RayTracingWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}