#include "main_wnd_proc.h"

void repos_child_wnds()
{
    RECT rect;
    LONG width;
    LONG height;

    GetClientRect(app::MainWnd.getHwnd(), &rect);
    width = get_rect_width(rect);
    height = get_rect_height(rect);

    if (app::ToolbarWnd.getHwnd())
    {
        MoveWindow(
            app::ToolbarWnd.getHwnd(),
            0, 0,
            app::ToolbarWidth, height,
            TRUE
        );
    }

    if (app::RenderWnd.getHwnd())
    {
        MoveWindow(
            app::RenderWnd.getHwnd(),
            app::ToolbarWidth, 0,
            width - app::ToolbarWidth, height,
            TRUE
        );
    }
}

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    MINMAXINFO* lpMinMaxInfo; // Системная структура для ограничения масштабирования род. окна

    static UINT_PTR timerId;

    switch (uMsg)
	{

    // при создании окна
    case WM_CREATE:
    {
        // Загрузить меню
        SetMenu(hWnd, LoadMenu(app::hInst, MAKEINTRESOURCE(IDR_MAINMENU)));

        // загрузка пиктограммы окна
        SendMessage(
            hWnd, WM_SETICON, ICON_SMALL,
            (LPARAM)LoadIcon(app::hInst, MAKEINTRESOURCE(IDI_ICON_APP_32))
        );

        // Создать окно Toolbar
        app::ToolbarWnd.Create(
            nullptr, app::hInst, SW_SHOWNORMAL,
            ToolbarWndProc, L"Toolbar", nullptr,
            0, 0,
            CS_HREDRAW | CS_VREDRAW,
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            0,
            hWnd
        );

        // Создание рендер окно
        app::RenderWnd.Create(
            nullptr, app::hInst, SW_SHOWNORMAL,
            RenderWndProc, L"GLRenderer", nullptr,
            0, 0,
            CS_VREDRAW | CS_HREDRAW | CS_OWNDC,
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            0,
            hWnd
        );

        // Создание контекнста OpenGL
        if (app::RenderWnd.CreateOpenGLContext() != OPENGL_CONTEXT_CREATED)
        {
            MessageBox(NULL, L"Не удалось создать контекст OpenGL",
                L"OpenGL",
                MB_OK | MB_ICONERROR);
        }

        SendMessage(app::RenderWnd.getHwnd(), WM_INIT_GL_OPTIONS, 0, 0);

        timerId = SetTimer(hWnd, 1, 41, NULL);

        return EXIT_SUCCESS;
    }

    case WM_SIZE:
    {
        repos_child_wnds();
        return EXIT_SUCCESS;
    }

    // вызывается при масштабировании окна
    case WM_GETMINMAXINFO:
    {
        // Установка минимального размера окна (система сама поймет когда прекратить масштабирование окна)
        lpMinMaxInfo = (MINMAXINFO*)lParam;
        lpMinMaxInfo->ptMinTrackSize.x = app::MinMainWndSize.x;
        lpMinMaxInfo->ptMinTrackSize.y = app::MinMainWndSize.y;
        return EXIT_SUCCESS;
    }

    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        
            case IDM_EXIT:
            {
                int res = MessageBox(
                    hWnd, L"Вы уверены, что хотите закрыть приложение?",
                    L"Выход", MB_YESNO | MB_ICONQUESTION
                );

                if (res == IDYES)
                    PostQuitMessage(0);

                return EXIT_SUCCESS;
            }

            case IDB_LOAD_MODEL:
            {
                DialogBox(app::hInst, MAKEINTRESOURCE(IDD_MODEL_LOADER), hWnd, ModelLoaderDlgProc);
                return EXIT_SUCCESS;
            }

            case IDB_WIREFRAME_ON:
            {
                SendMessage(app::RenderWnd.getHwnd(), WM_SET_WIREFRAME, (WPARAM)true, 0);
                return EXIT_SUCCESS;
            }

            case IDB_WIREFRAME_OFF:
            {
                SendMessage(app::RenderWnd.getHwnd(), WM_SET_WIREFRAME, (WPARAM)false, 0);
                return EXIT_SUCCESS;
            }

            case IDM_AUTOR:
            {
                MessageBox(
                    hWnd, AUTOR_TEXT,
                    AUTOR_CAPTION, MB_OK
                );

                return EXIT_SUCCESS;
            }

            default:
                return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }
    }

    case WM_TIMER:
    {
        InvalidateRect(app::RenderWnd.getHwnd(), NULL, FALSE);
        UpdateWindow(app::RenderWnd.getHwnd());
        return EXIT_SUCCESS;
    }

    // При нажатии на крестик
    case WM_CLOSE:
    {
        SendMessage(hWnd, WM_COMMAND, MAKEWPARAM(IDM_EXIT, 0), 0);
        return EXIT_SUCCESS;
    }

    // Прочие необработанные событие делает винда сама
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);

	}
}