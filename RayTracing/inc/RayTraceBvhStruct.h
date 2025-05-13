#ifndef RAY_TRACE_BVH_STRUCT_H
#define RAY_TRACE_BVH_STRUCT_H

#include "Vector3D.h"
#include "RayTraceBoundingSphereStruct.h"

// Индексы дочерних узлов дерева в массиве
struct RayTraceChildIndex
{
    int left;  // Индекс левого дочернего узла в массиве
    int right; // Индекс правого дочернего узла в массиве
};

// Индексы треугольников и матриц в отдельных массивах
struct RayTraceDataIndex
{
    int triangle; // Индекс треугольника (или -1, если это не лист)
    int matrix;   // Индекс матрицы (-1, если узел не относится к мешу)
};

// Bounding Volume Hierarchy
struct RayTraceBVHNode
{
    RayTraceBS BS;         // Ограничивающая сфера
    RayTraceChildIndex CI; // Дочерние индексы
    RayTraceDataIndex DI;  // Индексы данных
};

#endif // RAY_TRACE_BVH_STRUCT_H