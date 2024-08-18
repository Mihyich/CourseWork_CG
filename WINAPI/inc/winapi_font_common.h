#ifndef WINAPI_FONT_COMMON_H
#define WINAPI_FONT_COMMON_H

#include <windows.h>
#include "winapi_font_struct.h"
#include "winapi_font.h"

void measure_text_line(const WCHAR *text, HDC hDc, HFONT hFont, SIZE &rect);


int decrease_font_height_for_fitting_width(HDC hDc, FontParam_t fpt, const WCHAR *text, int fit_width);

int decrease_font_height_for_fitting_height(HDC hDc, FontParam_t fpt, const WCHAR *text, int fit_height);

int decrease_font_height_for_fitting(HDC hDc, FontParam_t fpt, const WCHAR *text, int fit_width, int fit_height);


int increase_font_height_for_fitting_width(HDC hDc, FontParam_t fpt, const WCHAR *text, int fit_width);

int increase_font_height_for_fitting_height(HDC hDc, FontParam_t fpt, const WCHAR *text, int fit_height);

int increase_font_height_for_fitting(HDC hDc, FontParam_t fpt, const WCHAR *text, int fit_width, int fit_height);


#endif // WINAPI_FONT_COMMON_H