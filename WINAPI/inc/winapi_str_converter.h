#ifndef WINAPI_STR_CONVERTER_H
#define WINAPI_STR_CONVERTER_H

#include <windows.h>
#include <string>

void winapi_convert_str_to_wstr(const std::string &str, std::wstring &wstr);

void winapi_convert_wstr_to_str(const std::wstring &wstr, std::string &str);

#endif // WINAPI_STR_CONVERTER_H