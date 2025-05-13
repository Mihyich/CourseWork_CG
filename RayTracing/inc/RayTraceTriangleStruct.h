#ifndef RAY_TRACE_TRIANGLE_STRUCT_H
#define RAY_TRACE_TRIANGLE_STRUCT_H

#include "Vector3D.h"

// Вершинные данные
struct RayTraceVertex
{
    vec3 p; // Позиция
    vec3 n; // Нормаль
};

// Вершинные данные треугольника + индекс для генерации BVH
struct RayTraceTriangle
{
    RayTraceVertex v1; // Вершина 1
    RayTraceVertex v2; // Вершина 2
    RayTraceVertex v3; // Вершина 3
    int index; // индекс
};

// Вершинные данные треугольника для использования в шейдере
struct RayTraceVertexTringle
{
    RayTraceVertex v1; // Вершина 1
    RayTraceVertex v2; // Вершина 2
    RayTraceVertex v3; // Вершина 3
};

#endif // RAY_TRACE_TRIANGLE_STRUCT_H