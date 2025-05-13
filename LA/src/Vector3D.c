#include "Vector3D.h"

#ifdef __cplusplus
extern "C"
{
#endif

void __cdecl vec3_set(pvec3 v, float x, float y, float z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

void __cdecl vec3_min(pvec3 v1, cpvec3 v2)
{
    v1->x = fminf(v1->x, v2->x);
    v1->y = fminf(v1->y, v2->y);
    v1->z = fminf(v1->z, v2->z);
}

void __cdecl vec3_min_n(pvec3 v, int n, ...)
{
    va_list vl;
    cpvec3 a = NULL;
    vec3_set(v, __FLT_MAX__, __FLT_MAX__, __FLT_MAX__);

    va_start(vl, n);

    while (n > 0)
    {
        a = va_arg(vl, cpvec3);
        vec3_min(v, a);
        --n;
    }

    va_end(vl);
}

void __cdecl vec3_min_res(cpvec3 v1, cpvec3 v2, pvec3 res)
{
    res->x = fminf(v1->x, v2->x);
    res->y = fminf(v1->y, v2->y);
    res->z = fminf(v1->z, v2->z);
}

void __cdecl vec3_max(pvec3 v1, cpvec3 v2)
{
    v1->x = fmaxf(v1->x, v2->x);
    v1->y = fmaxf(v1->y, v2->y);
    v1->z = fmaxf(v1->z, v2->z);
}

void __cdecl vec3_max_n(pvec3 v, int n, ...)
{
    va_list vl;
    cpvec3 a = NULL;
    vec3_set(v, -__FLT_MAX__, -__FLT_MAX__, -__FLT_MAX__);

    va_start(vl, n);

    while (n > 0)
    {
        a = va_arg(vl, cpvec3);
        vec3_max(v, a);
        --n;
    }

    va_end(vl);
}

void __cdecl vec3_max_res(cpvec3 v1, cpvec3 v2, pvec3 res)
{
    res->x = fmaxf(v1->x, v2->x);
    res->y = fmaxf(v1->y, v2->y);
    res->z = fmaxf(v1->z, v2->z);
}

void __cdecl vec3_invert(pvec3 v)
{
    v->x = -v->x;
    v->y = -v->y;
    v->z = -v->z;
}

void __cdecl vec3_scale(pvec3 v, float s)
{
    v->x *= s;
    v->y *= s;
    v->z *= s;
}

void __cdecl vec3_divide(pvec3 v, float d)
{
    v->x /= d;
    v->y /= d;
    v->z /= d;
}

void __cdecl vec3_add(pvec3 v1, cpvec3 v2)
{
    v1->x += v2->x;
    v1->y += v2->y;
    v1->z += v2->z;
}

void __cdecl vec3_sub(pvec3 v1, cpvec3 v2)
{
    v1->x -= v2->x;
    v1->y -= v2->y;
    v1->z -= v2->z;
}

void __cdecl vec3_scaled_add(pvec3 v1, cpvec3 v2, float s)
{
    v1->x += v2->x * s;
    v1->y += v2->y * s;
    v1->z += v2->z * s;
}

void __cdecl vec3_scaled_sub(pvec3 v1, cpvec3 v2, float s)
{
    v1->x -= v2->x * s;
    v1->y -= v2->y * s;
    v1->z -= v2->z * s;
}

void __cdecl vec3_add_n(pvec3 v, int n, ...)
{
    va_list vl;
    cpvec3 a = NULL;

    va_start(vl, n);

    while (n > 0)
    {
        a = va_arg(vl, cpvec3);

        v->x += a->x;
        v->y += a->y;
        v->z += a->z;

        --n;
    }

    va_end(vl);
}

void __cdecl vec3_sub_n(pvec3 v, int n, ...)
{
    va_list vl;
    cpvec3 a = NULL;

    va_start(vl, n);

    while (n > 0)
    {
        a = va_arg(vl, cpvec3);

        v->x -= a->x;
        v->y -= a->y;
        v->z -= a->z;

        --n;
    }

    va_end(vl);
}

void __cdecl vec3_scaled_add_n(pvec3 v, float s, int n, ...)
{
    va_list vl;
    cpvec3 a = NULL;

    va_start(vl, n);

    while (n > 0)
    {
        a = va_arg(vl, cpvec3);

        v->x += a->x * s;
        v->y += a->y * s;
        v->z += a->z * s;

        --n;
    }

    va_end(vl);
}

void __cdecl vec3_scaled_sub_n(pvec3 v, float s, int n, ...)
{
    va_list vl;
    cpvec3 a = NULL;

    va_start(vl, n);

    while (n > 0)
    {
        a = va_arg(vl, cpvec3);

        v->x -= a->x * s;
        v->y -= a->y * s;
        v->z -= a->z * s;

        --n;
    }

    va_end(vl);
}

void __cdecl vec3_sum(cpvec3 v1, cpvec3 v2, pvec3 res)
{
    res->x = v1->x + v2->x;
    res->y = v1->y + v2->y;
    res->z = v1->z + v2->z;
}

void __cdecl vec3_diff(cpvec3 v1, cpvec3 v2, pvec3 res)
{
    res->x = v1->x - v2->x;
    res->y = v1->y - v2->y;
    res->z = v1->z - v2->z;
}

void __cdecl vec3_sum_n(pvec3 res, int n, ...)
{
    va_list vl;
    cpvec3 a;
    vec3_set(res, 0, 0, 0);

    va_start(vl, n);

    while(n > 0)
    {
        a = va_arg(vl, cpvec3);

        res->x += a->x;
        res->y += a->y;
        res->z += a->z;

        --n;
    }

    va_end(vl);
}

void __cdecl vec3_sum_scaled_n(pvec3 res, float s, int n, ...)
{
    va_list vl;
    cpvec3 a;
    vec3_set(res, 0, 0, 0);

    va_start(vl, n);

    while(n > 0)
    {
        a = va_arg(vl, cpvec3);

        res->x += a->x;
        res->y += a->y;
        res->z += a->z;

        --n;
    }

    va_end(vl);

    vec3_scale(res, s);
}

void __cdecl vec3_component_product(pvec3 v1, cpvec3 v2)
{
    v1->x *= v2->x;
    v1->y *= v2->y;
    v1->z *= v2->z;
}

void __cdecl vec3_set_component_product(cpvec3 v1, cpvec3 v2, pvec3 res)
{
    res->x = v1->x * v2->x;
    res->y = v1->y * v2->y;
    res->z = v1->z * v2->z;
}

float __cdecl vec3_dot_product(cpvec3 v1, cpvec3 v2)
{
    return dot3(
        v1->x, v1->y, v1->z,
        v2->x, v2->y, v2->z);
}

float __cdecl vec3_det_product(cpvec3 v1, cpvec3 v2, cpvec3 v3)
{
    return det3(
        v1->x, v1->y, v1->z,
        v2->x, v2->y, v2->z,
        v3->x, v3->y, v3->z);
}

float __cdecl vec3_square_magnitude(cpvec3 v)
{
    return dot3(
        v->x, v->y, v->z,
        v->x, v->y, v->z);
}

float __cdecl vec3_magnitude(cpvec3 v)
{
    return sqrtf(dot3(v->x, v->y, v->z, v->x, v->y, v->z));
}

void __cdecl vec3_vector_product(cpvec3 v1, cpvec3 v2, pvec3 res)
{
    res->x = v1->y * v2->z - v1->z * v2->y;
	res->y = v1->z * v2->x - v1->x * v2->z;
	res->z = v1->x * v2->y - v1->y * v2->x;
}

void __cdecl vec3_normalize(pvec3 v)
{
    const float mag = 1.f / vec3_magnitude(v);

    v->x *= mag;
    v->y *= mag;
    v->z *= mag;
}

void __cdecl vec3_project(cpvec3 what, cpvec3 where, pvec3 res)
{
    float part = vec3_dot_product(what, where) / vec3_dot_product(where, where);
	res->x = where->x * part;
    res->y = where->y * part;
    res->z = where->z * part;
}

void __cdecl vec3_reflect(cpvec3 r, cpvec3 n, pvec3 res)
{
    float part;
    vec3 base;
    vec3 roof;

    part = -vec3_dot_product(r, n) / vec3_dot_product(n, n);

    base.x = n->x * part;
    base.y = n->y * part;
    base.z = n->z * part;

    vec3_sum(r, &base, &roof);
    vec3_scale(&roof, 2.f);
    vec3_diff(&roof, r, res);
}

int __cdecl vec3_is_equal(cpvec3 v1, cpvec3 v2)
{
    return is_equal(v1->x, v2->x) && is_equal(v1->y, v2->y) && is_equal(v1->z, v2->z);
}

#ifdef __cplusplus
}
#endif
