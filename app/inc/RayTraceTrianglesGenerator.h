#ifndef RAY_TRACE_TRIANGLES_GENERATOR_H
#define RAY_TRACE_TRIANGLES_GENERATOR_H

#include <vector>

#include "RayTraceBvhStruct.h"

bool genRayTraceTriangles(
    std::vector<RayTraceTriangle>& triangles,
    std::vector<vec3>& vertices,
    std::vector<vec3>& normales,
    std::vector<unsigned int>& indeces);

#endif // RAY_TRACE_TRIANGLES_GENERATOR_H