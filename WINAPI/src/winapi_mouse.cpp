#include "winapi_mouse.h"

void WinApiMouse::init(HWND hWnd)
{
    this->hWnd = hWnd;
}

void WinApiMouse::l_button_down()
{
    l_last_pos = l_cur_pos;
    l_delta_pos.x = l_delta_pos.y = 0.f;

    GetCursorPos(&this->l_cur_pos);
    ScreenToClient(this->hWnd, &this->l_cur_pos);

    l_tracking = true;
}

void WinApiMouse::l_button_up()
{
    l_tracking = false;
}

void WinApiMouse::r_button_down()
{
    r_last_pos = r_cur_pos;
    r_delta_pos.x = r_delta_pos.y = 0.f;

    GetCursorPos(&this->r_cur_pos);
    ScreenToClient(this->hWnd, &this->r_cur_pos);

    r_tracking = true;
}

void WinApiMouse::r_button_up()
{
    r_tracking = false;
}

void WinApiMouse::move(LPARAM lParam)
{
    l_last_pos = l_cur_pos;

    l_cur_pos.x = LOWORD(lParam);
    l_cur_pos.y = HIWORD(lParam);

    l_delta_pos.x = l_cur_pos.x - l_last_pos.x;
    l_delta_pos.y = l_cur_pos.y - l_last_pos.y;
}

void WinApiMouse::wheel(WPARAM wParam)
{
    this->delta_wheel = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
}

void WinApiMouse::update_pos()
{
    l_last_pos = l_cur_pos;
    r_last_pos = r_cur_pos;

    GetCursorPos(&this->l_cur_pos);
    ScreenToClient(this->hWnd, &this->l_cur_pos);
    r_cur_pos = l_cur_pos;

    l_delta_pos.x = l_cur_pos.x - l_last_pos.x;
    l_delta_pos.y = l_cur_pos.y - l_last_pos.y;

    r_delta_pos.x = r_cur_pos.x - r_last_pos.x;
    r_delta_pos.y = r_cur_pos.y - r_last_pos.y;
}

bool WinApiMouse::is_l_delta_small_enough(void)
{
    return delta_pos_small_enough(&this->l_delta_pos);
}

bool WinApiMouse::is_r_delta_small_enough(void)
{
    return delta_pos_small_enough(&this->r_delta_pos);
}

bool WinApiMouse::delta_pos_small_enough(POINT *delta)
{
    int dx = delta->x < 0 ? -delta->x : delta->x;
    int dy = delta->y < 0 ? -delta->y : delta->y;

    return dx <= SMALL_DELTA_DIST && dy <= SMALL_DELTA_DIST;
}