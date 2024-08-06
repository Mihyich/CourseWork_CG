#ifndef WINAPI_FRAME_BUFFER_H
#define WINAPI_FRAME_BUFFER_H

#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "winapi_mat_ext.h"
#include "winapi_color_common.h"

class WinApiFrameBuffer
{
public:
    WinApiFrameBuffer();

    WinApiFrameBuffer(HDC hDc);

    ~WinApiFrameBuffer();

private:
    void free_pixels_data(void);

    bool malloc_pixels_data(int width, int height);

public:

    bool create_pixel_matrix_from_hdc(void);

    bool create_pixel_matrix_from_hbitmap(const HBITMAP hBitmap);

    void copy_mask(WinApiFrameBuffer &fb, COLORREF color);

    void copy_into_hdc(const HDC hDc) const;

    // сохранить созданную пиксельную bitmap'у
    bool save(const wchar_t *file_name) const;

    void set_hdc(HDC hDc);

    int get_col_count(void) const;

    int get_row_count(void) const;

    COLORREF* operator[](int index);

private:
    HDC hDc;

    COLORREF** pixels;
    COLORREF* data;

    int width;
    int height;
};

#endif // WINAPI_FRAME_BUFFER_H