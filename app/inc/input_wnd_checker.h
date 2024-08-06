#ifndef INPUT_WND_CHECKER_H
#define INPUT_WND_CHECKER_H

#include <Windows.h>
#include <string>

#include "formater.h"
#include "Vector2D.h"

// чекеры

bool check_wnd_float_input(const HWND hwnd);

bool check_wnd_size_t_input(const HWND hwnd);

bool check_wnd_point_input(const HWND hwnd);

// получатели

bool get_wnd_float_input(const HWND hwnd, float *value);

bool get_wnd_size_t_input(const HWND hwnd, size_t *value);

bool get_wnd_point_input(const HWND hwnd, pvec2 value);

#endif // INPUT_WND_CHECKER_H