#ifndef VECTOR4D_H
#define VECTOR4D_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include "LA_sup.h"

#define dot4(x1, y1, z1, w1, x2, y2, z2, w2) \
((x1) * (x2) + (y1) * (y2) + (z1) * (z2) + (w1) * (w2))

#define det4( \
    x1, y1, z1, w1, \
    x2, y2, z2, w2, \
    x3, y3, z3, w3, \
    x4, y4, z4, w4) \
(((z3) * (w4) - (w3) * (z4)) * ((x1) * (y2) - (y1) * (x2)) + \
((y3) * (w4) - (w3) * (y4)) * ((z1) * (x2) - (x1) * (z2)) + \
((y3) * (z4) - (z3) * (y4)) * ((x1) * (w2) - (w1) * (x2)) + \
((x3) * (w4) - (w3) * (x4)) * ((y1) * (z2) - (z1) * (y2)) + \
((x3) * (z4) - (z3) * (x4)) * ((w1) * (y2) - (y1) * (w2)) + \
((x3) * (y4) - (y3) * (x4)) * ((z1) * (w2) - (w1) * (z2)))

typedef struct Vector4D vec4;
typedef vec4 *pvec4;
typedef const vec4 cvec4;
typedef cvec4 *cpvec4;

struct Vector4D
{
    float x;
    float y;
    float z;
    float w;
};

void __cdecl vec4_set(pvec4 v, float x, float y, float z, float w);

void __cdecl vec4_invert(pvec4 v);

void __cdecl vec4_scale(pvec4 v, float s);

void __cdecl vec4_divide(pvec4 v, float d);

void __cdecl vec4_add(pvec4 v1, cpvec4 v2);

void __cdecl vec4_sub(pvec4 v1, cpvec4 v2);

void __cdecl vec4_scaled_add(pvec4 v1, cpvec4 v2, float s);

void __cdecl vec4_scaled_sub(pvec4 v1, cpvec4 v2, float s);

void __cdecl vec4_add_n(pvec4 v, int n, ...);

void __cdecl vec4_sub_n(pvec4 v, int n, ...);

void __cdecl vec4_scaled_add_n(pvec4 v, float s, int n, ...);

void __cdecl vec4_scaled_sub_n(pvec4 v, float s, int n, ...);

void __cdecl vec4_sum(cpvec4 v1, cpvec4 v2, pvec4 res);

void __cdecl vec4_diff(cpvec4 v1, cpvec4 v2, pvec4 res);

void __cdecl vec4_sum_n(pvec4 res, int n, ...);

void __cdecl vec4_component_product(pvec4 v1, cpvec4 v2);

void __cdecl vec4_set_component_product(cpvec4 v1, cpvec4 v2, pvec4 res);

float __cdecl vec4_dot_product(cpvec4 v1, cpvec4 v2);

float __cdecl vec4_det_product(cpvec4 v1, cpvec4 v2, cpvec4 v3, cpvec4 v4);

float __cdecl vec4_square_magnitude(cpvec4 v);

float __cdecl vec4_magnitude(cpvec4 v);

void __cdecl vec4_normalize(pvec4 v);

int __cdecl vec4_is_equal(cpvec4 v1, cpvec4 v2);

#ifdef __cplusplus
}
#endif

#endif // VECTOR4D_H
