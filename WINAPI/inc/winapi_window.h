#ifndef WINAPI_WINDOW_H
#define WINAPI_WINDOW_H

#include <Windows.h>

class WinApiWindow
{
public:
    HWND hWnd = NULL; // Дескриптор окна (ручка для обращения к окну)
	WNDCLASSEX wcx; // Класс окна (описывает как выглядит окно)

    /**
     * windowName - Имя окна (в заголовке)
     * hInst - дескриптор приложения
     * cmdShow - режим отображения окна (но можно и свой)
     * pWndProc - функция обработки сообщений системы
     * lpszClassName - имя класса окна
     * lpszMenuName - имя меню (если есть)
     * width, height - размеры окна
     * classStyle - стиль класса окна
     * windowStyle - стиль окна
     * windowStyleEx - расширенный стиль окна
     * hParent - дочерний hwnd окна (если есть)
    */
    BOOL Create(
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
		HWND hParent);

    INT MainLoop();

	void peek_msgs(void) const;

    VOID Destroy();

protected:

    // возвращает rect с такими значенимяи, при которых окно имеет
	// заданные длину и ширину, при этом оно будет расположено по центру
	// экрана
	RECT GetAlignRect(INT width, INT height);

    BOOL RegWndClass(
		UINT cbSize,
		UINT style,
		LRESULT(WINAPI *pWndProc)(HWND, UINT, WPARAM, LPARAM),
		HINSTANCE hInstance,
		HICON hIcon,
		HCURSOR hCursor,
		LPCWSTR lpszMenuName,
		LPCWSTR lpszClassName);
};

#endif // WINDOW_H