#ifndef WINAPI_WINDOW_H
#define WINAPI_WINDOW_H

#define WIN32_LEAN_AND_MEAN 1 // Урезанный windows.h

#include <Windows.h>
#include <string>

#define WINDOW_NOT_CREATED -1 // Значение флага window_is_created при не созданном окне
#define WINDOW_CREATED 0      // Код возврата при успешном выполении функции генерации окна
#define ERR_WINDOW_COPY 1     // Код возврата при дуюлирующей генерации окна
#define ERR_WNDCLASS_COPY 2   // Код возврата при дублирующей регистрации класса стилей окна
#define ERR_WNDCLASS_GEN 3    // Код возврата при неудачной регистрации класса стилей окна
#define ERR_ADJWNDRECT 4      // Код возврата при неудачном выполнении функции AdjustWindowRectEx
#define ERR_WINDOW_GEN 5      // Код возврата при неудачном созданиие окна
#define ERR_WNDSHOW 6         // Код возврата при неудачном выполнении функции ShowWindow

#define MAINLOOP_SUCCESS_STOP 0 // Код возврата при успешной остановке бесконечного цикла обработки событий окна
#define MAINLOOP_NOT_STARTED 1  // Код возрата при неудачной попытке запустить бесконечный цилк обработки окна

#define SUCCESS_WNDDESTROY 0 // Код возврата при удачном уничтожении окна
#define ERR_WNDDESTROY 1     // Код возврата при неудочной попытке уничтожить окно
#define ERR_UNREG_CLASS 2    // Код возврата при неудачной попытке удалить зарегистрированный класс окна
#define ERR_ACCELDESTROY 3   // Код возврата при неудочной попытки удалить таблицу акселераторов

class WinApiWindow
{
protected:
	std::wstring ClassName;     // Имя класса окна
	WNDCLASSEX wcx; // Класс окна (описывает как выглядит окно)

	HINSTANCE hInstance = NULL;

	HWND hWnd = NULL; // Дескриптор окна (ручка для обращения к окну)
	HACCEL hAccel = NULL;       // Акселеряторы (комбинации клавиш)

	DWORD error = ERROR_SUCCESS; // Переменная для получения кода о последней случившейся ошибке
	RECT rect = {0, 0, 0, 0}; // Координаты и габариты окна

public:
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

	HWND getHwnd();

	INT getWidth();

	INT getHeight();

	DWORD get_last_error();

protected:
	VOID getAlignRect(RECT &dist_rect, INT width, INT height);

	BOOL CreateWndProcess(
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

    BOOL RegWndClass(
		UINT cbSize,
		UINT style,
		LRESULT(WINAPI *pWndProc)(HWND, UINT, WPARAM, LPARAM),
		HINSTANCE hInstance,
		HICON hIcon,
		HCURSOR hCursor,
		HBRUSH hbrBackground,
		LPCWSTR lpszMenuName,
		LPCWSTR lpszClassName,
		HICON hIconSm);

	VOID reset_and_free_data();
};

#endif // WINDOW_H