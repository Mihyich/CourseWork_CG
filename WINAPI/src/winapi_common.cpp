#include "winapi_common.h"

void make_wnd_redraw(HWND hWnd)
{
    if (!hWnd) return;
    InvalidateRect(hWnd, nullptr, TRUE);
    UpdateWindow(hWnd);
}

void set_wnd_showmode(int mode, size_t count, ...)
{
    va_list args;
    va_start(args, count);

    for (size_t i = 0; i < count; ++i)
    {
        HWND hWnd = va_arg(args, HWND);
        ShowWindow(hWnd, mode);
    }

    va_end(args);
}

void getAppExecutePath(HINSTANCE hInst, WCHAR path[MAX_PATH])
{
    if (!hInst) return;
    GetModuleFileName(hInst, path, MAX_PATH);
}

void LaunchAsyncApp(LPCWSTR programPath)
{
    // Создание структуры для запуска процесса
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    // Заполнение структуры STARTUPINFO
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);

    // Запуск нового процесса
    if (CreateProcess(programPath, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
}

UINT GetWindowShowMode(HWND hWnd)
{
    WINDOWPLACEMENT wndPlacement;
    wndPlacement.length = sizeof(WINDOWPLACEMENT);
    return GetWindowPlacement(hWnd, &wndPlacement);
}

VOID DisableAeroForWindow(HWND hWnd)
{
    BOOL isDwmEnabled = FALSE;

    if (SUCCEEDED(DwmIsCompositionEnabled(&isDwmEnabled)) && isDwmEnabled)
    {
        // Отключение прозрачности для этого окна
        BOOL disable = TRUE;
        DwmSetWindowAttribute(hWnd, DWMWA_TRANSITIONS_FORCEDISABLED, &disable, sizeof(disable));

        // Выключение размытия фона для окна
        DWM_BLURBEHIND bb = {0};
        bb.dwFlags = DWM_BB_ENABLE;
        bb.fEnable = FALSE;
        DwmEnableBlurBehindWindow(hWnd, &bb);
    }
}