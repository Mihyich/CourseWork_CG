#include <windows.h>

#include "main_wnd_proc.h"

#include "winapi_window.h"
#include "winapi_console.h"

#include "app_args.h"

INT WINAPI WinMain(
    HINSTANCE hInstance, // Дескриптор текущего приложения
    HINSTANCE hPrevInstance, // В современных системах всегда 0
    PSTR lpCmdLine, // Командная строка
    INT nCmdShow // Режим отображения окна
)
{
    UNREFERENCED_PARAMETER(hPrevInstance);

    WinApiConsole Console;
    Console.create();

    // инициализация труднодоступных переменных
    app::hInst = hInstance;
    app::lpCmdLine = lpCmdLine;

    // увеличить dpi
    if (!SetProcessDPIAware())
    {
        MessageBox(NULL, L"Качество текста будет паганым :(\nПрям таким как в этом окне...",
            L"Я должен извиниться",
            MB_OK | MB_ICONINFORMATION);
    }

    // загрузка шрифтов
    // app::Fonts.load_font(10, L"Arial", L"Arial10");

    // Создание родительского окна
    app::MainWnd.Create(
        L"Shadow CookBox 1.0.0 - Release x64 (Beta)",
        app::hInst, nCmdShow,
        MainWndProc,
        L"MainWnd",
        L"MainMenu",
        app::MinMainWndSize.x, app::MinMainWndSize.y,
        CS_HREDRAW | CS_VREDRAW,
        WS_MINIMIZEBOX | WS_SYSMENU | WS_CAPTION | WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
        0,
        NULL
    );

    // Запустить цикл обработки сообщений системы
    app::MainWnd.MainLoop();

    // Уничтожить окно
    app::MainWnd.Destroy();

    // Уничтожить шрифты
    app::Fonts.destroy();

    Console.destroy();

    return EXIT_SUCCESS;
}