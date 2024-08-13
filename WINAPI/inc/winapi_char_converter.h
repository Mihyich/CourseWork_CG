#ifndef WINAPI_CHAR_CONVERTER_H
#define WINAPI_CHAR_CONVERTER_H

#include <Windows.h>
#include <iostream>
#include <string.h>

/// @brief Конвертировать char в wchar_t
/// Гарантируется, что длина результирующей строки будет натуральным числом
/// @param source Исходная строка
/// @param dest Результирующая строка
/// @return Длина результирующей строки, с учетом символа окончания
size_t char_to_wchar(const char *const source, wchar_t **dest);

/// @brief Конвертировать char в wchar_t
/// Гарантируется, что длина результирующей строки будет натуральным числом
/// @param source Исходная строка
/// @param dest Результирующая строка
/// @return Длина результирующей строки, с учетом символа окончания
size_t char_to_wchar(const std::string *const source, std::wstring *dest);

/// @brief Конвертировать wchar_t в char
/// Гарантируется, что длина результирующей строки будет натуральным числом
/// @param source Исходная строка
/// @param dest Результирующая строка
/// @return Длина результирующей строки, с учетом символа окончания
size_t wchar_to_char(const wchar_t *const source, char **dest);

/// @brief Конвертировать wchar_t в char
/// Гарантируется, что длина результирующей строки будет натуральным числом
/// @param source Исходная строка
/// @param dest Результирующая строка
/// @return Длина результирующей строки, с учетом символа окончания
size_t wchar_to_char(const std::wstring *const source, std::string *dest);

#endif // WINAPI_CHAR_CONVERTER_H