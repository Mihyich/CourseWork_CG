#include "Matrix4D.h"

#ifdef __cplusplus
extern "C"
{
#endif

void __cdecl mat4_set(
    pmat4 m,
    float xx, float xy, float xz, float xw,
    float yx, float yy, float yz, float yw,
    float zx, float zy, float zz, float zw,
    float wx, float wy, float wz, float ww)
{
    m->x_basis.x = xx;
    m->x_basis.y = xy;
    m->x_basis.z = xz;
    m->x_basis.w = xw;

    m->y_basis.x = yx;
    m->y_basis.y = yy;
    m->y_basis.z = yz;
    m->y_basis.w = yw;

    m->z_basis.x = zx;
    m->z_basis.y = zy;
    m->z_basis.z = zz;
    m->z_basis.w = zw;

    m->w_basis.x = wx;
    m->w_basis.y = wy;
    m->w_basis.z = wz;
    m->w_basis.w = ww;
}

void __cdecl mat4_set_x_basis(pmat4 m, float x, float y, float z, float w)
{
    m->x_basis.x = x;
    m->x_basis.y = y;
    m->x_basis.z = z;
    m->x_basis.w = w;
}

void __cdecl mat4_set_y_basis(pmat4 m, float x, float y, float z, float w)
{
    m->y_basis.x = x;
    m->y_basis.y = y;
    m->y_basis.z = z;
    m->y_basis.w = w;
}

void __cdecl mat4_set_z_basis(pmat4 m, float x, float y, float z, float w)
{
    m->z_basis.x = x;
    m->z_basis.y = y;
    m->z_basis.z = z;
    m->z_basis.w = w;
}

void __cdecl mat4_set_w_basis(pmat4 m, float x, float y, float z, float w)
{
    m->w_basis.x = x;
    m->w_basis.y = y;
    m->w_basis.z = z;
    m->w_basis.w = w;
}

void __cdecl mat4_set_basises(pmat4 m, cpvec4 x, cpvec4 y, cpvec4 z, cpvec4 w)
{
    m->x_basis = *x;
    m->y_basis = *y;
    m->z_basis = *z;
    m->w_basis = *w;
}

void __cdecl mat4_set_ordinary(pmat4 m)
{
    mat4_set_x_basis(m, 1.f, 0.f, 0.f, 0.f);
    mat4_set_y_basis(m, 0.f, 1.f, 0.f, 0.f);
    mat4_set_z_basis(m, 0.f, 0.f, 1.f, 0.f);
    mat4_set_w_basis(m, 0.f, 0.f, 0.f, 1.f);
}

void __cdecl mat4_transpose(pmat4 m)
{
    _swap_u(&m->x_basis.y, &m->y_basis.x, sizeof(float));
    _swap_u(&m->x_basis.z, &m->z_basis.x, sizeof(float));
    _swap_u(&m->x_basis.w, &m->w_basis.x, sizeof(float));
    _swap_u(&m->y_basis.z, &m->z_basis.y, sizeof(float));
    _swap_u(&m->y_basis.w, &m->w_basis.y, sizeof(float));
    _swap_u(&m->z_basis.w, &m->w_basis.z, sizeof(float));
}

void __cdecl mat4_scalar_mult(pmat4 m, float s)
{
    m->x_basis.x *= s;
    m->x_basis.y *= s;
    m->x_basis.z *= s;
    m->x_basis.w *= s;

    m->y_basis.x *= s;
    m->y_basis.y *= s;
    m->y_basis.z *= s;
    m->y_basis.w *= s;

    m->z_basis.x *= s;
    m->z_basis.y *= s;
    m->z_basis.z *= s;
    m->z_basis.w *= s;

    m->w_basis.x *= s;
    m->w_basis.y *= s;
    m->w_basis.z *= s;
    m->w_basis.w *= s;
}

void __cdecl mat4_divide(pmat4 m, float d)
{
    m->x_basis.x /= d;
    m->x_basis.y /= d;
    m->x_basis.z /= d;
    m->x_basis.w /= d;

    m->y_basis.x /= d;
    m->y_basis.y /= d;
    m->y_basis.z /= d;
    m->y_basis.w /= d;

    m->z_basis.x /= d;
    m->z_basis.y /= d;
    m->z_basis.z /= d;
    m->z_basis.w /= d;

    m->w_basis.x /= d;
    m->w_basis.y /= d;
    m->w_basis.z /= d;
    m->w_basis.w /= d;
}

void __cdecl mat4_add(pmat4 m1, cpmat4 m2)
{
    m1->x_basis.x += m2->x_basis.x;
    m1->x_basis.y += m2->x_basis.y;
    m1->x_basis.z += m2->x_basis.z;
    m1->x_basis.w += m2->x_basis.w;

    m1->y_basis.x += m2->y_basis.x;
    m1->y_basis.y += m2->y_basis.y;
    m1->y_basis.z += m2->y_basis.z;
    m1->y_basis.w += m2->y_basis.w;

    m1->z_basis.x += m2->z_basis.x;
    m1->z_basis.y += m2->z_basis.y;
    m1->z_basis.z += m2->z_basis.z;
    m1->z_basis.w += m2->z_basis.w;

    m1->w_basis.x += m2->w_basis.x;
    m1->w_basis.y += m2->w_basis.y;
    m1->w_basis.z += m2->w_basis.z;
    m1->w_basis.w += m2->w_basis.w;
}

void __cdecl mat4_sub(pmat4 m1, cpmat4 m2)
{
    m1->x_basis.x -= m2->x_basis.x;
    m1->x_basis.y -= m2->x_basis.y;
    m1->x_basis.z -= m2->x_basis.z;
    m1->x_basis.w -= m2->x_basis.w;

    m1->y_basis.x -= m2->y_basis.x;
    m1->y_basis.y -= m2->y_basis.y;
    m1->y_basis.z -= m2->y_basis.z;
    m1->y_basis.w -= m2->y_basis.w;

    m1->z_basis.x -= m2->z_basis.x;
    m1->z_basis.y -= m2->z_basis.y;
    m1->z_basis.z -= m2->z_basis.z;
    m1->z_basis.w -= m2->z_basis.w;

    m1->w_basis.x -= m2->w_basis.x;
    m1->w_basis.y -= m2->w_basis.y;
    m1->w_basis.z -= m2->w_basis.z;
    m1->w_basis.w -= m2->w_basis.w;
}

void __cdecl mat4_sum(cpmat4 m1, cpmat4 m2, pmat4 res)
{
    res->x_basis.x = m1->x_basis.x + m2->x_basis.x;
    res->x_basis.y = m1->x_basis.y + m2->x_basis.y;
    res->x_basis.z = m1->x_basis.z + m2->x_basis.z;
    res->x_basis.w = m1->x_basis.w + m2->x_basis.w;

    res->y_basis.x = m1->y_basis.x + m2->y_basis.x;
    res->y_basis.y = m1->y_basis.y + m2->y_basis.y;
    res->y_basis.z = m1->y_basis.z + m2->y_basis.z;
    res->y_basis.w = m1->y_basis.w + m2->y_basis.w;

    res->z_basis.x = m1->z_basis.x + m2->z_basis.x;
    res->z_basis.y = m1->z_basis.y + m2->z_basis.y;
    res->z_basis.z = m1->z_basis.z + m2->z_basis.z;
    res->z_basis.w = m1->z_basis.w + m2->z_basis.w;

    res->w_basis.x = m1->w_basis.x + m2->w_basis.x;
    res->w_basis.y = m1->w_basis.y + m2->w_basis.y;
    res->w_basis.z = m1->w_basis.z + m2->w_basis.z;
    res->w_basis.w = m1->w_basis.w + m2->w_basis.w;
}

void __cdecl mat4_diff(cpmat4 m1, cpmat4 m2, pmat4 res)
{
    res->x_basis.x = m1->x_basis.x - m2->x_basis.x;
    res->x_basis.y = m1->x_basis.y - m2->x_basis.y;
    res->x_basis.z = m1->x_basis.z - m2->x_basis.z;
    res->x_basis.w = m1->x_basis.w - m2->x_basis.w;

    res->y_basis.x = m1->y_basis.x - m2->y_basis.x;
    res->y_basis.y = m1->y_basis.y - m2->y_basis.y;
    res->y_basis.z = m1->y_basis.z - m2->y_basis.z;
    res->y_basis.w = m1->y_basis.w - m2->y_basis.w;

    res->z_basis.x = m1->z_basis.x - m2->z_basis.x;
    res->z_basis.y = m1->z_basis.y - m2->z_basis.y;
    res->z_basis.z = m1->z_basis.z - m2->z_basis.z;
    res->z_basis.w = m1->z_basis.w - m2->z_basis.w;

    res->w_basis.x = m1->w_basis.x - m2->w_basis.x;
    res->w_basis.y = m1->w_basis.y - m2->w_basis.y;
    res->w_basis.z = m1->w_basis.z - m2->w_basis.z;
    res->w_basis.w = m1->w_basis.w - m2->w_basis.w;
}

void __cdecl mat4_compose(pmat4 m1, cpmat4 m2)
{
    const float xx = m1->x_basis.x;
    const float xy = m1->x_basis.y;
    const float xz = m1->x_basis.z;
    const float xw = m1->x_basis.w;

    const float yx = m1->y_basis.x;
    const float yy = m1->y_basis.y;
    const float yz = m1->y_basis.z;
    const float yw = m1->y_basis.w;

    const float zx = m1->z_basis.x;
    const float zy = m1->z_basis.y;
    const float zz = m1->z_basis.z;
    const float zw = m1->z_basis.w;

    float *md1 = (float*)m1;
    const float *md2 = (const float*)m2;

    md1[0] = dot4(xx, yx, zx, md1[12], md2[0], md2[1], md2[2], md2[3]);
    md1[1] = dot4(xy, yy, zy, md1[13], md2[0], md2[1], md2[2], md2[3]);
    md1[2] = dot4(xz, yz, zz, md1[14], md2[0], md2[1], md2[2], md2[3]);
    md1[3] = dot4(xw, yw, zw, md1[15], md2[0], md2[1], md2[2], md2[3]);

    md1[4] = dot4(xx, yx, zx, md1[12], md2[4], md2[5], md2[6], md2[7]);
    md1[5] = dot4(xy, yy, zy, md1[13], md2[4], md2[5], md2[6], md2[7]);
    md1[6] = dot4(xz, yz, zz, md1[14], md2[4], md2[5], md2[6], md2[7]);
    md1[7] = dot4(xw, yw, zw, md1[15], md2[4], md2[5], md2[6], md2[7]);

    md1[8] =  dot4(xx, yx, zx, md1[12], md2[8], md2[9], md2[10], md2[11]);
    md1[9] =  dot4(xy, yy, zy, md1[13], md2[8], md2[9], md2[10], md2[11]);
    md1[10] = dot4(xz, yz, zz, md1[14], md2[8], md2[9], md2[10], md2[11]);
    md1[11] = dot4(xw, yw, zw, md1[15], md2[8], md2[9], md2[10], md2[11]);

    md1[12] = dot4(xx, yx, zx, md1[12], md2[12], md2[13], md2[14], md2[15]);
    md1[13] = dot4(xy, yy, zy, md1[13], md2[12], md2[13], md2[14], md2[15]);
    md1[14] = dot4(xz, yz, zz, md1[14], md2[12], md2[13], md2[14], md2[15]);
    md1[15] = dot4(xw, yw, zw, md1[15], md2[12], md2[13], md2[14], md2[15]);
}

void __cdecl mat4_transform(cpmat4 m, pvec4 v)
{
    const float x = v->x;
    const float y = v->y;
    const float z = v->z;
    const float *md = (const float*)m;

    v->x = dot4(md[0], md[4], md[8], md[12], x, y, z, v->w);
    v->y = dot4(md[1], md[5], md[9], md[13], x, y, z, v->w);
    v->z = dot4(md[2], md[6], md[10], md[14], x, y, z, v->w);
    v->w = dot4(md[3], md[7], md[11], md[15], x, y, z, v->w);
}

void __cdecl mat4_compose_res(cpmat4 m1, cpmat4 m2, pmat4 res)
{
    const float *md1 = (const float*)m1;
    const float *md2 = (const float*)m2;
    float *rd = (float*)res;

    rd[0] = dot4(md1[0], md1[4], md1[8], md1[12], md2[0], md2[1], md2[2], md2[3]);
	rd[1] = dot4(md1[1], md1[5], md1[9], md1[13], md2[0], md2[1], md2[2], md2[3]);
	rd[2] = dot4(md1[2], md1[6], md1[10], md1[14], md2[0], md2[1], md2[2], md2[3]);
    rd[3] = dot4(md1[3], md1[7], md1[11], md1[15], md2[0], md2[1], md2[2], md2[3]);

    rd[4] = dot4(md1[0], md1[4], md1[8], md1[12], md2[4], md2[5], md2[6], md2[7]);
	rd[5] = dot4(md1[1], md1[5], md1[9], md1[13], md2[4], md2[5], md2[6], md2[7]);
	rd[6] = dot4(md1[2], md1[6], md1[10], md1[14], md2[4], md2[5], md2[6], md2[7]);
    rd[7] = dot4(md1[3], md1[7], md1[11], md1[15], md2[4], md2[5], md2[6], md2[7]);

    rd[8] = dot4(md1[0], md1[4], md1[8], md1[12], md2[8], md2[9], md2[10], md2[11]);
	rd[9] = dot4(md1[1], md1[5], md1[9], md1[13], md2[8], md2[9], md2[10], md2[11]);
	rd[10] = dot4(md1[2], md1[6], md1[10], md1[14], md2[8], md2[9], md2[10], md2[11]);
    rd[11] = dot4(md1[3], md1[7], md1[11], md1[15], md2[8], md2[9], md2[10], md2[11]);

    rd[12] = dot4(md1[0], md1[4], md1[8], md1[12], md2[12], md2[13], md2[14], md2[15]);
	rd[13] = dot4(md1[1], md1[5], md1[9], md1[13], md2[12], md2[13], md2[14], md2[15]);
	rd[14] = dot4(md1[2], md1[6], md1[10], md1[14], md2[12], md2[13], md2[14], md2[15]);
    rd[15] = dot4(md1[3], md1[7], md1[11], md1[15], md2[12], md2[13], md2[14], md2[15]);
}

void __cdecl mat4_transform_res(cpmat4 m, cpvec4 v, pvec4 res)
{
    const float *md = (const float*)m;

    res->x = dot4(md[0], md[4], md[8], md[12], v->x, v->y, v->z, v->w);
    res->y = dot4(md[1], md[5], md[9], md[13], v->x, v->y, v->z, v->w);
    res->z = dot4(md[2], md[6], md[10], md[14], v->x, v->y, v->z, v->w);
    res->w = dot4(md[3], md[7], md[11], md[15], v->x, v->y, v->z, v->w);
}

void __cdecl mat4_transform_vec3(cpmat4 m, pvec3 v)
{
    const float *md = (const float*)m;

    v->x = dot4(md[0], md[4], md[8], md[12], v->x, v->y, v->z, 1.f);
    v->y = dot4(md[1], md[5], md[9], md[13], v->x, v->y, v->z, 1.f);
    v->z = dot4(md[2], md[6], md[10], md[14], v->x, v->y, v->z, 1.f);
}

void __cdecl mat4_transform_vec3_res(cpmat4 m, cpvec3 v, pvec3 res)
{
    const float *md = (const float*)m;

    res->x = dot4(md[0], md[4], md[8], md[12], v->x, v->y, v->z, 1.f);
    res->y = dot4(md[1], md[5], md[9], md[13], v->x, v->y, v->z, 1.f);
    res->z = dot4(md[2], md[6], md[10], md[14], v->x, v->y, v->z, 1.f);
}

float __cdecl mat4_determinant(cpmat4 m)
{
    return det4(
        m->x_basis.x, m->x_basis.y, m->x_basis.z, m->x_basis.w,
        m->y_basis.x, m->y_basis.y, m->y_basis.z, m->y_basis.w,
        m->z_basis.x, m->z_basis.y, m->z_basis.z, m->z_basis.w,
        m->w_basis.x, m->w_basis.y, m->w_basis.z, m->w_basis.w
    );
}

void __cdecl mat4_inverse(pmat4 m)
{
    float determinant;

	float a00, a01, a02, a03;
	float a10, a11, a12, a13;
	float a20, a21, a22, a23;
	float a30, a31, a32, a33;

    float *md = (float*)m;

	a00 = det3(md[5], md[6], md[7],
			   md[9], md[10], md[11],
			   md[13], md[14], md[15]);

	a01 = -det3(md[4], md[6], md[7],
				md[8], md[10], md[11],
				md[12], md[14], md[15]);

	a02 = det3(md[4], md[5], md[7],
			   md[8], md[9], md[11],
			   md[12], md[13], md[15]);

	a03 = -det3(md[4], md[5], md[6],
				md[8], md[9], md[10],
				md[12], md[13], md[14]);

	determinant = dot4(md[0], md[1], md[2], md[3], a00, a01, a02, a03);

	if (is_equal_zero(determinant))
		return;

	a10 = -det3(md[1], md[2], md[3],
				md[9], md[10], md[11],
				md[13], md[14], md[15]);

	a11 = det3(md[0], md[2], md[3],
			   md[8], md[10], md[11],
			   md[12], md[14], md[15]);

	a12 = -det3(md[0], md[1], md[3],
				md[8], md[9], md[11],
				md[12], md[13], md[15]);

	a13 = det3(md[0], md[1], md[2],
			   md[8], md[9], md[10],
			   md[12], md[13], md[14]);

	a20 = det3(md[1], md[2], md[3],
			   md[5], md[6], md[7],
			   md[13], md[14], md[15]);

	a21 = -det3(md[0], md[2], md[3],
				md[4], md[6], md[7],
				md[12], md[14], md[15]);

	a22 = det3(md[0], md[1], md[3],
			   md[4], md[5], md[7],
			   md[12], md[13], md[15]);

	a23 = -det3(md[0], md[1], md[2],
				md[4], md[5], md[6],
				md[12], md[13], md[14]);

	a30 = -det3(md[1], md[2], md[3],
				md[5], md[6], md[7],
				md[9], md[10], md[11]);

	a31 = det3(md[0], md[2], md[3],
			   md[4], md[6], md[7],
			   md[8], md[10], md[11]);

	a32 = -det3(md[0], md[1], md[3],
				md[4], md[5], md[7],
				md[8], md[9], md[11]);

	a33 = det3(md[0], md[1], md[2],
			   md[4], md[5], md[6],
			   md[8], md[9], md[10]);

	determinant = 1.f / determinant;

	md[0] = a00 * determinant;
	md[4] = a01 * determinant;
	md[8] = a02 * determinant;
	md[12] = a03 * determinant;

	md[1] = a10 * determinant;
	md[5] = a11 * determinant;
	md[9] = a12 * determinant;
	md[13] = a13 * determinant;

	md[2] = a20 * determinant;
	md[6] = a21 * determinant;
	md[10] = a22 * determinant;
	md[14] = a23 * determinant;

	md[3] = a30 * determinant;
	md[7] = a31 * determinant;
	md[11] = a32 * determinant;
	md[15] = a33 * determinant;
}

void __cdecl mat4_normalize(pmat4 m)
{
    float determinant;

	float a00, a01, a02, a03;
	float a10, a11, a12, a13;
	float a20, a21, a22, a23;
	float a30, a31, a32, a33;

    float *md = (float*)m;

	a00 = det3(md[5], md[6], md[7],
			   md[9], md[10], md[11],
			   md[13], md[14], md[15]);

	a01 = -det3(md[4], md[6], md[7],
				md[8], md[10], md[11],
				md[12], md[14], md[15]);

	a02 = det3(md[4], md[5], md[7],
			   md[8], md[9], md[11],
			   md[12], md[13], md[15]);

	a03 = -det3(md[4], md[5], md[6],
				md[8], md[9], md[10],
				md[12], md[13], md[14]);

	determinant = dot4(md[0], md[1], md[2], md[3], a00, a01, a02, a03);

	if (is_equal_zero(determinant))
		return;

	a10 = -det3(md[1], md[2], md[3],
				md[9], md[10], md[11],
				md[13], md[14], md[15]);

	a11 = det3(md[0], md[2], md[3],
			   md[8], md[10], md[11],
			   md[12], md[14], md[15]);

	a12 = -det3(md[0], md[1], md[3],
				md[8], md[9], md[11],
				md[12], md[13], md[15]);

	a13 = det3(md[0], md[1], md[2],
			   md[8], md[9], md[10],
			   md[12], md[13], md[14]);

	a20 = det3(md[1], md[2], md[3],
			   md[5], md[6], md[7],
			   md[13], md[14], md[15]);

	a21 = -det3(md[0], md[2], md[3],
				md[4], md[6], md[7],
				md[12], md[14], md[15]);

	a22 = det3(md[0], md[1], md[3],
			   md[4], md[5], md[7],
			   md[12], md[13], md[15]);

	a23 = -det3(md[0], md[1], md[2],
				md[4], md[5], md[6],
				md[12], md[13], md[14]);

	a30 = -det3(md[1], md[2], md[3],
				md[5], md[6], md[7],
				md[9], md[10], md[11]);

	a31 = det3(md[0], md[2], md[3],
			   md[4], md[6], md[7],
			   md[8], md[10], md[11]);

	a32 = -det3(md[0], md[1], md[3],
				md[4], md[5], md[7],
				md[8], md[9], md[11]);

	a33 = det3(md[0], md[1], md[2],
			   md[4], md[5], md[6],
			   md[8], md[9], md[10]);

	determinant = 1.f / determinant;

	md[0] = a00 * determinant;
	md[1] = a01 * determinant;
	md[2] = a02 * determinant;
	md[3] = a03 * determinant;

	md[4] = a10 * determinant;
	md[5] = a11 * determinant;
	md[6] = a12 * determinant;
	md[7] = a13 * determinant;

	md[8] = a20 * determinant;
	md[9] = a21 * determinant;
	md[10] = a22 * determinant;
	md[11] = a23 * determinant;

	md[12] = a30 * determinant;
	md[13] = a31 * determinant;
	md[14] = a32 * determinant;
	md[15] = a33 * determinant;
}

void __cdecl mat4_set_scale(pmat4 m, float x, float y, float z)
{
    m->x_basis.x = x;
    m->x_basis.y = 0.f;
    m->x_basis.z = 0.f;
    m->x_basis.w = 0.f;

    m->y_basis.x = 0.f;
    m->y_basis.y = y;
    m->y_basis.z = 0.f;
    m->y_basis.w = 0.f;

    m->z_basis.x = 0.f;
    m->z_basis.y = 0.f;
    m->z_basis.z = z;
    m->z_basis.w = 0.f;

    m->w_basis.x = 0.f;
    m->w_basis.y = 0.f;
    m->w_basis.z = 0.f;
    m->w_basis.w = 1.f;
}

void __cdecl mat4_set_translate(pmat4 m, float x, float y, float z)
{
    m->x_basis.x = 1.f;
    m->x_basis.y = 0.f;
    m->x_basis.z = 0.f;
    m->x_basis.w = 0.f;

    m->y_basis.x = 0.f;
    m->y_basis.y = 1.f;
    m->y_basis.z = 0.f;
    m->y_basis.w = 0.f;

    m->z_basis.x = 0.f;
    m->z_basis.y = 0.f;
    m->z_basis.z = 1.f;
    m->z_basis.w = 0.f;

    m->w_basis.x = x;
    m->w_basis.y = y;
    m->w_basis.z = z;
    m->w_basis.w = 1.f;
}

void __cdecl mat4_set_rotate_x(pmat4 m, float rad)
{
    m->x_basis.x = 1.f;
    m->x_basis.y = 0.f;
    m->x_basis.z = 0.f;
    m->x_basis.w = 0.f;

    m->y_basis.x = 0.f;
    m->y_basis.y = cosf(rad);
    m->y_basis.z = sinf(rad);
    m->y_basis.w = 0.f;

    m->z_basis.x = 0.f;
    m->z_basis.y = -m->y_basis.z;
    m->z_basis.z = m->y_basis.y;
    m->z_basis.w = 0.f;

    m->w_basis.x = 0.f;
    m->w_basis.y = 0.f;
    m->w_basis.z = 0.f;
    m->w_basis.w = 1.f;
}

void __cdecl mat4_set_rotate_x_degrees(pmat4 m, float degrees)
{
    mat4_set_rotate_x(m, degrees_to_radians(degrees));
}

void __cdecl mat4_set_rotate_y(pmat4 m, float rad)
{
    m->x_basis.x = cosf(rad);
    m->x_basis.y = 0.f;
    m->x_basis.z = sinf(rad);
    m->x_basis.w = 0.f;

    m->y_basis.x = 0.f;
    m->y_basis.y = 1.f;
    m->y_basis.z = 0.f;
    m->y_basis.w = 0.f;

    m->z_basis.x = -m->x_basis.z;
    m->z_basis.y = 0.f;
    m->z_basis.z = m->x_basis.x;
    m->z_basis.w = 0.f;

    m->w_basis.x = 0.f;
    m->w_basis.y = 0.f;
    m->w_basis.z = 0.f;
    m->w_basis.w = 1.f;
}

void __cdecl mat4_set_rotate_y_degrees(pmat4 m, float degrees)
{
    mat4_set_rotate_y(m, degrees_to_radians(degrees));
}

void __cdecl mat4_set_rotate_z(pmat4 m, float rad)
{
    m->x_basis.x = cosf(rad);
    m->x_basis.y = sinf(rad);
    m->x_basis.z = 0.f;
    m->x_basis.w = 0.f;

    m->y_basis.x = -m->x_basis.y;
    m->y_basis.y = m->x_basis.x;
    m->y_basis.z = 0.f;
    m->y_basis.w = 0.f;

    m->z_basis.x = 0.f;
    m->z_basis.y = 0.f;
    m->z_basis.z = 1.f;
    m->z_basis.w = 0.f;

    m->w_basis.x = 0.f;
    m->w_basis.y = 0.f;
    m->w_basis.z = 0.f;
    m->w_basis.w = 1.f;
}

void __cdecl mat4_set_rotate_z_degrees(pmat4 m, float degrees)
{
    mat4_set_rotate_z(m, degrees_to_radians(degrees));
}

void __cdecl mat4_set_rotate_axis(pmat4 m, float x, float y, float z, float rad)
{
    const float c = cosf(rad);
	const float s = sinf(rad);
	const float fsu = 1.f - c;

    m->x_basis.x = x * x * fsu + c;
    m->x_basis.y = x * y * fsu - z * s;
    m->x_basis.z = x * z * fsu + y * s;
    m->x_basis.w = 0.f;

    m->y_basis.x = x * y * fsu + z * s;
    m->y_basis.y = y * y * fsu + c;
    m->y_basis.z = y * z * fsu - x * s;
    m->y_basis.w = 0.f;

    m->z_basis.x = x * z * fsu - y * s;
    m->z_basis.y = y * z * fsu + x * s;
    m->z_basis.z = z * z * fsu + c;
    m->z_basis.w = 0.f;

    m->w_basis.x = 0.f;
    m->w_basis.y = 0.f;
    m->w_basis.z = 0.f;
    m->w_basis.w = 1.f;

    // const float c = cosf(rad);
    // const float s = sinf(rad);
    // const float t = 1.0f - c;

    // m->x_basis.x = c + x * x * t;
    // m->x_basis.y = y * x * t - z * s;
    // m->x_basis.z = z * x * t + y * s;
    // m->x_basis.w = 0.f;

    // m->y_basis.x = x * y * t + z * s;
    // m->y_basis.y = c + y * y * t;
    // m->y_basis.z = z * y * t - x * s;
    // m->y_basis.w = 0.f;

    // m->z_basis.x = x * z * t - y * s;
    // m->z_basis.y = y * z * t + x * s;
    // m->z_basis.z = c + z * z * t;
    // m->z_basis.w = 0.f;

    // m->w_basis.x = 0.f;
    // m->w_basis.y = 0.f;
    // m->w_basis.z = 0.f;
    // m->w_basis.w = 1.f;
}

void __cdecl mat4_set_rotate_axis_degrees(pmat4 m, float x, float y, float z, float degrees)
{
    mat4_set_rotate_axis(m, x, y, z, degrees_to_radians(degrees));
}

void __cdecl mat4_set_ortho_projection(pmat4 m, float l, float r, float b, float t, float f, float n)
{
    m->x_basis.x = 2.f / (r - l);
    m->x_basis.y = 0.f;
    m->x_basis.z = 0.f;
    m->x_basis.w = 0.f;

    m->y_basis.x = 0.f;
    m->y_basis.y = 2.f / (t - b);
    m->y_basis.z = 0.f;
    m->y_basis.w = 0.f;

    m->z_basis.x = 0.f;
    m->z_basis.y = 0.f;
    m->z_basis.z = 1.f / (f - n);
    m->z_basis.w = 0.f;

    m->w_basis.x = (l + r) / (l - r);
    m->w_basis.y = (t + b) / (t - b);
    m->w_basis.z = -n / (f - n);
    m->w_basis.w = 1.f;
}

void __cdecl mat4_set_perspective_projection(pmat4 m, float w, float h, float n, float f, float fov)
{
	const float inv_k = 1.f / (w / h);
	const float inv_tangent = 1.f / tanf(fov / 2.f);
	const float dif = f - n;

    m->x_basis.x = inv_k * inv_tangent;
    m->x_basis.y = 0.f;
    m->x_basis.z = 0.f;
    m->x_basis.w = 0.f;

    m->y_basis.x = 0.f;
    m->y_basis.y = inv_tangent;
    m->y_basis.z = 0.f;
    m->y_basis.w = 0.f;

    m->z_basis.x = 0.f;
    m->z_basis.y = 0.f;
    m->z_basis.z = f / dif;
    m->z_basis.w = 1.f;

    m->w_basis.x = 0.f;
    m->w_basis.y = 0.f;
    m->w_basis.z = -f * n / dif;
    m->w_basis.w = 0.f;
}

void __cdecl mat4_set_scale_to_point(pmat4 m, cpvec3 scale, cpvec3 point)
{
    mat4_set_x_basis(m, scale->x, 0.f, 0.f, 0.f);
    mat4_set_y_basis(m, 0.f, scale->y, 0.f, 0.f);
    mat4_set_z_basis(m, 0.f, 0.f, scale->z, 0.f);
    mat4_set_w_basis(m, point->x * (1.f - scale->x), point->y * (1.f - scale->y), point->z * (1.f - scale->z), 1.f);
}

void __cdecl mat4_set_rotate_around_point(pmat4 m, cpvec3 axis, cpvec3 point, float rad)
{
    const float cs = cosf(rad);
	const float sn = sinf(rad);
	const float fsu = 1.f - cs;

    const float a = axis->x * axis->x * fsu + cs;
    const float b = axis->x * axis->y * fsu + axis->z * sn;
    const float c = axis->x * axis->z * fsu - axis->y * sn;

    const float d = axis->x * axis->y * fsu - axis->z * sn;
    const float e = axis->y * axis->y * fsu + cs;
    const float f = axis->y * axis->z * fsu + axis->x * sn;

    const float g = axis->x * axis->z * fsu + axis->y * sn;
    const float h = axis->y * axis->z * fsu - axis->x * sn;
    const float i = axis->z * axis->z * fsu + cs;

    mat4_set_x_basis(m, a, b, c, 0.f);
    mat4_set_y_basis(m, d, e, f, 0.f);
    mat4_set_z_basis(m, g, h, i, 0.f);

    m->w_basis.x = point->x - dot3(a, d, g, point->x, point->y, point->z);
    m->w_basis.y = point->y - dot3(b, e, h, point->x, point->y, point->z);
    m->w_basis.z = point->z - dot3(c, f, i, point->x, point->y, point->z);
    m->w_basis.w = 1.f;
}

int __cdecl mat4_is_equal(cpmat4 m1, cpmat4 m2)
{
    return
        vec4_is_equal(&m1->x_basis, &m2->x_basis) &&
        vec4_is_equal(&m1->y_basis, &m2->y_basis) &&
        vec4_is_equal(&m1->z_basis, &m2->z_basis) &&
        vec4_is_equal(&m1->w_basis, &m2->w_basis);
}

#ifdef __cplusplus
}
#endif
