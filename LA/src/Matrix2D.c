#include "Matrix2D.h"

#ifdef __cplusplus
extern "C"
{
#endif

void __cdecl mat2_set(pmat2 m, float xx, float xy, float yx, float yy)
{
    m->x_basis.x = xx;
    m->x_basis.y = xy;

    m->y_basis.x = yx;
    m->y_basis.y = yy;
}

void __cdecl mat2_set_x_basis(pmat2 m, float x, float y)
{
    m->x_basis.x = x;
    m->x_basis.y = y;
}

void __cdecl mat2_set_y_basis(pmat2 m, float x, float y)
{
    m->y_basis.x = x;
    m->y_basis.y = y;
}

void __cdecl mat2_set_basises(pmat2 m, cpvec2 x, cpvec2 y)
{
    m->x_basis = *x;
    m->y_basis = *y;
}

void __cdecl mat2_transpose(pmat2 m)
{
    _swap_u(&m->x_basis.y, &m->y_basis.x, sizeof(float));
}

void __cdecl mat2_scalar_mult(pmat2 m, float s)
{
    m->x_basis.x *= s;
    m->x_basis.y *= s;

    m->y_basis.x *= s;
    m->y_basis.y *= s;
}

void __cdecl mat2_divide(pmat2 m, float d)
{
    m->x_basis.x /= d;
    m->x_basis.y /= d;

    m->y_basis.x /= d;
    m->y_basis.y /= d;
}

void __cdecl mat2_add(pmat2 m1, cpmat2 m2)
{
    m1->x_basis.x += m2->x_basis.x;
    m1->x_basis.y += m2->x_basis.y;

    m1->y_basis.x += m2->y_basis.x;
    m1->y_basis.y += m2->y_basis.y;
}

void __cdecl mat2_sub(pmat2 m1, cpmat2 m2)
{
    m1->x_basis.x -= m2->x_basis.x;
    m1->x_basis.y -= m2->x_basis.y;

    m1->y_basis.x -= m2->y_basis.x;
    m1->y_basis.y -= m2->y_basis.y;
}

void __cdecl mat2_sum(cpmat2 m1, cpmat2 m2, pmat2 res)
{
    res->x_basis.x = m1->x_basis.x + m2->x_basis.x;
    res->x_basis.y = m1->x_basis.y + m2->x_basis.y;

    res->y_basis.x = m1->y_basis.x + m2->y_basis.x;
    res->y_basis.y = m1->y_basis.y + m2->y_basis.y;
}

void __cdecl mat2_diff(cpmat2 m1, cpmat2 m2, pmat2 res)
{
    res->x_basis.x = m1->x_basis.x - m2->x_basis.x;
    res->x_basis.y = m1->x_basis.y - m2->x_basis.y;

    res->y_basis.x = m1->y_basis.x - m2->y_basis.x;
    res->y_basis.y = m1->y_basis.y - m2->y_basis.y;
}

void __cdecl mat2_compose(pmat2 m1, cpmat2 m2)
{
    const float xx = m1->x_basis.x;
    const float xy = m1->x_basis.y;

    float *md1 = (float*)m1;
    const float *md2 = (const float*)m2;

    md1[0] = dot2(xx, md1[2], md2[0], md2[1]);
    md1[1] = dot2(xy, md1[3], md2[0], md2[1]);

    md1[2] = dot2(xx, md1[2], md2[2], md2[3]);
    md1[3] = dot2(xy, md1[3], md2[2], md2[3]);
}

void __cdecl mat2_transform(cpmat2 m, pvec2 v)
{
    const float x = v->x;
    const float *md = (const float*)m;

    v->x = dot2(md[0], md[2], x, v->y);
    v->y = dot2(md[1], md[3], x, v->y);
}

void __cdecl mat2_compose_res(cpmat2 m1, cpmat2 m2, pmat2 res)
{
    const float *md1 = (const float*)m1;
    const float *md2 = (const float*)m2;
    float *rd = (float*)res;

    rd[0] = dot2(md1[0], md1[2], md2[0], md2[1]);
    rd[1] = dot2(md1[1], md1[3], md2[0], md2[1]);

    rd[2] = dot2(md1[0], md1[2], md2[2], md2[3]);
    rd[3] = dot2(md1[1], md1[3], md2[2], md2[3]);
}

void __cdecl mat2_transform_res(cpmat2 m, cpvec2 v, pvec2 res)
{
    const float *md = (const float*)m;

    res->x = dot2(md[0], md[2], v->x, v->y);
    res->y = dot2(md[1], md[3], v->x, v->y);
}

float __cdecl mat2_determinant(cpmat2 m)
{
    return det2(
        m->x_basis.x, m->x_basis.y,
        m->y_basis.x, m->y_basis.y
    );
}

void __cdecl mat2_inverse(pmat2 m)
{
    float determinant;

	float a00, a01;
	float a10, a11;

    float *md = (float*)m;

	a00 = md[3];
	a01 = -md[2];

    determinant = dot2(md[0], md[1], a00, a01);

	if (is_equal_zero(determinant))
		return;

	a10 = -md[1];
	a11 = md[0];

	determinant = 1.f / determinant;

	md[0] = a00 * determinant;
	md[2] = a01 * determinant;

	md[1] = a10 * determinant;
	md[3] = a11 * determinant;
}

void __cdecl mat2_normalize(pmat2 m)
{
    float determinant;

	float a00, a01;
	float a10, a11;

    float *md = (float*)m;

	a00 = md[3];
	a01 = -md[2];

	determinant = dot2(md[0], md[1], a00, a01);

	if (is_equal_zero(determinant))
		return;

	a10 = -md[1];
	a11 = md[0];

	determinant = 1.f / determinant;

	md[0] = a00 * determinant;
	md[1] = a01 * determinant;

	md[2] = a10 * determinant;
	md[3] = a11 * determinant;
}

void __cdecl mat2_set_scale(pmat2 m, float x, float y)
{
    m->x_basis.x = x;
    m->x_basis.y = 0.f;

    m->y_basis.x = 0.f;
    m->y_basis.y = y;
}

void __cdecl mat2_set_rotate(pmat2 m, float rad)
{
    float *md = (float*)m;

    md[0] = cosf(rad);
	md[1] = sinf(rad);

	md[2] = -md[1];
	md[3] = md[0];
}

void __cdecl mat2_set_rotate_degrees(pmat2 m, float degrees)
{
    mat2_set_rotate(m, degrees_to_radians(degrees));
}

void __cdecl mat2_scale(pmat2 m, float x, float y)
{
    float *md = (float*)m;

    md[0] *= x;
	md[1] *= x;

	md[2] *= y;
	md[3] *= y;
}

void __cdecl mat2_rotate(pmat2 m, float rad)
{
    float *md = (float*)m;

    float c = cosf(rad);
	float s = sinf(rad);

	float xx = md[0];
	float xy = md[1];

	md[0] = dot2(xx, md[2], c, s);
	md[1] = dot2(xy, md[3], c, s);

	md[2] = dot2(xx, md[2], -s, c);
	md[3] = dot2(xy, md[3], -s, c);
}

void __cdecl mat2_rotate_degrees(pmat2 m, float degrees)
{
    mat2_rotate(m, degrees_to_radians(degrees));
}

int __cdecl mat2_is_equal(cpmat2 m1, cpmat2 m2)
{
    return
        vec2_is_equal(&m1->x_basis, &m2->x_basis) &&
        vec2_is_equal(&m1->y_basis, &m2->y_basis);
}

#ifdef __cplusplus
}
#endif
