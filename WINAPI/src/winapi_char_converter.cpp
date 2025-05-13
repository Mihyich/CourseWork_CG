#include "winapi_char_converter.h"

size_t char_to_wchar(const char *const source, wchar_t **dest)
{
    // Определение размера буфера для строки wchar_t
    size_t wstr_length = 0;
    mbstowcs_s(&wstr_length, NULL, 0, source, 0);

    // Создание буфера для строки wchar_t
    *dest = new wchar_t[wstr_length];

    // Преобразование строки из char в wchar_t
    mbstowcs_s(NULL, *dest, wstr_length, source, wstr_length);

    return wstr_length;
}

size_t char_to_wchar(const std::string *const source, std::wstring *dest)
{
    // Определение размера буфера для строки wchar_t
    size_t wstr_length = 0;
    mbstowcs_s(&wstr_length, NULL, 0, source->c_str(), 0);

    // Создание буфера для строки wchar_t
    dest->resize(wstr_length);

    // Преобразование строки из char в wchar_t
    mbstowcs_s(NULL, &(*dest)[0], wstr_length, source->c_str(), wstr_length);

    return wstr_length;
}

size_t wchar_to_char(const wchar_t *const source, char **dest)
{
    int str_length = WideCharToMultiByte(CP_UTF8, 0, source, -1, nullptr, 0, nullptr, nullptr);
    *dest = new char[str_length];
    WideCharToMultiByte(CP_UTF8, 0, source, -1, *dest, str_length, nullptr, nullptr);
    return str_length;
}

size_t wchar_to_char(const std::wstring *const source, std::string *dest)
{
    // Определение размера буфера для строки char
    size_t str_length = 0;
    wcstombs_s(&str_length, NULL, 0, source->c_str(), 0);

    // Создание буфера для строки char
    dest->resize(str_length);

    // Преобразование строки из wchar_t в char
    wcstombs_s(NULL, &(*dest)[0], str_length, source->c_str(), str_length);

    return str_length;
}
