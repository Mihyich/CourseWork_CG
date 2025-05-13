#include "winapi_str_converter.h"

void winapi_convert_str_to_wstr(const std::string &str, std::wstring &wstr)
{
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
    wstr.resize(size_needed);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], size_needed);
}

void winapi_convert_wstr_to_str(const std::wstring &wstr, std::string &str)
{
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
    str.resize(size_needed);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], size_needed, NULL, NULL);
}