#ifndef FORMATER_H
#define FORMATER_H

#include <iostream>
#include <regex>
#include <string>
#include <list>

// +/- ... {7} . {6}
#define MAX_FLOAT_LEN 15

// {20}
#define MAX_SIZE_T_LEN 20

// два float числа и один символ табуляции между ними
#define MAX_POINT_LEN MAX_FLOAT_LEN * 2 + 1


void token_worlds(const wchar_t *str, std::list<std::wstring> *tokens);

bool check_size_t_format(const wchar_t *str);

bool check_float_format(const wchar_t *str);

bool check_point_format(const wchar_t *str);

bool convert_str_to_size_t(const wchar_t *str, size_t *value);

bool convert_str_to_float(const wchar_t *str, float *value);

bool convert_str_to_point(const wchar_t *str, float *x, float *y);

bool is_equal_str_points(const wchar_t *str1, const wchar_t *str2);

#endif // FORMATER_H