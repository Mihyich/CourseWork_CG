#ifndef WINAPI_CHAR_CONVERTER_H
#define WINAPI_CHAR_CONVERTER_H

#include <Windows.h>
#include <iostream>
#include <string.h>

size_t char_to_wchar(const char *const source, wchar_t **dest);

size_t char_to_wchar(const std::string *const source, std::wstring *dest);

size_t wchar_to_char(const wchar_t *const source, char **dest);

size_t wchar_to_char(const std::wstring *const source, std::string *dest);

#endif // WINAPI_CHAR_CONVERTER_H