#ifndef MATRIX4D_H
#define MATRIX4D_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "LA_sup.h"
#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"

typedef struct Matrix4D mat4;
typedef mat4 *pmat4;
typedef const mat4 cmat4;
typedef cmat4 *cpmat4;

struct Matrix4D
{
    vec4 x_basis;
    vec4 y_basis;
    vec4 z_basis;
    vec4 w_basis;
};

void __cdecl mat4_set(
    pmat4 m,
    float xx, float xy, float xz, float xw,
    float yx, float yy, float yz, float yw,
    float zx, float zy, float zz, float zw,
    float wx, float wy, float wz, float ww);

void __cdecl mat4_set_x_basis(pmat4 m, float x, float y, float z, float w);

void __cdecl mat4_set_y_basis(pmat4 m, float x, float y, float z, float w);

void __cdecl mat4_set_z_basis(pmat4 m, float x, float y, float z, float w);

void __cdecl mat4_set_w_basis(pmat4 m, float x, float y, float z, float w);

void __cdecl mat4_set_basises(pmat4 m, cpvec4 x, cpvec4 y, cpvec4 z, cpvec4 w);

void __cdecl mat4_set_ordinary(pmat4 m);

void __cdecl mat4_transpose(pmat4 m);

void __cdecl mat4_scalar_mult(pmat4 m, float s);

void __cdecl mat4_divide(pmat4 m, float d);

void __cdecl mat4_add(pmat4 m1, cpmat4 m2);

void __cdecl mat4_sub(pmat4 m1, cpmat4 m2);

void __cdecl mat4_sum(cpmat4 m1, cpmat4 m2, pmat4 res);

void __cdecl mat4_diff(cpmat4 m1, cpmat4 m2, pmat4 res);

void __cdecl mat4_compose(pmat4 m1, cpmat4 m2);

void __cdecl mat4_transform(cpmat4 m, pvec4 v);

void __cdecl mat4_compose_res(cpmat4 m1, cpmat4 m2, pmat4 res);

void __cdecl mat4_transform_res(cpmat4 m, cpvec4 v, pvec4 res);

void __cdecl mat4_transform_vec3(cpmat4 m, pvec3 v);

void __cdecl mat4_transform_vec3_res(cpmat4 m, cpvec3 v, pvec3 res);

float __cdecl mat4_determinant(cpmat4 m);

void __cdecl mat4_inverse(pmat4 m);

void __cdecl mat4_normalize(pmat4 m);

void __cdecl mat4_set_scale(pmat4 m, float x, float y, float z);

void __cdecl mat4_set_translate(pmat4 m, float x, float y, float z);

void __cdecl mat4_set_rotate_x(pmat4 m, float rad);

void __cdecl mat4_set_rotate_x_degrees(pmat4 m, float degrees);

void __cdecl mat4_set_rotate_y(pmat4 m, float rad);

void __cdecl mat4_set_rotate_y_degrees(pmat4 m, float degrees);

void __cdecl mat4_set_rotate_z(pmat4 m, float rad);

void __cdecl mat4_set_rotate_z_degrees(pmat4 m, float degrees);

void __cdecl mat4_set_rotate_axis(pmat4 m, float x, float y, float z, float rad);

void __cdecl mat4_set_rotate_axis_degrees(pmat4 m, float x, float y, float z, float degrees);

void __cdecl mat4_set_ortho_projection(pmat4 m, float l, float r, float b, float t, float f, float n);

void __cdecl mat4_set_perspective_projection(pmat4 m, float w, float h, float n, float f, float fov);

void __cdecl mat4_set_scale_to_point(pmat4 m, cpvec3 scale, cpvec3 point);

void __cdecl mat4_set_rotate_around_point(pmat4 m, cpvec3 axis, cpvec3 point, float rad);

int __cdecl mat4_is_equal(cpmat4 m1, cpmat4 m2);

#ifdef __cplusplus
}
#endif

#endif // MATRIX4D_H
