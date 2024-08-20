#include "main_wnd_proc.h"

void repos_child_wnds()
{
    RECT rect;
    LONG width;
    LONG height;
    LONG posX = 0;
    LONG posY = 0;
    LONG tmp_width = 0;
    LONG tmp_height = 0;
    WINBOOL ToolbarVisible;
    WINBOOL RenderVisible;

    GetClientRect(app::MainWnd.getHwnd(), &rect);
    width = get_rect_width(rect);
    height = get_rect_height(rect);

    if (app::ToolbarWnd.getHwnd() && app::RenderWnd.getHwnd())
    {
        ToolbarVisible = IsWindowVisible(app::ToolbarWnd.getHwnd());
        RenderVisible = IsWindowVisible(app::RenderWnd.getHwnd());

        if (ToolbarVisible)
        {
            tmp_width = RenderVisible ? app::ToolbarWidth : width;
            tmp_height = height;

            MoveWindow(
                app::ToolbarWnd.getHwnd(),
                posX, posY,
                tmp_width, tmp_height,
                TRUE
            );
        }

        posX += tmp_width;
        
        if (RenderVisible)
        {
            tmp_width = width - tmp_width;
            tmp_height = height;

            MoveWindow(
                app::RenderWnd.getHwnd(),
                posX, posY,
                tmp_width, tmp_height,
                TRUE
            );
        }
    }
}

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    MINMAXINFO* lpMinMaxInfo; // Системная структура для ограничения масштабирования род. окна

    static HMENU hMenu = nullptr;
    static UINT_PTR timerId;

    switch (uMsg)
	{

    // при создании окна
    case WM_CREATE:
    {
        // Загрузить меню
        SetMenu(hWnd, LoadMenu(app::hInst, MAKEINTRESOURCE(IDR_MAINMENU)));
        hMenu = GetMenu(hWnd);

        EnableMenuItem(hMenu, IDB_WIREFRAME_ON, MF_ENABLED);
        EnableMenuItem(hMenu, IDB_WIREFRAME_OFF, MF_DISABLED);

        EnableMenuItem(hMenu, IDB_SHOW_TOOLBAR, MF_DISABLED);
        EnableMenuItem(hMenu, IDB_HIDE_TOOLBAR, MF_ENABLED);

        EnableMenuItem(hMenu, IDB_SHOW_RENDERWND, MF_DISABLED);
        EnableMenuItem(hMenu, IDB_HIDE_RENDERWND, MF_ENABLED);

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
            WS_CHILD | WS_VISIBLE,
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
            case IDM_NEW_WINDOW:
            {
                return EXIT_SUCCESS;
            }

            case IDM_TAKE_FOTO:
            {
                return EXIT_SUCCESS;
            }

            case IDM_SCAN_SHADOW:
            {
                return EXIT_SUCCESS;
            }

            case IDM_LAUNCH_TESTING:
            {
                return EXIT_SUCCESS;
            }
            
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
                EnableMenuItem(hMenu, IDB_WIREFRAME_ON, MF_DISABLED);
                EnableMenuItem(hMenu, IDB_WIREFRAME_OFF, MF_ENABLED);
                SendMessage(app::RenderWnd.getHwnd(), WM_SET_WIREFRAME, (WPARAM)true, 0);
                return EXIT_SUCCESS;
            }

            case IDB_WIREFRAME_OFF:
            {
                EnableMenuItem(hMenu, IDB_WIREFRAME_ON, MF_ENABLED);
                EnableMenuItem(hMenu, IDB_WIREFRAME_OFF, MF_DISABLED);
                SendMessage(app::RenderWnd.getHwnd(), WM_SET_WIREFRAME, (WPARAM)false, 0);
                return EXIT_SUCCESS;
            }

            case IDB_SHOW_TOOLBAR:
            {
                EnableMenuItem(hMenu, IDB_SHOW_TOOLBAR, MF_DISABLED);
                EnableMenuItem(hMenu, IDB_HIDE_TOOLBAR, MF_ENABLED);
                ShowWindow(app::ToolbarWnd.getHwnd(), SW_SHOW);
                repos_child_wnds();
                return EXIT_SUCCESS;
            }

            case IDB_HIDE_TOOLBAR:
            {
                EnableMenuItem(hMenu, IDB_SHOW_TOOLBAR, MF_ENABLED);
                EnableMenuItem(hMenu, IDB_HIDE_TOOLBAR, MF_DISABLED);
                ShowWindow(app::ToolbarWnd.getHwnd(), SW_HIDE);
                repos_child_wnds();
                return EXIT_SUCCESS;
            }

            case IDB_SHOW_RENDERWND:
            {
                EnableMenuItem(hMenu, IDB_SHOW_RENDERWND, MF_DISABLED);
                EnableMenuItem(hMenu, IDB_HIDE_RENDERWND, MF_ENABLED);
                ShowWindow(app::RenderWnd.getHwnd(), SW_SHOW);
                repos_child_wnds();
                return EXIT_SUCCESS;
            }
            
            case IDB_HIDE_RENDERWND:
            {
                EnableMenuItem(hMenu, IDB_SHOW_RENDERWND, MF_ENABLED);
                EnableMenuItem(hMenu, IDB_HIDE_RENDERWND, MF_DISABLED);
                ShowWindow(app::RenderWnd.getHwnd(), SW_HIDE);
                repos_child_wnds();
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

    case WM_DESTROY:
    {
        KillTimer(hWnd, timerId);
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    // Прочие необработанные событие делает винда сама
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);

	}
}