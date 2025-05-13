#ifndef RAY_TRACE_BOUNDING_AABB_STRUCT_H
#define RAY_TRACE_BOUNDING_AABB_STRUCT_H

#include "Vector3D.h"

// Ограничивающий AABB
struct RayTraceAABB
{
    vec3 min; // Левый нижний ближний угол
    vec3 max; // Правый верхний дальний угол
};

#endif // RAY_TRACE_AABB_BOUNDING_STRUCT_H