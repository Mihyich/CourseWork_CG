#ifndef INPUT_DATA_CHECK_H
#define INPUT_DATA_CHECK_H

#include <string>

#include "val_args.h"
#include "app_args.h"
#include "input_wnd_checker.h"
#include "winapi_str_converter.h"

#define FORMULA_LENGHT 255

bool check_input_data(
    const HWND XLimitInputHwnd, const HWND ZLimitInputHwnd,
    const HWND XStepInputHwnd, const HWND ZStepInputHWND,
    std::wstring &err_msg
);

#endif // INPUT_DATA_CHECK_H