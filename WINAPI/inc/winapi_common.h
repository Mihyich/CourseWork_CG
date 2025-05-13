#ifndef WINAPI_COMMON_H
#define WINAPI_COMMON_H

#include <windows.h>
#include <dwmapi.h>
#include <cstdarg>

void make_wnd_redraw(HWND hWnd);

void set_wnd_showmode(int mode, size_t count, ...);

void getAppExecutePath(HINSTANCE hInst, WCHAR path[MAX_PATH]);

void LaunchAsyncApp(LPCWSTR programPath);

void GetAlignCenterRect(INT width, INT height, RECT *rect);

UINT GetWindowShowMode(HWND hWnd);

VOID DisableAeroForWindow(HWND hWnd);

#endif // WINAPI_COMMON_H