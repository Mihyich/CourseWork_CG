#ifndef RAY_TRACE_BOUNDING_SPHERE_H
#define RAY_TRACE_BOUNDING_SPHERE_H

#include <vector>

#include "RayTraceBoundingSphereStruct.h"
#include "RayTraceBoundingAabbStruct.h"
#include "RayTraceTriangleStruct.h"
#include "RayTraceBvhStruct.h"

#include "RayTraceBoundingAabb.h"

bool isPointInsideBoundingSphere(const RayTraceBS& RTBS, const vec3& p);

bool isTriangleInsideBoundingSphere(const RayTraceBS& RTBS, const RayTraceVertexTringle& triangle);

void expandBoundingSphereToInclude(RayTraceBS& RTBS, const vec3& p);

RayTraceBS computeBoundingSphere(const std::vector<RayTraceTriangle>& triangles);

RayTraceBS computeBoundingSphere(const RayTraceBS& RTBS1, const RayTraceBS& RTBS2);

RayTraceBS computeBoundingSphere(const RayTraceBVHNode& node1, const RayTraceBVHNode& node2);

#endif // RAY_TRACE_BOUNDING_SPHERE_H