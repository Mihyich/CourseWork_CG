#include "RayTraceBvhGenerator.h"

void RayTraceBVHTree::addMesh(const std::vector<RayTraceTriangle>& triangles, const mat4& model)
 {
    int modelIndex = models.size();
    models.push_back(model);

    int subtreeRoot = buildBVH(triangles, modelIndex);
    updateTree(subtreeRoot);
}

int RayTraceBVHTree::buildBVH(const std::vector<RayTraceTriangle>& triangles, int modelIndex)
{
    return buildSubtree(triangles, modelIndex);
}

RayTraceBS RayTraceBVHTree::computeBoundingSphere(const std::vector<RayTraceTriangle>& triangles)
{
    vec3 minPos;
    vec3 maxPos;

    vec3 center;
    vec3 dist;
    float radius;

    for (const auto& t : triangles)
    {
        vec3_min_n(&minPos, 3, &t.v1.p, &t.v2.p, &t.v3.p);
        vec3_max_n(&maxPos, 3, &t.v1.p, &t.v2.p, &t.v3.p);
    }

    vec3_sum(&minPos, &maxPos, &center);
    vec3_scale(&center, 0.5f);

    vec3_diff(&maxPos, &center, &dist);
    radius = vec3_magnitude(&dist);

    return {center, radius};
}

RayTraceBS RayTraceBVHTree::computeBoundingSphere(const RayTraceBVHNode& node1, const RayTraceBVHNode& node2)
{
    vec3 center;
    vec3 dist;
    float radius;

    vec3_sum(&node1.center, &node2.center, &center);
    vec3_scale(&center, 0.5f);
    vec3_diff(&center, &node1.center, &dist);
    radius = vec3_magnitude(&dist) + node1.radius;

    return RayTraceBS {center, radius};
}

void RayTraceBVHTree::splitTriangles(
    const std::vector<RayTraceTriangle>& triangles,
    std::vector<RayTraceTriangle>& leftTriangles,
    std::vector<RayTraceTriangle>& rightTriangles)
{
    // Простейшее разделение: по оси X (можно улучшить)
    std::vector<vec3> centers;
    vec3 center;
    float median = 0.0f;

    for (const auto& tri : triangles)
    {
        vec3_sum_scaled_n(&center, 1.f / 3.f, 3, &tri.v1.p, &tri.v2.p, &tri.v3.p);
        centers.push_back(center);
    }

    for (const auto& center : centers)
    {
        median += center.x;
    }
    median /= centers.size();

    for (size_t i = 0; i < triangles.size(); ++i)
    {
        if (centers[i].x < median)
        {
            leftTriangles.push_back(triangles[i]);
        }
        else
        {
            rightTriangles.push_back(triangles[i]);
        }
    }
}

int RayTraceBVHTree::buildSubtree(const std::vector<RayTraceTriangle>& triangles, int modelIndex)
{
    RayTraceBVHNode RTnode;
    RayTraceBS RTBS;

    int currentIndex;
    int leftChildIndex;
    int rightChildIndex;

    std::vector<RayTraceTriangle> leftTriangles;
    std::vector<RayTraceTriangle> rightTriangles;

    // Листовой узел: содержит треугольник
    if (triangles.size() == 1)
    {
        RTBS = computeBoundingSphere(triangles);

        RTnode.center = RTBS.c;
        RTnode.radius = RTBS.r;
        // RTnode.triangleIndex = triangles[0].index;
        RTnode.modelIndex = modelIndex;

        nodes.push_back(RTnode);
        return nodes.size() - 1;
    }

    // Разделить треугольники на две группы (например, по медиане)
    splitTriangles(triangles, leftTriangles, rightTriangles);

    currentIndex = nodes.size();
    nodes.push_back(RayTraceBVHNode{});

    // Рекурсивно строим дочерние узлы
    leftChildIndex = buildSubtree(leftTriangles, modelIndex);
    rightChildIndex = buildSubtree(rightTriangles, modelIndex);

    // Заполняем текущий узел
    RTBS = computeBoundingSphere(triangles);
    RTnode.leftChild = leftChildIndex;
    RTnode.rightChild = rightChildIndex;
    RTnode.center = RTBS.c;
    RTnode.radius = RTBS.r;
    RTnode.triangleIndex = -1; // Указываем, что это не листовой узел

    nodes[currentIndex] = RTnode;
    return currentIndex;
}

void RayTraceBVHTree::updateTree(int newSubtreeRoot)
{
    // Если дерево пустое, просто добавляем новый поддерево как корень
    if (nodes.empty())
    {
        nodes.push_back(nodes[newSubtreeRoot]);
    }
    // Если дерево не пустое, объединяем новое поддерево с существующим
    else
    {
        int oldRoot = 0; // Текущий корень дерева
        int newRoot = nodes.size();
        nodes.push_back(RayTraceBVHNode{});

        // Определение нового Bounding Sphere для нового корня
        RayTraceBVHNode newNode;
        newNode.leftChild = oldRoot;
        newNode.rightChild = newSubtreeRoot;

        RayTraceBS newSphere = computeBoundingSphere(nodes[oldRoot], nodes[newSubtreeRoot]);
        newNode.center = newSphere.c;
        newNode.radius = newSphere.r;
        newNode.triangleIndex = -1;

        nodes[newRoot] = newNode;
    }
}