#include "render_wnd_proc.h"

LRESULT RenderWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static RECT client_rect;
    static int client_width;
    static int client_height;

    static float v = 0.0f;

    switch (message)
    {

    case WM_SIZE:
    {
        GetClientRect(hWnd, &client_rect);
        glViewport(0, 0, client_width, client_height);
        return EXIT_SUCCESS;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        v += 0.2f;
        glClearColor(sinf(v), cosf(v), 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        SwapBuffers(hdc);

        EndPaint(hWnd, &ps);
        return EXIT_SUCCESS;
    }

    case WM_ERASEBKGND:
    {
        return EXIT_FAILURE;
    }

    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}