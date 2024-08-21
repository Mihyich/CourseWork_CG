#include "RayTraceBoundingSphere.h"

RayTraceBS computeBoundingSphere(const std::vector<RayTraceTriangle>& triangles)
{
    RayTraceAABB RTAABB = computeAxisAlignBoundingBox(triangles);

    vec3 center;
    vec3 dist;
    float radius;

    vec3_sum_scaled_n(&center, 0.5f, 2, &RTAABB.min, &RTAABB.max);

    vec3_diff(&RTAABB.max, &RTAABB.min, &dist);
    radius = vec3_magnitude(&dist) / 2.f;

    return RayTraceBS {center, radius};
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