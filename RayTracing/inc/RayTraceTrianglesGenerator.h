#ifndef RAY_TRACE_TRIANGLES_GENERATOR_H
#define RAY_TRACE_TRIANGLES_GENERATOR_H

#include <vector>

#include "RayTraceTriangleStruct.h"
#include "RayTraceBvhStruct.h"

bool genRayTraceTriangles(
    std::vector<RayTraceTriangle>& triangles,
    const std::vector<vec3>& vertices,
    const std::vector<vec3>& normales,
    const std::vector<unsigned int>& indeces);

#endif // RAY_TRACE_TRIANGLES_GENERATOR_H