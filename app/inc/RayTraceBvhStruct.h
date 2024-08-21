#ifndef RAY_TRACE_BVH_STRUCT_H
#define RAY_TRACE_BVH_STRUCT_H

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
    RayTraceBS BS;         // Ограничиавющая сфера
    RayTraceChildIndex CI; // Дочерние индексы
    RayTraceDataIndex DI;  // Индексы данных
};

#endif // RAY_TRACE_BVH_STRUCT_H