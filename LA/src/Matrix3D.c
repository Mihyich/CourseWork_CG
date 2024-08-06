#include "Matrix3D.h"

#ifdef __cplusplus
extern "C"
{
#endif

void __cdecl mat3_set(
    pmat3 m,
    float xx, float xy, float xz,
    float yx, float yy, float yz,
    float zx, float zy, float zz)
{
    m->x_basis.x = xx; m->x_basis.y = xy; m->x_basis.z = xz;
    m->y_basis.x = yx; m->y_basis.y = yy; m->y_basis.z = yz;
    m->z_basis.x = zx; m->z_basis.y = zy; m->z_basis.z = zz;
}

void __cdecl mat3_set_x_basis(pmat3 m, float x, float y, float z)
{
    m->x_basis.x = x;
    m->x_basis.y = y;
    m->x_basis.z = z;
}

void __cdecl mat3_set_y_basis(pmat3 m, float x, float y, float z)
{
    m->y_basis.x = x;
    m->y_basis.y = y;
    m->y_basis.z = z;
}

void __cdecl mat3_set_z_basis(pmat3 m, float x, float y, float z)
{
    m->z_basis.x = x;
    m->z_basis.y = y;
    m->z_basis.z = z;
}

void __cdecl mat3_set_basises(pmat3 m, cpvec3 x, cpvec3 y, cpvec3 z)
{
    m->x_basis = *x;
    m->y_basis = *y;
    m->z_basis = *z;
}

void __cdecl mat3_set_ordinary(pmat3 m)
{
    mat3_set_x_basis(m, 1.f, 0.f, 0.f);
    mat3_set_y_basis(m, 0.f, 1.f, 0.f);
    mat3_set_z_basis(m, 0.f, 0.f, 1.f);
}

void __cdecl mat3_transpose(pmat3 m)
{
    float *md = (float*)m;
    _swap_u(md + 1, md + 3, sizeof(float));
    _swap_u(md + 2, md + 6, sizeof(float));
    _swap_u(md + 5, md + 7, sizeof(float));
}

void __cdecl mat3_scalar_mult(pmat3 m, float s)
{
    m->x_basis.x *= s;
    m->x_basis.y *= s;
    m->x_basis.z *= s;

    m->y_basis.x *= s;
    m->y_basis.y *= s;
    m->y_basis.z *= s;

    m->z_basis.x *= s;
    m->z_basis.y *= s;
    m->z_basis.z *= s;
}

void __cdecl mat3_divide(pmat3 m, float d)
{
    m->x_basis.x /= d;
    m->x_basis.y /= d;
    m->x_basis.z /= d;

    m->y_basis.x /= d;
    m->y_basis.y /= d;
    m->y_basis.z /= d;

    m->z_basis.x /= d;
    m->z_basis.y /= d;
    m->z_basis.z /= d;
}

void __cdecl mat3_add(pmat3 m1, cpmat3 m2)
{
    m1->x_basis.x += m2->x_basis.x;
    m1->x_basis.y += m2->x_basis.y;
    m1->x_basis.z += m2->x_basis.z;

    m1->y_basis.x += m2->y_basis.x;
    m1->y_basis.y += m2->y_basis.y;
    m1->y_basis.z += m2->y_basis.z;

    m1->z_basis.x += m2->z_basis.x;
    m1->z_basis.y += m2->z_basis.y;
    m1->z_basis.z += m2->z_basis.z;
}

void __cdecl mat3_sub(pmat3 m1, cpmat3 m2)
{
    m1->x_basis.x -= m2->x_basis.x;
    m1->x_basis.y -= m2->x_basis.y;
    m1->x_basis.z -= m2->x_basis.z;

    m1->y_basis.x -= m2->y_basis.x;
    m1->y_basis.y -= m2->y_basis.y;
    m1->y_basis.z -= m2->y_basis.z;

    m1->z_basis.x -= m2->z_basis.x;
    m1->z_basis.y -= m2->z_basis.y;
    m1->z_basis.z -= m2->z_basis.z;
}

void __cdecl mat3_sum(cpmat3 m1, cpmat3 m2, pmat3 res)
{
    res->x_basis.x = m1->x_basis.x + m2->x_basis.x;
    res->x_basis.y = m1->x_basis.y + m2->x_basis.y;
    res->x_basis.z = m1->x_basis.z + m2->x_basis.z;

    res->y_basis.x = m1->y_basis.x + m2->y_basis.x;
    res->y_basis.y = m1->y_basis.y + m2->y_basis.y;
    res->y_basis.z = m1->y_basis.z + m2->y_basis.z;

    res->z_basis.x = m1->z_basis.x + m2->z_basis.x;
    res->z_basis.y = m1->z_basis.y + m2->z_basis.y;
    res->z_basis.z = m1->z_basis.z + m2->z_basis.z;
}

void __cdecl mat3_diff(cpmat3 m1, cpmat3 m2, pmat3 res)
{
    res->x_basis.x = m1->x_basis.x - m2->x_basis.x;
    res->x_basis.y = m1->x_basis.y - m2->x_basis.y;
    res->x_basis.z = m1->x_basis.z - m2->x_basis.z;

    res->y_basis.x = m1->y_basis.x - m2->y_basis.x;
    res->y_basis.y = m1->y_basis.y - m2->y_basis.y;
    res->y_basis.z = m1->y_basis.z - m2->y_basis.z;

    res->z_basis.x = m1->z_basis.x - m2->z_basis.x;
    res->z_basis.y = m1->z_basis.y - m2->z_basis.y;
    res->z_basis.z = m1->z_basis.z - m2->z_basis.z;
}

void __cdecl mat3_compose(pmat3 m1, cpmat3 m2)
{
    const float xx = m1->x_basis.x;
    const float xy = m1->x_basis.y;
    const float xz = m1->x_basis.z;

    const float yx = m1->y_basis.x;
    const float yy = m1->y_basis.y;
    const float yz = m1->y_basis.z;

    float *md1 = (float*)m1;
    const float *md2 = (const float*)m2;

    md1[0] = dot3(xx, yx, md1[6], md2[0], md2[1], md2[2]);
	md1[1] = dot3(xy, yy, md1[7], md2[0], md2[1], md2[2]);
	md1[2] = dot3(xz, yz, md1[8], md2[0], md2[1], md2[2]);

	md1[3] = dot3(xx, yx, md1[6], md2[3], md2[4], md2[5]);
	md1[4] = dot3(xy, yy, md1[7], md2[3], md2[4], md2[5]);
	md1[5] = dot3(xz, yz, md1[8], md2[3], md2[4], md2[5]);

	md1[6] = dot3(xx, yx, md1[6], md2[6], md2[7], md2[8]);
	md1[7] = dot3(xy, yy, md1[7], md2[6], md2[7], md2[8]);
	md1[8] = dot3(xz, yz, md1[8], md2[6], md2[7], md2[8]);
}

void __cdecl mat3_transform(cpmat3 m, pvec3 v)
{
    const float x = v->x;
    const float y = v->y;
    const float *md = (const float*)m;

    v->x = dot3(md[0], md[3], md[6], x, y, v->z);
    v->y = dot3(md[1], md[4], md[7], x, y, v->z);
    v->z = dot3(md[2], md[5], md[8], x, y, v->z);
}

void __cdecl mat3_transform_vec2(cpmat3 m, pvec2 v)
{
    vec3 temp = { v->x, v->y, 1.f };

    mat3_transform(m, &temp);

    v->x = temp.x;
    v->y = temp.y;
}

void __cdecl mat3_compose_res(cpmat3 m1, cpmat3 m2, pmat3 res)
{
    const float *md1 = (const float*)m1;
    const float *md2 = (const float*)m2;
    float *rd = (float*)res;

    rd[0] = dot3(md1[0], md1[3], md1[6], md2[0], md2[1], md2[2]);
	rd[1] = dot3(md1[1], md1[4], md1[7], md2[0], md2[1], md2[2]);
	rd[2] = dot3(md1[2], md1[5], md1[8], md2[0], md2[1], md2[2]);

	rd[3] = dot3(md1[0], md1[3], md1[6], md2[3], md2[4], md2[5]);
	rd[4] = dot3(md1[1], md1[4], md1[7], md2[3], md2[4], md2[5]);
	rd[5] = dot3(md1[2], md1[5], md1[8], md2[3], md2[4], md2[5]);

	rd[6] = dot3(md1[0], md1[3], md1[6], md2[6], md2[7], md2[8]);
	rd[7] = dot3(md1[1], md1[4], md1[7], md2[6], md2[7], md2[8]);
	rd[8] = dot3(md1[2], md1[5], md1[8], md2[6], md2[7], md2[8]);
}

void __cdecl mat3_transform_res(cpmat3 m, cpvec3 v, pvec3 res)
{
    const float *md = (const float*)m;

    res->x = dot3(md[0], md[3], md[6], v->x, v->y, v->z);
    res->y = dot3(md[1], md[4], md[7], v->x, v->y, v->z);
    res->z = dot3(md[2], md[5], md[8], v->x, v->y, v->z);
}

void __cdecl mat3_transform_vec2_res(cpmat3 m, cpvec2 v, pvec2 res)
{
    const float *md = (const float*)m;

    res->x = dot3(md[0], md[3], md[6], v->x, v->y, 1.f);
    res->y = dot3(md[1], md[4], md[7], v->x, v->y, 1.f);
}

float __cdecl mat3_determinant(cpmat3 m)
{
    return det3(
        m->x_basis.x, m->x_basis.y, m->x_basis.z,
        m->y_basis.x, m->y_basis.y, m->y_basis.z,
        m->z_basis.x, m->z_basis.y, m->z_basis.z
    );
}

void __cdecl mat3_inverse(pmat3 m)
{
    float determinant;

    float a00, a01, a02;
	float a10, a11, a12;
	float a20, a21, a22;

    float *md = (float*)m;

    a00 = det2(md[4], md[5], md[7], md[8]);
	a01 = -det2(md[3], md[5], md[6], md[8]);
	a02 = det2(md[3], md[4], md[6], md[7]);

    determinant = dot3(md[0], md[1], md[2], a00, a01, a02);

	if (is_equal_zero(determinant))
		return;

    a10 = -det2(md[1], md[2], md[7], md[8]);
	a11 = det2(md[0], md[2], md[6], md[8]);
	a12 = -det2(md[0], md[1], md[6], md[7]);

    a20 = det2(md[1], md[2], md[4], md[5]);
	a21 = -det2(md[0], md[2], md[3], md[5]);
	a22 = det2(md[0], md[1], md[3], md[4]);

	determinant = 1.f / determinant;

	md[0] = a00 * determinant;
	md[3] = a01 * determinant;
	md[6] = a02 * determinant;

	md[1] = a10 * determinant;
	md[4] = a11 * determinant;
	md[7] = a12 * determinant;

	md[2] = a20 * determinant;
	md[5] = a21 * determinant;
	md[8] = a22 * determinant;
}

void __cdecl mat3_normalize(pmat3 m)
{
    float determinant;

    float a00, a01, a02;
	float a10, a11, a12;
	float a20, a21, a22;

    float *md = (float*)m;

    a00 = det2(md[4], md[5], md[7], md[8]);
	a01 = -det2(md[3], md[5], md[6], md[8]);
	a02 = det2(md[3], md[4], md[6], md[7]);

    determinant = dot3(md[0], md[1], md[2], a00, a01, a02);

	if (is_equal_zero(determinant))
		return;

    a10 = -det2(md[1], md[2], md[7], md[8]);
	a11 = det2(md[0], md[2], md[6], md[8]);
	a12 = -det2(md[0], md[1], md[6], md[7]);

    a20 = det2(md[1], md[2], md[4], md[5]);
	a21 = -det2(md[0], md[2], md[3], md[5]);
	a22 = det2(md[0], md[1], md[3], md[4]);

	determinant = 1.f / determinant;

	md[0] = a00 * determinant;
	md[1] = a01 * determinant;
	md[2] = a02 * determinant;

	md[3] = a10 * determinant;
	md[4] = a11 * determinant;
	md[5] = a12 * determinant;

	md[6] = a20 * determinant;
	md[7] = a21 * determinant;
	md[8] = a22 * determinant;
}

void __cdecl mat3_set_scale(pmat3 m, float x, float y, float z)
{
    m->x_basis.x = x;
    m->x_basis.y = 0.f;
    m->x_basis.z = 0.f;

    m->y_basis.x = 0.f;
    m->y_basis.y = y;
    m->y_basis.z = 0.f;

    m->z_basis.x = 0.f;
    m->z_basis.y = 0.f;
    m->z_basis.z = z;
}

void __cdecl mat3_set_translate(pmat3 m, float x, float y)
{
    m->x_basis.x = 1.f;
    m->x_basis.y = 0.f;
    m->x_basis.z = 0.f;

    m->y_basis.x = 0.f;
    m->y_basis.y = 1.f;
    m->y_basis.z = 0.f;

    m->z_basis.x = x;
    m->z_basis.y = y;
    m->z_basis.z = 1.f;
}

void __cdecl mat3_set_rotate_x(pmat3 m, float rad)
{
    m->x_basis.x = 1.f;
    m->x_basis.y = 0.f;
    m->x_basis.z = 0.f;

    m->y_basis.x = 0.f;
    m->y_basis.y = cosf(rad);
    m->y_basis.z = sinf(rad);

    m->z_basis.x = 0.f;
    m->z_basis.y = -m->y_basis.z;
    m->z_basis.z = m->y_basis.y;
}

void __cdecl mat3_set_rotate_x_degrees(pmat3 m, float degrees)
{
    mat3_set_rotate_x(m, degrees_to_radians(degrees));
}

void __cdecl mat3_set_rotate_y(pmat3 m, float rad)
{
    m->x_basis.x = cosf(rad);
    m->x_basis.y = 0.f;
    m->x_basis.z = sinf(rad);

    m->y_basis.x = 0.f;
    m->y_basis.y = 1.f;
    m->y_basis.z = 0.f;

    m->z_basis.x = -m->x_basis.z;
    m->z_basis.y = 0.f;
    m->z_basis.z = m->x_basis.x;
}

void __cdecl mat3_set_rotate_y_degrees(pmat3 m, float degrees)
{
    mat3_set_rotate_y(m, degrees_to_radians(degrees));
}

void __cdecl mat3_set_rotate_z(pmat3 m, float rad)
{
    m->x_basis.x = cosf(rad);
    m->x_basis.y = sinf(rad);
    m->x_basis.z = 0.f;

    m->y_basis.x = -m->x_basis.y;
    m->y_basis.y = m->x_basis.x;
    m->y_basis.z = 0.f;

    m->z_basis.x = 0.f;
    m->z_basis.y = 0.f;
    m->z_basis.z = 1.f;
}

void __cdecl mat3_set_rotate_z_degrees(pmat3 m, float degrees)
{
    mat3_set_rotate_z(m, degrees_to_radians(degrees));
}

void __cdecl mat3_set_rotate_axis(pmat3 m, float x, float y, float z, float rad)
{
    const float c = cosf(rad);
	const float s = sinf(rad);
	const float fsu = 1.f - c;

    m->x_basis.x = x * x * fsu + c;
    m->x_basis.y = x * y * fsu - z * s;
    m->x_basis.z = x * z * fsu + y * s;

    m->y_basis.x = x * y * fsu + z * s;
    m->y_basis.y = y * y * fsu + c;
    m->y_basis.z = y * z * fsu - x * s;

    m->z_basis.x = x * z * fsu - y * s;
    m->z_basis.y = y * z * fsu + x * s;
    m->z_basis.z = z * z * fsu + c;
}

void __cdecl mat3_set_rotate_axis_degrees(pmat3 m, float x, float y, float z, float degrees)
{
    mat3_set_rotate_axis(m, x, y, z, degrees_to_radians(degrees));
}

void __cdecl mat3_scale(pmat3 m, float x, float y, float z)
{
    m->x_basis.x *= x;
    m->x_basis.y *= x;
    m->x_basis.z *= x;

    m->y_basis.x *= y;
    m->y_basis.y *= y;
    m->y_basis.z *= y;

    m->z_basis.x *= z;
    m->z_basis.y *= z;
    m->z_basis.z *= z;
}

void __cdecl mat3_translate(pmat3 m, float x, float y)
{
    float *md = (float*)m;

    m->z_basis.x = dot3(md[0], md[3], md[6], x, y, 1);
    m->z_basis.y = dot3(md[1], md[4], md[7], x, y, 1);
    m->z_basis.z = dot3(md[2], md[5], md[8], x, y, 1);
}

void __cdecl mat3_rotate_x(pmat3 m, float rad)
{
    const float c = cosf(rad);
    const float s = sinf(rad);
	const float yx = m->y_basis.x;
    const float yy = m->y_basis.y;
    const float yz = m->y_basis.z;

	m->y_basis.x *= c;
	m->y_basis.y *= c;
	m->y_basis.z *= c;

	m->y_basis.x += m->z_basis.x * s;
	m->y_basis.y += m->z_basis.y * s;
	m->y_basis.z += m->z_basis.z * s;

	m->z_basis.x *= c;
	m->z_basis.y *= c;
	m->z_basis.z *= c;

	m->z_basis.x -= yx * s;
	m->z_basis.y -= yy * s;
	m->z_basis.z -= yz * s;
}

void __cdecl mat3_rotate_x_degrees(pmat3 m, float degrees)
{
    mat3_rotate_x(m, degrees_to_radians(degrees));
}

void __cdecl mat3_rotate_y(pmat3 m, float rad)
{
    const float c = cosf(rad);;
    const float s = sinf(rad);
	const float xx = m->x_basis.x;
    const float xy = m->x_basis.y;
    const float xz = m->x_basis.z;

	m->x_basis.x *= c;
	m->x_basis.y *= c;
	m->x_basis.z *= c;

	m->x_basis.x += m->z_basis.x * s;
	m->x_basis.y += m->z_basis.y * s;
	m->x_basis.z += m->z_basis.z * s;

	m->z_basis.x *= c;
	m->z_basis.y *= c;
	m->z_basis.z *= c;

	m->z_basis.x -= xx * s;
	m->z_basis.y -= xy * s;
	m->z_basis.z -= xz * s;
}

void __cdecl mat3_rotate_y_degrees(pmat3 m, float degrees)
{
    mat3_rotate_y(m, degrees_to_radians(degrees));
}

void __cdecl mat3_rotate_z(pmat3 m, float rad)
{
    const float c = cosf(rad);
    const float s = sinf(rad);
	const float xx = m->x_basis.x;
    const float xy = m->x_basis.y;
    const float xz = m->x_basis.z;

	m->x_basis.x *= c;
	m->x_basis.y *= c;
	m->x_basis.z *= c;

	m->x_basis.x += m->y_basis.x * s;
	m->x_basis.y += m->y_basis.y * s;
	m->x_basis.z += m->y_basis.z * s;

	m->y_basis.x *= c;
	m->y_basis.y *= c;
	m->y_basis.z *= c;

	m->y_basis.x -= xx * s;
	m->y_basis.y -= xy * s;
	m->y_basis.z -= xz * s;
}

void __cdecl mat3_rotate_z_degrees(pmat3 m, float degrees)
{
    mat3_rotate_z(m, degrees_to_radians(degrees));
}

void __cdecl mat3_rotate_axis(pmat3 m, float x, float y, float z, float rad)
{
    const float c = cosf(rad);
	const float s = sinf(rad);
	const float fsu = 1.f - c;

    mat3 rot;

	rot.x_basis.x = x * x * fsu + c;
	rot.x_basis.y = x * y * fsu + z * s;
	rot.x_basis.z = x * z * fsu - y * s;

	rot.y_basis.x = x * y * fsu - z * s;
	rot.y_basis.y = y * y * fsu + c;
	rot.y_basis.z = y * z * fsu + x * s;

	rot.z_basis.x = x * z * fsu + y * s;
	rot.z_basis.y = y * z * fsu - x * s;
	rot.z_basis.z = z * z * fsu + c;

    mat3_compose(m, &rot);
}

void __cdecl mat3_rotate_axis_degrees(pmat3 m, float x, float y, float z, float degrees)
{
    mat3_rotate_axis(m, x, y, z, degrees_to_radians(degrees));
}

void __cdecl mat3_set_ortho_projection(pmat3 m, float l, float r, float b, float t)
{
    m->x_basis.x = 2.f / (r - l);
    m->x_basis.y = 0.f;
    m->x_basis.z = 0.f;

    m->y_basis.x = 0.f;
    m->y_basis.y = 2.f / (t - b);
    m->y_basis.z = 0.f;

    m->z_basis.x = (l + r) / (l - r);
    m->z_basis.y = (t + b) / (t - b);
    m->z_basis.z = 1.f;
}

void __cdecl mat3_set_scale_to_point(pmat3 m, cpvec2 scale, cpvec2 point)
{
    mat3_set_x_basis(m, scale->x, 0.f, 0.f);
    mat3_set_y_basis(m, 0.f, scale->y, 0.f);
    mat3_set_z_basis(m, point->x * (1.f - scale->x), point->y * (1.f - scale->y), 1.f);
}

void __cdecl mat3_set_rotate_around_point(pmat3 m, cpvec2 point, float rad)
{
    const float a = cosf(rad);
    const float b = sinf(rad);

    mat3_set_x_basis(m, a, b, 0.f);
    mat3_set_y_basis(m, -b, a, 0.f);
    
    m->z_basis.x = dot2(point->x, point->y, 1.f - a, b);
    m->z_basis.y = dot2(point->x, point->y, -b, 1.f - a);
    m->z_basis.z = 1.f;
}

int __cdecl mat3_is_equal(cpmat3 m1, cpmat3 m2)
{
    return
        vec3_is_equal(&m1->x_basis, &m2->x_basis) &&
        vec3_is_equal(&m1->y_basis, &m2->y_basis) &&
        vec3_is_equal(&m1->z_basis, &m2->z_basis);
}

#ifdef __cplusplus
}
#endif
