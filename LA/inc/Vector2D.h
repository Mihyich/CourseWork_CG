#ifndef VECTOR2D_H
#define VECTOR2D_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include "LA_sup.h"

#define dot2(x1, y1, x2, y2) ((x1) * (x2) + (y1) * (y2))
#define det2(x1, y1, x2, y2) ((x1) * (y2) - (x2) * (y1))

typedef struct Vector2D vec2;
typedef vec2 *pvec2;
typedef const vec2 cvec2;
typedef cvec2 *cpvec2;

struct Vector2D
{
    float x;
    float y;
};

void __cdecl vec2_set(pvec2 v, float x, float y);

void __cdecl vec2_invert(pvec2 v);

void __cdecl vec2_invert_res(cpvec2 v, pvec2 res);

void __cdecl vec2_scale(pvec2 v, float s);

void __cdecl vec2_divide(pvec2 v, float d);

void __cdecl vec2_add(pvec2 v1, cpvec2 v2);

void __cdecl vec2_sub(pvec2 v1, cpvec2 v2);

void __cdecl vec2_scaled_add(pvec2 v1, cpvec2 v2, float s);

void __cdecl vec2_scaled_sub(pvec2 v1, cpvec2 v2, float s);

void __cdecl vec2_add_n(pvec2 v, int n, ...);

void __cdecl vec2_sub_n(pvec2 v, int n, ...);

void __cdecl vec2_scaled_add_n(pvec2 v, float s, int n, ...);

void __cdecl vec2_scaled_sub_n(pvec2 v, float s, int n, ...);

void __cdecl vec2_sum(cpvec2 v1, cpvec2 v2, pvec2 res);

void __cdecl vec2_diff(cpvec2 v1, cpvec2 v2, pvec2 res);

void __cdecl vec2_mult(cpvec2 v, float s, pvec2 res);

void __cdecl vec2_division(cpvec2 v, float d, pvec2 res);

void __cdecl vec2_sum_n(pvec2 res, int n, ...);

void __cdecl vec2_component_product(pvec2 v1, cpvec2 v2);

void __cdecl vec2_set_component_product(cpvec2 v1, cpvec2 v2, pvec2 res);

float __cdecl vec2_dot_product(cpvec2 v1, cpvec2 v2);

float __cdecl vec2_det_product(cpvec2 v1, cpvec2 v2);

float __cdecl vec2_square_magnitude(cpvec2 v);

float __cdecl vec2_magnitude(cpvec2 v);

void __cdecl vec2_normalize(pvec2 v);

void __cdecl vec2_perpendicular_clw(cpvec2 v, pvec2 res);

void __cdecl vec2_perpendicular_nclw(cpvec2 v, pvec2 res);

void __cdecl vec2_project(cpvec2 what, cpvec2 where, pvec2 res);

void __cdecl vec2_reflect(cpvec2 r, cpvec2 n, pvec2 res);

int __cdecl vec2_is_equal(cpvec2 v1, cpvec2 v2);

#ifdef __cplusplus
}
#endif

#endif // VECTOR2D_H
