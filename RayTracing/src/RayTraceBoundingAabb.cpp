#include "RayTraceBoundingAabb.h"

RayTraceAABB computeAxisAlignBoundingBox(const std::vector<RayTraceTriangle>& triangles)
{
    vec3 min = {__FLT_MAX__, __FLT_MAX__, __FLT_MAX__};
    vec3 max = {-__FLT_MAX__, -__FLT_MAX__, -__FLT_MAX__};

    for (const auto& t : triangles)
    {
       min.x = std::min(min.x, std::min(t.v1.p.x, std::min(t.v2.p.x, t.v3.p.x)));
       min.y = std::min(min.y, std::min(t.v1.p.y, std::min(t.v2.p.y, t.v3.p.y)));
       min.z = std::min(min.z, std::min(t.v1.p.z, std::min(t.v2.p.z, t.v3.p.z)));

       max.x = std::max(max.x, std::max(t.v1.p.x, std::max(t.v2.p.x, t.v3.p.x)));
       max.y = std::max(max.y, std::max(t.v1.p.y, std::max(t.v2.p.y, t.v3.p.y)));
       max.z = std::max(max.z, std::max(t.v1.p.z, std::max(t.v2.p.z, t.v3.p.z)));
    }

    return RayTraceAABB {min, max};
}