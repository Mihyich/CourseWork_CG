#ifndef WINAPI_MOUSE_H
#define WINAPI_MOUSE_H

#include <Windows.h>

#define SMALL_DELTA_DIST 3

class WinApiMouse
{
public:
    // относительно клиентской области окна
    POINT l_last_pos = { 0, 0 };
    POINT l_cur_pos = { 0, 0 };
    POINT l_delta_pos = { 0, 0 };

    POINT r_last_pos = { 0, 0 };
    POINT r_cur_pos = { 0, 0 };
    POINT r_delta_pos = { 0, 0 };

    // последняя дельта прокрутка
    int delta_wheel = 0;

    // зажата левая кнопка мыши
    bool l_tracking = false;

    // зажата правая кнопка мыши
    bool r_tracking = false;

    void init(HWND hWnd);

    void l_button_down();

    void l_button_up();

    void r_button_down();

    void r_button_up();

    void move();

    void wheel(WPARAM wParam);

    void update_pos();

    bool is_l_delta_small_enough(void);

    bool is_r_delta_small_enough(void);

private:

    bool delta_pos_small_enough(POINT *delta);

    HWND hWnd = nullptr;
};

#endif // WINAPI_MOUSE_H