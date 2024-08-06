#include "drawarea_wnd_poc.h"

void update_coord_info_data(cpvec2 pos)
{
    wchar_t msg[MAX_COORD_MSG_LEN + 1];
    wchar_t buffer[MAX_COORD_VALUE_LEN + 1];
    int lenght = 0;

    memset(msg, '\0', (MAX_COORD_MSG_LEN + 1) * sizeof(wchar_t));
    memset(buffer, '\0', (MAX_COORD_VALUE_LEN + 1) * sizeof(wchar_t));
    lenght = _snwprintf_s(buffer, MAX_COORD_VALUE_LEN + 1, L"%.3f", pos->x);

    if (lenght > 0)
    {
        wcscat_s(msg, MAX_COORD_MSG_LEN + 1, L"x: ");
        wcscat_s(msg, MAX_COORD_MSG_LEN + 1, buffer);
        SendMessage(app::coordX_info_hwnd, WM_SETTEXT, 0, (LPARAM)msg);
    }

    memset(msg, '\0', (MAX_COORD_MSG_LEN + 1) * sizeof(wchar_t));
    memset(buffer, '\0', (MAX_COORD_VALUE_LEN + 1) * sizeof(wchar_t));
    lenght = _snwprintf_s(buffer, MAX_COORD_VALUE_LEN + 1, L"%.3f", pos->y);

    if (lenght > 0)
    {
        wcscat_s(msg, MAX_COORD_MSG_LEN + 1, L"y: ");
        wcscat_s(msg, MAX_COORD_MSG_LEN + 1, buffer);
        SendMessage(app::coordY_info_hwnd, WM_SETTEXT, 0, (LPARAM)msg);
    }
}

void update_scale_info_data(float value)
{
    wchar_t msg[MAX_SCALE_MSG_LEN + 1];
    wchar_t buffer[MAX_SCALE_VALUE_LEN + 1];
    int lenght = 0;

    memset(msg, '\0', (MAX_SCALE_MSG_LEN + 1) * sizeof(wchar_t));
    memset(buffer, '\0', (MAX_SCALE_VALUE_LEN + 1) * sizeof(wchar_t));
    lenght = _snwprintf_s(buffer, MAX_SCALE_VALUE_LEN + 1, L"%.3f", value);

    if (lenght > 0)
    {
        wcscat_s(msg, MAX_SCALE_MSG_LEN + 1, L"scale: ");
        wcscat_s(msg, MAX_SCALE_MSG_LEN + 1, buffer);
        SendMessage(app::scale_info_hwnd, WM_SETTEXT, 0, (LPARAM)msg);
    }
}

LRESULT CALLBACK DrawAreaWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static WinApiRender Render;

    static WinApiMouse mouse;
    static vec2 tracking_coord = { 0.f, 0.f }; // переведеная в систему координат позиция мыши
    static vec2 delta_coord = { 0.f, 0.f }; // переведеная в систему координат дельта позиций мыши

    static bool first_draw = false;

    switch(uMsg)
    {
        case WM_CREATE:
        {            
            Render.init(hWnd);
            mouse.init(hWnd);

            return EXIT_SUCCESS;
        }

        case WM_LBUTTONDOWN:
        {
            mouse.l_button_down();
            return EXIT_SUCCESS;
        }

        case WM_LBUTTONUP:
        {
            mouse.l_button_up();           
            return EXIT_SUCCESS;
        }

        case WM_MOUSEMOVE:
        {
            // обновить позицию мыши
            mouse.move(lParam);
            tracking_coord.x = (float)mouse.l_cur_pos.x;
            tracking_coord.y = (float)mouse.l_cur_pos.y;
            Render.convert_from_local_into_client(&tracking_coord);
            // повернуть поверхность
            if (mouse.l_tracking)
            {
                 delta_coord.x = mouse.l_delta_pos.x;
                delta_coord.y = -mouse.l_delta_pos.y;
                
                vals::x_angle += delta_coord.y;
                vals::y_angle -= delta_coord.x;

                if (first_draw) vals::need_resolve = true;
                make_wnd_redraw(hWnd);
            }
            // Вывод инфы
            update_coord_info_data(&tracking_coord);

            return EXIT_SUCCESS;
        }

        case WM_MOUSEWHEEL:
        {
            // сделать прокрутку
            mouse.wheel(wParam);
            Render.update_scale(mouse.delta_wheel);
            // Вывод инфы
            update_coord_info_data(&tracking_coord);
            update_scale_info_data(Render.get_scale());
            // насильно перерисовать это окно
            if (first_draw) vals::need_resolve = true;
            make_wnd_redraw(hWnd);

            return EXIT_SUCCESS;
        }

        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {

            // сбросить перемещение 
            case ID_RND_CENTER:
            {
                Render.set_origin(0.f, 0.f);
                if (first_draw) vals::need_resolve = true;
                make_wnd_redraw(hWnd);
                return EXIT_SUCCESS;
            }

            // сбросить масштаб
            case ID_RND_SCALE:
            {
                Render.set_scale_rol(0);
                SendMessage(app::scale_info_hwnd, WM_SETTEXT, 0, (LPARAM)L"Scale: 1.000");
                if (first_draw) vals::need_resolve = true;
                make_wnd_redraw(hWnd);
                return EXIT_SUCCESS;
            }

            // Сбросить перемещение и масштаб
            case ID_RND_ALL:
            {
                Render.set_origin(0.f, 0.f);
                Render.set_scale_rol(0);
                SendMessage(app::scale_info_hwnd, WM_SETTEXT, 0, (LPARAM)L"Scale: 1.000");
                if (first_draw) vals::need_resolve = true;
                make_wnd_redraw(hWnd);
                return EXIT_SUCCESS;
            }


            default:
                return DefWindowProc(hWnd, uMsg, wParam, lParam);
            }
        }

        case WM_SIZE:
        {
            Render.update_size();
            if (first_draw) vals::need_resolve = true;
            return EXIT_SUCCESS;
        }

        case  WM_PAINT:
        {
            // Подготовиться к рисованию
            Render.start();

            // залить фон
            Render.draw_background(RGB(255, 255, 255));

            if (vals::need_resolve)
            {
                vals::need_resolve = false;
                first_draw = true;

                drawSurface(Render, &vals::x_range, &vals::z_range, vals::x_step, vals::z_step, vals::formula, vals::surface_color);
            }
            else
            {
                Render.draw_grid(100.f);
            }

            // Скопировать кадр в окно
            Render.swap_buffer();

            // Закончить рисование
            Render.end();

            // (づ￣ 3￣)づ "Вьуюх!!!"
            return EXIT_SUCCESS;
        }

        case WM_ERASEBKGND:
        {
            // ничего не надо стирать, поэтому
            // я запрещаю это системе }:ю
            return EXIT_SUCCESS;
        }

        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}