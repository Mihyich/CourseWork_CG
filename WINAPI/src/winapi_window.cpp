#include "winapi_window.h"

BOOL WinApiWindow::Create(
    LPCTSTR windowName,
    HINSTANCE hInst,
    INT cmdShow,
    LRESULT(WINAPI *pWndProc)(HWND, UINT, WPARAM, LPARAM),
    LPCWSTR lpszClassName,
    LPCWSTR lpszMenuName,
    INT width, INT height,
    UINT classStyle,
    DWORD windowStyle,
    DWORD windowStyleEx,
    HWND hParent)
{
    BOOL result = EXIT_SUCCESS;

    // регистрация класса окна
    if (!RegWndClass(sizeof(wcx), classStyle,
		pWndProc,
		hInst,
		LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
		lpszMenuName,
		lpszClassName))
	{
		MessageBox(NULL,
			L"ErrorWndClassRg", L"ErrorWndTitle",
			MB_OK | MB_ICONERROR);

		result = EXIT_FAILURE;
	}
    else
    {
        hWnd = CreateWindowEx(
            windowStyleEx, lpszClassName,
            windowName, windowStyle,
            0, 0,
            width, height,
            hParent,
            HMENU(NULL),
            hInst,
            NULL);

        if (!hWnd)
        {
            MessageBox(NULL,
			L"ErrorWndCreate", L"ErrorWndTitle",
			MB_OK | MB_ICONERROR);

            result = EXIT_FAILURE;
        }
        else
        {
            ShowWindow(hWnd, cmdShow);
        }
    }

    return result;
}

INT WinApiWindow::MainLoop()
{
    if (!hWnd)
		return FALSE;

    MSG msg;

    // Событийный обработчик событий (если сообщений нет прогримма прерывается, и останавливается на GetMessage)
    while (GetMessage(&msg, NULL, 0, 0))
	{
        TranslateMessage(&msg);
        DispatchMessage(&msg);
	}

    return 0;
}

void WinApiWindow::peek_msgs(void) const
{
    MSG msg;

    // Обработать все сообщения, которые есть в очереди (Если сообщения закончились, цикл  прервется)
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

VOID WinApiWindow::Destroy()
{
    if (hWnd)
	{
		DestroyWindow(hWnd);
		hWnd = NULL;
	}

	UnregisterClass(wcx.lpszClassName, wcx.hInstance);
}

BOOL WinApiWindow::RegWndClass(
    UINT cbSize,
	UINT style,
	LRESULT(WINAPI *pWndProc)(HWND, UINT, WPARAM, LPARAM),
	HINSTANCE hInstance,
	HICON hIcon,
	HCURSOR hCursor,
	LPCWSTR lpszMenuName,
	LPCWSTR lpszClassName)
{
    wcx.cbSize = cbSize;
	wcx.style = style;
	wcx.lpfnWndProc = (WNDPROC)pWndProc;
	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.hInstance = hInstance;
	wcx.hIcon = hIcon;
	wcx.hCursor = hCursor;
	wcx.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wcx.lpszMenuName = lpszMenuName;
	wcx.lpszClassName = lpszClassName;
	wcx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	return !RegisterClassEx(&wcx) ? FALSE : TRUE;
}