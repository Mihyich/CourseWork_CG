#ifndef WINAPI_BITMAP_SAVER_H
#define WINAPI_BITMAP_SAVER_H

#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>

#include "winapi_mat_ext.h"

bool gen_bitmap_header(std::wstring &file_name, BITMAP &bmp, bool inverseY = false);

BYTE* create_bitmap_bit_array(const HBITMAP hBitmap);

bool save_bitmap(const wchar_t *file_name, const HBITMAP hBitmap, bool inverseY = false);

bool save_bitmap(const wchar_t *file_name, const HDC hDc, bool inverseY = false);

#endif // WINAPI_BITMAP_SAVER_H