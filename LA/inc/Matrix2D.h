#ifndef MATRIX2D_H
#define MATRIX2D_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "LA_sup.h"
#include "Vector2D.h"

typedef struct Matrix2D mat2;
typedef mat2 *pmat2;
typedef const mat2 cmat2;
typedef cmat2 *cpmat2;

struct Matrix2D
{
    vec2 x_basis;
    vec2 y_basis;
};

void __cdecl mat2_set(pmat2 m, float xx, float xy, float yx, float yy);

void __cdecl mat2_set_x_basis(pmat2 m, float x, float y);

void __cdecl mat2_set_y_basis(pmat2 m, float x, float y);

void __cdecl mat2_set_basises(pmat2 m, cpvec2 x, cpvec2 y);

void __cdecl mat2_transpose(pmat2 m);

void __cdecl mat2_scalar_mult(pmat2 m, float s);

void __cdecl mat2_divide(pmat2 m, float d);

void __cdecl mat2_add(pmat2 m1, cpmat2 m2);

void __cdecl mat2_sub(pmat2 m1, cpmat2 m2);

void __cdecl mat2_sum(cpmat2 m1, cpmat2 m2, pmat2 res);

void __cdecl mat2_diff(cpmat2 m1, cpmat2 m2, pmat2 res);

void __cdecl mat2_compose(pmat2 m1, cpmat2 m2);

void __cdecl mat2_transform(cpmat2 m, pvec2 v);

void __cdecl mat2_compose_res(cpmat2 m1, cpmat2 m2, pmat2 res);

void __cdecl mat2_transform_res(cpmat2 m, cpvec2 v, pvec2 res);

float __cdecl mat2_determinant(cpmat2 m);

void __cdecl mat2_inverse(pmat2 m);

void __cdecl mat2_normalize(pmat2 m);

void __cdecl mat2_set_scale(pmat2 m, float x, float y);

void __cdecl mat2_set_rotate(pmat2 m, float rad);

void __cdecl mat2_set_rotate_degrees(pmat2 m, float degrees);

void __cdecl mat2_scale(pmat2 m, float x, float y);

void __cdecl mat2_rotate(pmat2 m, float rad);

void __cdecl mat2_rotate_degrees(pmat2 m, float degrees);

int __cdecl mat2_is_equal(cpmat2 m1, cpmat2 m2);

#ifdef __cplusplus
}
#endif

#endif // MATRIX2D_H
