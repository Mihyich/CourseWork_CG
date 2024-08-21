#version 460 core

layout(points) in;                             // Входной тип примитивов - точки (По факту только 1, и то она никак не используется)
layout(triangle_strip, max_vertices = 3) out;  // Выходной тип примитивов - треугольники

// Вершинные данные
struct RayTraceVertex
{
    vec3 p; // Позиция
    vec3 n; // Нормаль
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

layout(std430, binding = 0) buffer Triangles
{
    RayTraceVertexTringle triangles[];
};

layout(std430, binding = 1) buffer Matrices
{
    mat4 matrices[];
};

layout(std430, binding = 2) buffer Bvh
{
    RayTraceBVHNode bvh[];
};

uniform mat4 view;
uniform mat4 projection;

// Генерация примитива - треугольник
void genPrimitiveTriangle(RayTraceVertexTringle triangle)
{
    vec4 v1 = projection * view * vec4(triangle.v1.p, 1.0);
    vec4 v2 = projection * view * vec4(triangle.v2.p, 1.0);
    vec4 v3 = projection * view * vec4(triangle.v3.p, 1.0);

    gl_Position = v1;
    EmitVertex();
    
    gl_Position = v2;
    EmitVertex();
    
    gl_Position = v3;
    EmitVertex();
    
    EndPrimitive();
}

void main()
{
    int numBvhNodes = bvh.length();
    RayTraceBVHNode node;

    // Обход элементов дерева через по массиву напрямую
    for (int i = 0; i < numBvhNodes; ++i)
    {
        node = bvh[i];

        // Нужно нарисовать ограничивающий объем
        if (node.DI.matrix > 0)
        {
            // Рисование сферы...
        }

        // Нужно нарисовать треугольник
        if (node.DI.triangle > 0)
        {
            genPrimitiveTriangle(triangles[node.DI.triangle]);
        }
    }
}