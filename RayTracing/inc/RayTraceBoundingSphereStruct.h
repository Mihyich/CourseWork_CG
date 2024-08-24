#ifndef RAY_TRACE_BOUNDING_SPHERE_STRUCT_H
#define RAY_TRACE_BOUNDING_SPHERE_STRUCT_H

#include "Vector3D.h"

// Ограничивающая сфера
struct RayTraceBS
{
    vec3 c; // центер
    float r; // радиус
};

#endif // RAY_TRACE_BOUNDING_SPHERE_STRUCT_H