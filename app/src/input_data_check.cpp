#include "input_data_check.h"

bool check_input_data(
    const HWND XLimitInputHwnd, const HWND ZLimitInputHwnd,
    const HWND XStepInputHwnd, const HWND ZStepInputHWND,
    std::wstring &err_msg
)
{
    struct msg 
    {
        bool rs = true;
        std::wstring err;
    };

    bool res = true;
    std::vector<msg> logs;

    logs.resize(4);

    wchar_t XLimitInput[MAX_POINT_LEN + 1];
    wchar_t ZLimitInput[MAX_POINT_LEN + 1];
    wchar_t XStepInput[MAX_FLOAT_LEN + 1];
    wchar_t ZStepInput[MAX_FLOAT_LEN + 1];

    memset(XLimitInput, '\0', sizeof(wchar_t) * (MAX_POINT_LEN + 1));
    memset(ZLimitInput, '\0', sizeof(wchar_t) * (MAX_POINT_LEN + 1));
    memset(XStepInput, '\0', sizeof(wchar_t) * (MAX_FLOAT_LEN + 1));
    memset(ZStepInput, '\0', sizeof(wchar_t) * (MAX_FLOAT_LEN + 1));

    GetWindowText(XLimitInputHwnd, XLimitInput, MAX_POINT_LEN + 1);
    GetWindowText(ZLimitInputHwnd, ZLimitInput, MAX_POINT_LEN + 1);
    GetWindowText(XStepInputHwnd, XStepInput, MAX_FLOAT_LEN + 1);
    GetWindowText(ZStepInputHWND, ZStepInput, MAX_FLOAT_LEN + 1);

    if (!check_point_format(XLimitInput))
    {
        logs[0].rs = false;
        logs[0].err = L"Диапазон X имеет некорректный формат\n";
    }

    if (!check_point_format(ZLimitInput))
    {
        logs[1].rs = false;
        logs[1].err = L"Диапазон Z имеет некорректный формат\n";
    }

    if (!check_float_format(XStepInput))
    {
        logs[2].rs = false;
        logs[2].err = L"Шаг X имеет некорректный формат\n";
    }

    if (!check_float_format(ZStepInput))
    {
        logs[3].rs = false;
        logs[3].err = L"Шаг Z имеет некорректный формат\n";
    }

    err_msg.clear();
    for (const auto &log : logs)
    {
        if (!log.rs)
        {
            err_msg += log.err;
            res = false;
        }
    } 

    return res;
}