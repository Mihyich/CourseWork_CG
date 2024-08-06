#ifndef WINAPI_RENDER_H
#define WINAPI_RENDER_H

#include <Windows.h>
#include <iostream>
#include <cmath>
#include "winapi_double_buffer.h"
#include "winapi_pen_common.h"
#include "winapi_pen.h"
#include "winapi_brush.h"
#include "winapi_mat_ext.h"
#include "Vector2D.h"
#include "Matrix3D.h"

#define MIN_ROL_BROAD -72
#define MAX_ROL_BROAD 72
#define SCALE_ROL_BROAD 8

// для рисования draw_point
#define POINT_SIZE 6.f

class WinApiRender
{
private:
    HWND hWnd = nullptr; // дескриптор окна
    WinApiDoubleBuffer Dbuffer; // двойная буферизация

    mat3 proj; // матрица смены системы координат с центрового в winapi
    mat3 proj_inv; // обратная (winapi в центровое)

    vec2 origin; // начало координат
    int scale_rol = 0;
    float scale; // коэффициент масштабирования
    
    // перед каждым кадром (то есть в start())
    // подготовить:

    // контексты рисования
    HDC hDc;
    HDC hmemDc;
    PAINTSTRUCT ps;
    // размер области рисования
    POINT size;

public:

    // стека будет динамически изменяться при изменении масштаба в 2 раза
    bool dynamic_expanded_grid;

public:

    // Управление ====================

    void init(HWND hWnd);

    void start(void);

    void swap_buffer(void) const;

    void end(void);

    // Управление ====================
    // |    |    |    |    |    |    |
    // |    |    |    |    |    |    |
    // |    |    |    |    |    |    |
    // |    |    |    |    |    |    |
    // |    |    |    |    |    |    |
    // Рисование =====================

    void draw_background(COLORREF color) const;

    void draw_pixel(const POINT &pos, int size) const;

    void draw_pixels(const POINT *pos, size_t count, int size) const;

    void draw_pixels_simmetric(const POINT &center, const POINT &diff, int size) const;

    void draw_point(float x, float y);

    void draw_point_arr(cpvec2 arr, size_t count, COLORREF COL);

    void draw_point_arr(cpvec2 arr, const int *valid, size_t count, COLORREF COL);

    void draw_line(int x1, int y1, int x2, int y2) const;

    void draw_line(float x1, float y1, float x2, float y2) const;

    void draw_line(const POINT &p1, const POINT &p2) const;

    void draw_lines(const POINT *points, size_t count) const;

    void draw_polyline(const POINT *points, size_t count) const;

    void draw_line_strip(const POINT *points, size_t count) const;

    void draw_grid(float step);

    void draw_rect(int l, int t, int r, int b) const;

    void draw_rect(const POINT &lt, const  POINT &rb) const;

    void draw_rect(const RECT *rect) const;

    void draw_ellipse(const INT l, const INT t, const INT r, const INT b) const;

    void draw_ellipse(const POINT *lt, const POINT *rb) const;

    void draw_ellipse(const RECT *rect) const;

    void draw_ellipse(const POINT *position, const float radius_x, const float radius_y) const;

    void draw_circle(const POINT *position, const float radius) const;

    void draw_arc(const INT x1, const INT y1, const INT x2, const INT y2, const INT x3, const INT y3, const INT x4, const INT y4) const;

    void draw_arc(const RECT *rect, const POINT *s, const POINT *e) const;

    void draw_arc(const RECT *rect, float ang1, float ang2) const;

    void draw_ring(const INT l, const INT t, const INT r, const INT b) const;

    void draw_ring(const RECT *rect) const;

    void draw_ring(const POINT *lt, const POINT *rb) const;

    void draw_ring(const POINT *position, const float radius) const;

    void draw_ring(const POINT *position, const float radius_x, const float radius_y) const;

    // Рисование =====================
    // |    |    |    |    |    |    |
    // |    |    |    |    |    |    |
    // |    |    |    |    |    |    |
    // |    |    |    |    |    |    |
    // |    |    |    |    |    |    |
    // Обновление ====================

    void update_proj(void);

    void update_buffer_size(void);

    void update_size(void);

    // Обновление ====================
    // |    |    |    |    |    |    |
    // |    |    |    |    |    |    |
    // |    |    |    |    |    |    |
    // |    |    |    |    |    |    |
    // |    |    |    |    |    |    |
    // Измененение системы координат =

    void update_origin(pvec2 dt);

    void update_scale(int dt);
    
    void update_scale_via_point(int dt, cpvec2 loc_mouse_pos);

    // Измененение системы координат =
    // |    |    |    |    |    |    |
    // |    |    |    |    |    |    |
    // |    |    |    |    |    |    |
    // |    |    |    |    |    |    |
    // |    |    |    |    |    |    |
    // Перевод координат =============

    void convert_from_client_into_local(pvec2 coord) const;

    void convert_from_client_into_local(float *x, float *y) const;

    void convert_from_client_into_local(POINT *coord) const;

    void convert_from_local_into_client(pvec2 coord) const;

    void convert_from_local_into_client(float *x, float *y) const;

    void convert_from_local_into_client(POINT *coord) const;

    // Перевод координат =============
    // |    |    |    |    |    |    |
    // |    |    |    |    |    |    |
    // |    |    |    |    |    |    |
    // |    |    |    |    |    |    |
    // |    |    |    |    |    |    |
    // Сеттеры =======================

    void set_origin(float x, float y);

    void set_scale_rol(int scale_rol);

    // Сеттеры =======================
    // |    |    |    |    |    |    |
    // |    |    |    |    |    |    |
    // |    |    |    |    |    |    |
    // |    |    |    |    |    |    |
    // |    |    |    |    |    |    |
    // Геттеры =======================

    int get_width(void) const;

    int get_height(void) const;

    COLORREF get_pixel_color(int x, int y) const;

    COLORREF get_pixel_color(const POINT &coord) const;

    int get_pixel_size(void) const;

    float get_scale(void) const;

    void get_proj(pmat3 proj) const;

    void get_view(pmat3 view) const;

    HDC get_hdc(void) const;

    HBITMAP get_hMemBitmap(void) const;

    void get_wnd_size(POINT *size) const;

    // Геттеры =======================

private:

    float dyn_ex_step(float step) const;
};

#endif // WINAPI_RENDER_H