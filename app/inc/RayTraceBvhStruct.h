#ifndef RAY_TRACE_BVH_STRUCT_H
#define RAY_TRACE_BVH_STRUCT_H

#include "Vector3D.h"

// Вершинные данные
struct RayTraceVertex
{
    vec3 p; // Позиция
    vec3 n; // Нормаль
};

// Вершинные данные треугольника
struct RayTraceTriangle
{
    RayTraceVertex v1; // Вершина 1
    RayTraceVertex v2; // Вершина 2
    RayTraceVertex v3; // Вершина 3
    int index; // индекс
};

// Ограничивающая сфера
struct RayTraceBS
{
    vec3 c; // центер
    float r; // радиус
};

// Ограничивающий AABB
struct RayTraceAABB
{
    vec3 min; // Левый нижний ближний угол
    vec3 max; // Правый верхний дальний угол
};

// Bounding Volume Hierarchy
struct RayTraceBVHNode
{
    vec3 center;           // Центр Bounding Sphere
    float radius;          // Радиус Bounding Sphere
    int leftChild;         // Индекс левого дочернего узла в массиве
    int rightChild;        // Индекс правого дочернего узла в массиве
    int triangleIndex;     // Индекс первой вершины треугольника (или -1, если это не лист)
    int modelIndex;        // Индекс матрицы модели для текущего узла (-1, если узел не относится к мешу)
};

#endif // RAY_TRACE_BVH_STRUCT_H