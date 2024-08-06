#ifndef WINAPI_MAT_EXT_H
#define WINAPI_MAT_EXT_H

#include <windows.h>
#include <math.h>
#include "LA_sup.h"

#define WA_LCLAMP(v, l) (((v) < (l)) ? (l) : (v))

#define WA_RCLAMP(v, r) (((v) > (r)) ? (r) : (v))

#define WA_CLAMP(v, l, r) (((v) < (l)) ? (l) : (((v) > (r)) ? (r) : (v)))

#define WA_IS_LCLAMP(v, l) ((v) >= (l))

#define WA_IS_RCLAMP(v, r) ((v) <= (r))

#define WA_IS_CLAMP(v, l, r) (WA_IS_LCLAMP(v, l) && WA_IS_RCLAMP(v, r))

#define WA_INTERPOLATE(v1, v2, k) ((v1) + ((v2) - (v1)) * (k))

size_t get_digit_count_in_number(int val);

size_t get_char_count_in_number(int val);

LONG get_rect_width(const RECT &rect);

LONG get_rect_height(const RECT &rect);

void get_rect_center(const RECT &rect, POINT &center);

#endif // WINAPI_MAT_EXT_H