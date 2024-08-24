#ifndef RAY_TRACE_BOUNDING_AABB_H
#define RAY_TRACE_BOUNDING_AABB_H

#include <vector>

#include "RayTraceBoundingAabbStruct.h"
#include "RayTraceTriangleStruct.h"

RayTraceAABB computeAxisAlignBoundingBox(const std::vector<RayTraceTriangle>& triangles);

#endif // RAY_TRACE_BOUNDING_AABB_H