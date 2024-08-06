#include "input_wnd_checker.h"

bool check_wnd_float_input(const HWND hwnd)
{
    if (!hwnd)
        return false;

    bool err = EXIT_SUCCESS;
    wchar_t edt_str[MAX_FLOAT_LEN + 1];

    memset(edt_str, '\0', sizeof(wchar_t) * (MAX_FLOAT_LEN + 1));
    GetWindowText(hwnd, edt_str, MAX_FLOAT_LEN + 1);

    if (!check_float_format(edt_str))
    {
        err = EXIT_FAILURE;
    }

    return err;
}

bool check_wnd_size_t_input(const HWND hwnd)
{
    if (!hwnd)
        return false;

    bool err = EXIT_SUCCESS;
    wchar_t edt_str[MAX_SIZE_T_LEN + 1];

    memset(edt_str, '\0', sizeof(wchar_t) * (MAX_SIZE_T_LEN + 1));
    GetWindowText(hwnd, edt_str, MAX_SIZE_T_LEN + 1);

    if (!check_size_t_format(edt_str))
    {
        err = EXIT_FAILURE;
    }

    return err;
}

bool check_wnd_point_input(const HWND hwnd)
{
    if (!hwnd)
        return false;

    bool err = EXIT_SUCCESS;
    wchar_t edt_str[MAX_POINT_LEN + 1];

    memset(edt_str, '\0', sizeof(wchar_t) * (MAX_POINT_LEN + 1));
    GetWindowText(hwnd, edt_str, MAX_POINT_LEN + 1);

    if (!check_point_format(edt_str))
    {
        err = EXIT_FAILURE;
    }

    return err;
}

bool get_wnd_float_input(const HWND hwnd, float *value)
{
    if (!hwnd || !value)
        return false;

    wchar_t edt_str[MAX_FLOAT_LEN + 1];

    memset(edt_str, '\0', sizeof(wchar_t) * (MAX_FLOAT_LEN + 1));
    GetWindowText(hwnd, edt_str, MAX_FLOAT_LEN + 1);
    
    return convert_str_to_float(edt_str, value);
}

bool get_wnd_size_t_input(const HWND hwnd, size_t *value)
{
    if (!hwnd || !value)
        return false;

    wchar_t edt_str[MAX_SIZE_T_LEN + 1];

    memset(edt_str, '\0', sizeof(wchar_t) * (MAX_SIZE_T_LEN + 1));
    GetWindowText(hwnd, edt_str, MAX_SIZE_T_LEN + 1);
    
    return convert_str_to_size_t(edt_str, value);
}

bool get_wnd_point_input(const HWND hwnd, pvec2 value)
{
    if (!hwnd || !value)
        return false;

    wchar_t edt_str[MAX_POINT_LEN + 1];

    memset(edt_str, '\0', sizeof(wchar_t) * (MAX_POINT_LEN + 1));
    GetWindowText(hwnd, edt_str, MAX_POINT_LEN + 1);

    return convert_str_to_point(edt_str, &value->x, &value->y);
}