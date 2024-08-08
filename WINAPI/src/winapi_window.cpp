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
    return CreateWndProcess(
        windowName,
        hInst,
        cmdShow,
        pWndProc,
        lpszClassName,
        lpszMenuName,
        width,  height,
        classStyle,
        windowStyle,
        windowStyleEx,
        hParent
    );
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

HWND WinApiWindow::getHwnd()
{
    return this->hWnd;
}

INT WinApiWindow::getWidth()
{
    return rect.right - rect.left;
}

INT WinApiWindow::getHeight()
{
    return rect.bottom - rect.top;
}

DWORD WinApiWindow::get_last_error()
{
    return this->error;
}

VOID WinApiWindow::getAlignRect(RECT &dist_rect, INT width, INT height)
{
    dist_rect.left = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
    dist_rect.right = dist_rect.left + width;
    dist_rect.top = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
    dist_rect.bottom = dist_rect.top + height;
}

BOOL WinApiWindow::CreateWndProcess(
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
    BOOL result = WINDOW_CREATED;

    // регистрация класса окна
    if (!RegWndClass(sizeof(wcx), classStyle,
		pWndProc,
		hInst,
		LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
        (HBRUSH)(COLOR_WINDOW),
		lpszMenuName,
		lpszClassName,
        LoadIcon(NULL, IDI_APPLICATION)))
	{
        reset_and_free_data();
        error = GetLastError();

		MessageBox(NULL,
			L"ErrorWndClassRg", L"ErrorWndTitle",
			MB_OK | MB_ICONERROR);

		result = ERR_WNDCLASS_GEN;
	}
    else
    {
        this->ClassName.assign(lpszClassName);
        this->hInstance = hInst;

        getAlignRect(rect, width, height);

        hWnd = CreateWindowEx(
            windowStyleEx, lpszClassName,
            windowName, windowStyle,
            rect.left, rect.top,
            width, height,
            hParent,
            HMENU(NULL),
            hInst,
            NULL);

        if (!hWnd)
        {
            reset_and_free_data();
            error = GetLastError();

            MessageBox(NULL,
			L"ErrorWndCreate", L"ErrorWndTitle",
			MB_OK | MB_ICONERROR);

            result = ERR_WINDOW_GEN;
        }
        else
        {
            ShowWindow(hWnd, cmdShow);

            if (GetLastError() != ERROR_SUCCESS)
            {
                reset_and_free_data();
                error = GetLastError();
                result = ERR_WNDSHOW;
            }
            else
            {
                /*
                переустановить курсор (чтобы при создании окна,
                мышь сразу была правильной)
                */
                SetCursor(LoadCursor(nullptr, IDC_ARROW));
            }
        }
    }

    return result;
}

BOOL WinApiWindow::RegWndClass(
    UINT cbSize,
	UINT style,
	LRESULT(WINAPI *pWndProc)(HWND, UINT, WPARAM, LPARAM),
	HINSTANCE hInstance,
	HICON hIcon,
	HCURSOR hCursor,
    HBRUSH hbrBackground,
	LPCWSTR lpszMenuName,
	LPCWSTR lpszClassName,
    HICON hIconSm)
{
    ZeroMemory(&wcx, sizeof(WNDCLASSEX));

    wcx.cbSize = cbSize;
	wcx.style = style;
	wcx.lpfnWndProc = (WNDPROC)pWndProc;
	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.hInstance = hInstance;
	wcx.hIcon = hIcon;
	wcx.hCursor = hCursor;
    wcx.hbrBackground = hbrBackground;
	wcx.lpszMenuName = lpszMenuName;
	wcx.lpszClassName = lpszClassName;
    wcx.hIconSm = hIconSm;

	return RegisterClassEx(&wcx);
}

VOID WinApiWindow::reset_and_free_data()
{
    // почистить ресурсы окна (почистить все на всякий случай)
    DestroyWindow(this->hWnd);
    UnregisterClass(this->ClassName.c_str(), this->hInstance);
    DestroyAcceleratorTable(this->hAccel);

    // обнулить все данные
    this->hInstance = NULL;
    this->hWnd = NULL;
    this->ClassName.clear();
    this->hAccel = NULL;
}