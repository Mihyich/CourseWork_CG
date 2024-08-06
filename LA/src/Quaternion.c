#include "Quaternion.h"

#ifdef __cplusplus
extern "C"
{
#endif

void __cdecl quat_set(pquat q, float x, float y, float z, float w)
{
    q->x = x;
    q->y = y;
    q->z = z;
    q->w = w;
}

float __cdecl quat_square_magnitude(cpquat q)
{
    return dot4(
        q->x, q->y, q->z, q->w,
        q->x, q->y, q->z, q->w
    );
}

float __cdecl quat_magnitude(cpquat q)
{
    return sqrtf(
        dot4(
            q->x, q->y, q->z, q->w,
            q->x, q->y, q->z, q->w
        )
    );
}

void __cdecl quat_normalize(pquat q)
{
    float mag = quat_magnitude(q);

    if (!is_equal_zero(mag))
    {
        mag = 1.f / mag;

	    q->x *= mag;
	    q->y *= mag;
	    q->z *= mag;
        q->w *= mag;
    }
}

void __cdecl quat_conjugate(pquat q)
{
    q->x = -q->x;
    q->y = -q->y;
    q->z = -q->z;
}

void __cdecl quat_inverse(pquat q)
{
    float inv_mag = quat_square_magnitude(q);

    if (!is_equal_zero(inv_mag))
    {
        inv_mag = 1.0f / inv_mag;

        q->x *= -inv_mag;
        q->y *= -inv_mag;
        q->z *= -inv_mag;
        q->w *= inv_mag;
    }
}

void __cdecl quat_compose(pquat q1, cpquat q2)
{
    const float w = q1->w;
	const float x = q1->x;
	const float y = q1->y;
	const float z = q1->z;

	q1->x = w * q2->x + x * q2->w + y * q2->z - z * q2->y;
	q1->y = w * q2->y - x * q2->z + y * q2->w + z * q2->x;
	q1->z = w * q2->z + x * q2->y - y * q2->x + z * q2->w;
    q1->w = w * q2->w - x * q2->x - y * q2->y - z * q2->z;
}

void __cdecl quat_compose_res(cpquat q1, cpquat q2, pquat res)
{
    res->x = q1->w * q2->x + q1->x * q2->w + q1->y * q2->z - q1->z * q2->y;
	res->y = q1->w * q2->y - q1->x * q2->z + q1->y * q2->w + q1->z * q2->x;
	res->z = q1->w * q2->z + q1->x * q2->y - q1->y * q2->x + q1->z * q2->w;
    res->w = q1->w * q2->w - q1->x * q2->x - q1->y * q2->y - q1->z * q2->z;
}

void __cdecl quat_set_rotate(pquat q, float x, float y, float z, float rad)
{
    rad *= 0.5f;

	const float s = -sinf(rad);
    const float c = cosf(rad);

    q->x = s * x;
    q->y = s * y;
    q->z = s * z;
    q->w = c;
}

void __cdecl quat_set_rotate_degrees(pquat q, float x, float y, float z, float degrees)
{
    quat_set_rotate(q, x, y, z, degrees_to_radians(degrees));
}

void __cdecl quat_rotate_vec(pvec3 v, cpquat q)
{
    quat quat_res = *q;
	quat quat_vec = (quat){ v->x, v->y, v->z, 0.f };
	quat quat_con = (quat){ -q->x, -q->y, -q->z, q->w };

    quat_compose(&quat_vec, &quat_con);
    quat_compose(&quat_res, &quat_vec);
    *v = (vec3){ quat_res.x, quat_res.y, quat_res.z };
}

#ifdef __cplusplus
}
#endif
