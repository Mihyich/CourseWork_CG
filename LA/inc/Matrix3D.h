#ifndef MATRIX3D_H
#define MATRIX3D_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "LA_sup.h"
#include "Vector3D.h"
#include "Vector2D.h"

typedef struct Matrix3D mat3;
typedef mat3 *pmat3;
typedef const mat3 cmat3;
typedef cmat3 *cpmat3;

struct Matrix3D
{
    vec3 x_basis;
    vec3 y_basis;
    vec3 z_basis;
};

void __cdecl mat3_set(
    pmat3 m,
    float xx, float xy, float xz,
    float yx, float yy, float yz,
    float zx, float zy, float zz);

void __cdecl mat3_set_x_basis(pmat3 m, float x, float y, float z);

void __cdecl mat3_set_y_basis(pmat3 m, float x, float y, float z);

void __cdecl mat3_set_z_basis(pmat3 m, float x, float y, float z);

void __cdecl mat3_set_basises(pmat3 m, cpvec3 x, cpvec3 y, cpvec3 z);

void __cdecl mat3_set_ordinary(pmat3 m);

void __cdecl mat3_transpose(pmat3 m);

void __cdecl mat3_scalar_mult(pmat3 m, float s);

void __cdecl mat3_divide(pmat3 m, float d);

void __cdecl mat3_add(pmat3 m1, cpmat3 m2);

void __cdecl mat3_sub(pmat3 m1, cpmat3 m2);

void __cdecl mat3_sum(cpmat3 m1, cpmat3 m2, pmat3 res);

void __cdecl mat3_diff(cpmat3 m1, cpmat3 m2, pmat3 res);

void __cdecl mat3_compose(pmat3 m1, cpmat3 m2);

void __cdecl mat3_transform(cpmat3 m, pvec3 v);

void __cdecl mat3_transform_vec2(cpmat3 m, pvec2 v);

void __cdecl mat3_compose_res(cpmat3 m1, cpmat3 m2, pmat3 res);

void __cdecl mat3_transform_res(cpmat3 m, cpvec3 v, pvec3 res);

void __cdecl mat3_transform_vec2_res(cpmat3 m, cpvec2 v, pvec2 res);

float __cdecl mat3_determinant(cpmat3 m);

void __cdecl mat3_inverse(pmat3 m);

void __cdecl mat3_normalize(pmat3 m);

void __cdecl mat3_set_scale(pmat3 m, float x, float y, float z);

void __cdecl mat3_set_translate(pmat3 m, float x, float y);

void __cdecl mat3_set_rotate_x(pmat3 m, float rad);

void __cdecl mat3_set_rotate_x_degrees(pmat3 m, float degrees);

void __cdecl mat3_set_rotate_y(pmat3 m, float rad);

void __cdecl mat3_set_rotate_y_degrees(pmat3 m, float degrees);

void __cdecl mat3_set_rotate_z(pmat3 m, float rad);

void __cdecl mat3_set_rotate_z_degrees(pmat3 m, float degrees);

void __cdecl mat3_set_rotate_axis(pmat3 m, float x, float y, float z, float rad);

void __cdecl mat3_set_rotate_axis_degrees(pmat3 m, float x, float y, float z, float degrees);

void __cdecl mat3_scale(pmat3 m, float x, float y, float z);

void __cdecl mat3_translate(pmat3 m, float x, float y);

void __cdecl mat3_rotate_x(pmat3 m, float rad);

void __cdecl mat3_rotate_x_degrees(pmat3 m, float degrees);

void __cdecl mat3_rotate_y(pmat3 m, float rad);

void __cdecl mat3_rotate_y_degrees(pmat3 m, float degrees);

void __cdecl mat3_rotate_z(pmat3 m, float rad);

void __cdecl mat3_rotate_z_degrees(pmat3 m, float degrees);

void __cdecl mat3_rotate_axis(pmat3 m, float x, float y, float z, float rad);

void __cdecl mat3_rotate_axis_degrees(pmat3 m, float x, float y, float z, float degrees);

void __cdecl mat3_set_ortho_projection(pmat3 m, float l, float r, float b, float t);

void __cdecl mat3_set_scale_to_point(pmat3 m, cpvec2 scale, cpvec2 point);

void __cdecl mat3_set_rotate_around_point(pmat3 m, cpvec2 point, float rad);

int __cdecl mat3_is_equal(cpmat3 m1, cpmat3 m2);

#ifdef __cplusplus
}
#endif

#endif // MATRIX3D_H
