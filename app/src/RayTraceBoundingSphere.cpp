#include "RayTraceBoundingSphere.h"

bool isPointInsideBoundingSphere(const RayTraceBS& RTBS, const vec3& p)
{
    vec3 dist;
    vec3_diff(&RTBS.c, &p, &dist);
    return vec3_square_magnitude(&dist) <= RTBS.r * RTBS.r;
}

bool isTriangleInsideBoundingSphere(const RayTraceBS& RTBS, const RayTraceVertexTringle& triangle)
{
    bool v1 = isPointInsideBoundingSphere(RTBS, triangle.v1.p);
    bool v2 = isPointInsideBoundingSphere(RTBS, triangle.v2.p);
    bool v3 = isPointInsideBoundingSphere(RTBS, triangle.v3.p);

    return v1 && v2 && v3;
}

void expandBoundingSphereToInclude(RayTraceBS& RTBS, const vec3& p)
{
    if (isPointInsideBoundingSphere(RTBS, p))
        return;

    vec3 dist;
    vec3_diff(&RTBS.c, &p, &dist);

    float d = vec3_magnitude(&dist);
    float nRadius = (RTBS.r + d) * 0.5f;
    float k = (nRadius - RTBS.r) / d;

    vec3 direction;
    vec3_diff(&p, &RTBS.c, &direction);
    vec3_scale(&direction, k);
    
    vec3_add(&RTBS.c, &direction);
    RTBS.r = nRadius;
}

RayTraceBS computeBoundingSphere(const std::vector<RayTraceTriangle>& triangles)
{
    if (triangles.empty())
        return RayTraceBS { 0, 0, 0, 0 };

    vec3 initialPoint = triangles[0].v1.p;
    RayTraceBS RTBS = { initialPoint, 0 };

    for (const auto& triangle : triangles)
    {
        expandBoundingSphereToInclude(RTBS, triangle.v1.p);
        expandBoundingSphereToInclude(RTBS, triangle.v2.p);
        expandBoundingSphereToInclude(RTBS, triangle.v3.p);
    }

    return RTBS;
}

bool isBoundingSphereInsideBoundingSphere(const RayTraceBS& outer, const RayTraceBS& inner)
{
    vec3 dist;
    vec3_diff(&inner.c, &outer.c, &dist);
    float dist_square = vec3_square_magnitude(&dist);
    float radius_diff = outer.r - inner.r;
    return dist_square <= radius_diff * radius_diff;
}

RayTraceBS computeBoundingSphere(const RayTraceBS& RTBS1, const RayTraceBS& RTBS2)
{
    vec3 dist;
    vec3_diff(&RTBS1.c, &RTBS2.c, &dist);
    float dist_mag = vec3_magnitude(&dist);

    if (RTBS1.r >= dist_mag + RTBS2.r) return RTBS1;
    if (RTBS2.r >= dist_mag + RTBS1.r) return RTBS2;

    float new_radius = (dist_mag + RTBS1.r + RTBS2.r) / 2.0f;
    float t = (new_radius - RTBS1.r) / dist_mag;

    vec3 new_center;
    vec3_scale(&dist, t);
    vec3_sum(&RTBS2.c, &dist, &new_center);

    return RayTraceBS { new_center, new_radius };
}

RayTraceBS computeBoundingSphere(const RayTraceBVHNode& node1, const RayTraceBVHNode& node2)
{
    return computeBoundingSphere(node1.BS, node2.BS);
}