#include "Vector2D.h"

#ifdef __cplusplus
extern "C"
{
#endif

void __cdecl vec2_set(pvec2 v, float x, float y)
{
    v->x = x;
    v->y = y;
}

void __cdecl vec2_invert(pvec2 v)
{
    v->x = -v->x;
    v->y = -v->y;
}

void __cdecl vec2_invert_res(cpvec2 v, pvec2 res)
{
    res->x = -v->x;
    res->y = -v->y;
}

void __cdecl vec2_scale(pvec2 v, float s)
{
    v->x *= s;
    v->y *= s;
}

void __cdecl vec2_divide(pvec2 v, float d)
{
    v->x /= d;
    v->y /= d;
}

void __cdecl vec2_add(pvec2 v1, cpvec2 v2)
{
    v1->x += v2->x;
    v1->y += v2->y;
}

void __cdecl vec2_sub(pvec2 v1, cpvec2 v2)
{
    v1->x -= v2->x;
    v1->y -= v2->y;
}

void __cdecl vec2_scaled_add(pvec2 v1, cpvec2 v2, float s)
{
    v1->x += v2->x * s;
    v1->y += v2->y * s;
}

void __cdecl vec2_scaled_sub(pvec2 v1, cpvec2 v2, float s)
{
    v1->x -= v2->x * s;
    v1->y -= v2->y * s;
}

void __cdecl vec2_add_n(pvec2 v, int n, ...)
{
    va_list vl;
    cpvec2 a = NULL;

    va_start(vl, n);

    while (n > 0)
    {
        a = va_arg(vl, cpvec2);

        v->x += a->x;
        v->y += a->y;

        --n;
    }

    va_end(vl);
}

void __cdecl vec2_sub_n(pvec2 v, int n, ...)
{
    va_list vl;
    cpvec2 a = NULL;

    va_start(vl, n);

    while (n > 0)
    {
        a = va_arg(vl, cpvec2);

        v->x -= a->x;
        v->y -= a->y;

        --n;
    }

    va_end(vl);
}

void __cdecl vec2_scaled_add_n(pvec2 v, float s, int n, ...)
{
    va_list vl;
    cpvec2 a = NULL;

    va_start(vl, n);

    while (n > 0)
    {
        a = va_arg(vl, cpvec2);

        v->x += a->x * s;
        v->y += a->y * s;

        --n;
    }

    va_end(vl);
}

void __cdecl vec2_scaled_sub_n(pvec2 v, float s, int n, ...)
{
    va_list vl;
    cpvec2 a = NULL;

    va_start(vl, n);

    while (n > 0)
    {
        a = va_arg(vl, cpvec2);

        v->x -= a->x * s;
        v->y -= a->y * s;

        --n;
    }

    va_end(vl);
}

void __cdecl vec2_sum(cpvec2 v1, cpvec2 v2, pvec2 res)
{
    res->x = v1->x + v2->x;
    res->y = v1->y + v2->y;
}

void __cdecl vec2_diff(cpvec2 v1, cpvec2 v2, pvec2 res)
{
    res->x = v1->x - v2->x;
    res->y = v1->y - v2->y;
}

void __cdecl vec2_mult(cpvec2 v, float s, pvec2 res)
{
    res->x = v->x * s;
    res->y = v->y * s;
}

void __cdecl vec2_division(cpvec2 v, float d, pvec2 res)
{
    res->x = v->x / d;
    res->y = v->y / d;
}

void __cdecl vec2_sum_n(pvec2 res, int n, ...)
{
    va_list vl;
    cpvec2 a;

    memset(res, 0, sizeof(vec2));
    va_start(vl, n);

    while(n > 0)
    {
        a = va_arg(vl, cpvec2);

        res->x += a->x;
        res->y += a->y;

        --n;
    }

    va_end(vl);
}

void __cdecl vec2_component_product(pvec2 v1, cpvec2 v2)
{
    v1->x *= v2->x;
    v1->y *= v2->y;
}

void __cdecl vec2_set_component_product(cpvec2 v1, cpvec2 v2, pvec2 res)
{
    res->x = v1->x * v2->x;
    res->y = v1->y * v2->y;
}

float __cdecl vec2_dot_product(cpvec2 v1, cpvec2 v2)
{
    return dot2(v1->x, v1->y, v2->x, v2->y);
}

float __cdecl vec2_det_product(cpvec2 v1, cpvec2 v2)
{
    return det2(v1->x, v1->y, v2->x, v2->y);
}

float __cdecl vec2_square_magnitude(cpvec2 v)
{
    return dot2(v->x, v->y, v->x, v->y);
}

float __cdecl vec2_magnitude(cpvec2 v)
{
    return sqrtf(dot2(v->x, v->y, v->x, v->y));
}

void __cdecl vec2_normalize(pvec2 v)
{
    vec2_divide(v, vec2_magnitude(v));
}

void __cdecl vec2_perpendicular_clw(cpvec2 v, pvec2 res)
{
    res->x = -v->y;
    res->y = v->x;
}

void __cdecl vec2_perpendicular_nclw(cpvec2 v, pvec2 res)
{
    res->x = v->y;
    res->y = -v->x;
}

void __cdecl vec2_project(cpvec2 what, cpvec2 where, pvec2 res)
{
    float part = vec2_dot_product(what, where) / vec2_dot_product(where, where);
	res->x = where->x * part;
    res->y = where->y * part;
}

void __cdecl vec2_reflect(cpvec2 r, cpvec2 n, pvec2 res)
{
    float part;
    vec2 base;
    vec2 roof;

    part = -vec2_dot_product(r, n) / vec2_dot_product(n, n);

    base.x = n->x * part;
    base.y = n->y * part;

    vec2_sum(r, &base, &roof);
    vec2_scale(&roof, 2.f);
    vec2_diff(&roof, r, res);
}

int __cdecl vec2_is_equal(cpvec2 v1, cpvec2 v2)
{
    return is_equal(v1->x, v2->x) && is_equal(v1->y, v2->y);
}

#ifdef __cplusplus
}
#endif
