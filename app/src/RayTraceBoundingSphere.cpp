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

RayTraceBS computeBoundingSphere(const RayTraceBS& RTBS1, const RayTraceBS& RTBS2)
{
    vec3 dist;
    vec3 center;
    float radius;

    vec3_diff(&RTBS1.c, &RTBS2.c, &dist);
    radius = (vec3_magnitude(&dist) + RTBS1.r + RTBS2.r) / 2.f;

    vec3_sum_scaled_n(&center, 0.5f, 2, &RTBS1.c, &RTBS2.c);

    return RayTraceBS {center, radius};
}

RayTraceBS computeBoundingSphere(const RayTraceBVHNode& node1, const RayTraceBVHNode& node2)
{
    return computeBoundingSphere(node1.BS, node2.BS);
}