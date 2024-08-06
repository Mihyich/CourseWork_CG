#ifndef WINAPI_COLOR_COMMON_H
#define WINAPI_COLOR_COMMON_H

#include <windows.h>
#include <math.h>

COLORREF color_interpolation(COLORREF c1, COLORREF c2, float k);

COLORREF color_reverse(COLORREF color);

void reverse_color(COLORREF &color);

void reverse_color_str(COLORREF *sc, COLORREF *ec);

#endif // WINAPI_COLOR_COMMON_H