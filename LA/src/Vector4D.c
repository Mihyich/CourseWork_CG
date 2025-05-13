#include "Vector4D.h"

#ifdef __cplusplus
extern "C"
{
#endif

void __cdecl vec4_set(pvec4 v, float x, float y, float z, float w)
{
    v->x = x;
    v->y = y;
    v->z = z;
    v->w = w;
}

void __cdecl vec4_invert(pvec4 v)
{
    v->x = -v->x;
    v->y = -v->y;
    v->z = -v->z;
    v->w = -v->w;
}

void __cdecl vec4_scale(pvec4 v, float s)
{
    v->x *= s;
    v->y *= s;
    v->z *= s;
    v->w *= s;
}

void __cdecl vec4_divide(pvec4 v, float d)
{
    v->x /= d;
    v->y /= d;
    v->z /= d;
    v->w /= d;
}

void __cdecl vec4_add(pvec4 v1, cpvec4 v2)
{
    v1->x += v2->x;
    v1->y += v2->y;
    v1->z += v2->z;
    v1->w += v2->w;
}

void __cdecl vec4_sub(pvec4 v1, cpvec4 v2)
{
    v1->x -= v2->x;
    v1->y -= v2->y;
    v1->z -= v2->z;
    v1->w -= v2->w;
}

void __cdecl vec4_scaled_add(pvec4 v1, cpvec4 v2, float s)
{
    v1->x += v2->x * s;
    v1->y += v2->y * s;
    v1->z += v2->z * s;
    v1->w += v2->w * s;
}

void __cdecl vec4_scaled_sub(pvec4 v1, cpvec4 v2, float s)
{
    v1->x -= v2->x * s;
    v1->y -= v2->y * s;
    v1->z -= v2->z * s;
    v1->w -= v2->w * s;
}

void __cdecl vec4_add_n(pvec4 v, int n, ...)
{
    va_list vl;
    cpvec4 a = NULL;

    va_start(vl, n);

    while (n > 0)
    {
        a = va_arg(vl, cpvec4);

        v->x += a->x;
        v->y += a->y;
        v->z += a->z;
        v->w += a->w;

        --n;
    }

    va_end(vl);
}

void __cdecl vec4_sub_n(pvec4 v, int n, ...)
{
    va_list vl;
    cpvec4 a = NULL;

    va_start(vl, n);

    while (n > 0)
    {
        a = va_arg(vl, cpvec4);

        v->x -= a->x;
        v->y -= a->y;
        v->z -= a->z;
        v->w -= a->w;

        --n;
    }

    va_end(vl);
}

void __cdecl vec4_scaled_add_n(pvec4 v, float s, int n, ...)
{
    va_list vl;
    cpvec4 a = NULL;

    va_start(vl, n);

    while (n > 0)
    {
        a = va_arg(vl, cpvec4);

        v->x += a->x * s;
        v->y += a->y * s;
        v->z += a->z * s;
        v->w += a->w * s;

        --n;
    }

    va_end(vl);
}

void __cdecl vec4_scaled_sub_n(pvec4 v, float s, int n, ...)
{
    va_list vl;
    cpvec4 a = NULL;

    va_start(vl, n);

    while (n > 0)
    {
        a = va_arg(vl, cpvec4);

        v->x -= a->x * s;
        v->y -= a->y * s;
        v->z -= a->z * s;
        v->w -= a->w * s;

        --n;
    }

    va_end(vl);
}

void __cdecl vec4_sum(cpvec4 v1, cpvec4 v2, pvec4 res)
{
    res->x = v1->x + v2->x;
    res->y = v1->y + v2->y;
    res->z = v1->z + v2->z;
    res->w = v1->w + v2->w;
}

void __cdecl vec4_diff(cpvec4 v1, cpvec4 v2, pvec4 res)
{
    res->x = v1->x - v2->x;
    res->y = v1->y - v2->y;
    res->z = v1->z - v2->z;
    res->w = v1->w - v2->w;
}

void __cdecl vec4_sum_n(pvec4 res, int n, ...)
{
    va_list vl;
    cpvec4 a;

    memset(res, 0, sizeof(vec4));
    va_start(vl, n);

    while(n > 0)
    {
        a = va_arg(vl, cpvec4);

        res->x += a->x;
        res->y += a->y;
        res->z += a->z;
        res->w += a->w;

        --n;
    }

    va_end(vl);
}

void __cdecl vec4_component_product(pvec4 v1, cpvec4 v2)
{
    v1->x *= v2->x;
    v1->y *= v2->y;
    v1->z *= v2->z;
    v1->w *= v2->w;
}

void __cdecl vec4_set_component_product(cpvec4 v1, cpvec4 v2, pvec4 res)
{
    res->x = v1->x * v2->x;
    res->y = v1->y * v2->y;
    res->z = v1->z * v2->z;
    res->w = v1->w * v2->w;
}

float __cdecl vec4_dot_product(cpvec4 v1, cpvec4 v2)
{
    return dot4(
        v1->x, v1->y, v1->z, v1->w,
        v2->x, v2->y, v2->z, v2->w
    );
}

float __cdecl vec4_det_product(cpvec4 v1, cpvec4 v2, cpvec4 v3, cpvec4 v4)
{
    return det4(
        v1->x, v1->y, v1->z, v1->w,
        v2->x, v2->y, v2->z, v2->w,
        v3->x, v3->y, v3->z, v3->w,
        v4->x, v4->y, v4->z, v4->w
    );
}

float __cdecl vec4_square_magnitude(cpvec4 v)
{
    return dot4(
        v->x, v->y, v->z, v->w,
        v->x, v->y, v->z, v->w
    );
}

float __cdecl vec4_magnitude(cpvec4 v)
{
    return sqrtf(
        dot4(
            v->x, v->y, v->z, v->w,
            v->x, v->y, v->z, v->w
        )
    );
}

void __cdecl vec4_normalize(pvec4 v)
{
    const float mag = 1.f / vec4_magnitude(v);

    v->x *= mag;
    v->y *= mag;
    v->z *= mag;
    v->w *= mag;
}

int __cdecl vec4_is_equal(cpvec4 v1, cpvec4 v2)
{
    return
        is_equal(v1->x, v2->x) &&
        is_equal(v1->y, v2->y) &&
        is_equal(v1->z, v2->z) &&
        is_equal(v1->w, v2->w);
}

#ifdef __cplusplus
}
#endif
