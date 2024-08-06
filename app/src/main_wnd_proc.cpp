#include "main_wnd_proc.h"

void repos_child_wnds()
{
    RECT rect;
    LONG width;
    LONG height;

    GetClientRect(app::MainWnd.hWnd, &rect);
    width = get_rect_width(rect);
    height = get_rect_height(rect);

    ShowWindow(app::DrawAreaInfoWnd.hWnd, SW_SHOW);

    MoveWindow(
        app::ToolbarWnd.hWnd,
        0, 0,
        app::ToolbarWidth, height,
        TRUE
    );

    MoveWindow(
        app::DrawAreaWnd.hWnd,
        app::ToolbarWidth, 0,
        width - app::ToolbarWidth, height - app::DrawAreaInfoHeight,
        TRUE
    );

    MoveWindow(
        app::DrawAreaInfoWnd.hWnd,
        app::ToolbarWidth, height - app::DrawAreaInfoHeight,
        width - app::ToolbarWidth, app::DrawAreaInfoHeight,
        TRUE
    );
}

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // Про главное окно
    MINMAXINFO* lpMinMaxInfo; // Системная структура для ограничения масштабирования род. окна
    int rs_int; // вспомогательная переменная

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

        // Создать окно DrawArea
        app::DrawAreaWnd.Create(
            nullptr, app::hInst, SW_SHOWNORMAL,
            DrawAreaWndProc, L"DrawArea", nullptr,
            0, 0,
            CS_HREDRAW | CS_VREDRAW,
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            0,
            hWnd
        );

        // Создать окно информации о графическом окне
        app::DrawAreaInfoWnd.Create(
            nullptr, app::hInst, SW_SHOWNORMAL,
            DrawAreaInfoWndProc, L"DrawAreaInfo", nullptr,
            0, 0,
            CS_HREDRAW | CS_VREDRAW,
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            0,
            hWnd
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

    // Обработки нажатий вообще всего чего можно
    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        
        // Меню о авторе
        case ID_FILE_AUTOR:
        {
            MessageBox(
                hWnd, AUTOR_CAPTION,
                AUTOR, MB_OK
            );

            return EXIT_SUCCESS;
        }

        // Меню о задаче
        case ID_FILE_TASK:
        {
            MessageBox(
                hWnd, TASK_CAPTION,
                TASK_NOMER, MB_OK
            );

            return EXIT_SUCCESS;
        }

        // Меню выход
        case ID_FILE_EXIT:
        {
            PostQuitMessage(0); // это вызовет WM_DESTROY у всех-всех окон
            return EXIT_SUCCESS;
        }

        // сбросить перемещение 
        case ID_RND_CENTER:
        {
            SendMessage(app::DrawAreaWnd.hWnd, WM_COMMAND, (WPARAM)ID_RND_CENTER, 0);
            return EXIT_SUCCESS;
        }

        // сбросить масштаб
        case ID_RND_SCALE:
        {
            SendMessage(app::DrawAreaWnd.hWnd, WM_COMMAND, (WPARAM)ID_RND_SCALE, 0);
            return EXIT_SUCCESS;
        }

        // Сбросить перемещение и масштаб
        case ID_RND_ALL:
        {
            SendMessage(app::DrawAreaWnd.hWnd, WM_COMMAND, (WPARAM)ID_RND_ALL, 0);
            return EXIT_SUCCESS;
        }

        case ID_INFO_INPUT:
        {
            MessageBox(
                hWnd, INSTRUCTION_CAPTION_INPUT,
                INSTRUCTION_HEADER, MB_OK
            );

            return EXIT_SUCCESS;
        }

        case ID_INFO_FORMAT:
        {
            MessageBox(
                hWnd, INSTRUCTION_CAPTION_FORMAT,
                INSTRUCTION_HEADER, MB_OK
            );

            return EXIT_SUCCESS;
        }

        case ID_INFO_COORD_SYSTEM:
        {
            MessageBox(
                hWnd, INSTRUCTION_CAPTION_COORD_SYSTEM,
                INSTRUCTION_HEADER, MB_OK
            );
            return EXIT_SUCCESS;
        }

        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }
    }

    // При нажатии на крестик
    case WM_CLOSE:
    {
        rs_int = MessageBox(
            hWnd,
            L"Вы уверены, что хотите закрыть приложение?", L"Выход",
            MB_YESNO | MB_ICONQUESTION
        );

        // Если пользователь нажал "Да", то закрываем окно
        if (rs_int == IDYES)
            PostQuitMessage(0); // это вызовет WM_DESTROY у всех-всех окон

        return EXIT_SUCCESS;
    }

    // Прочие необработанные событие делает винда сама
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);

	}
}