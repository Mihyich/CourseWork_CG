#include "RayTraceBvhGenerator.h"

void RayTraceBVHTree::addMesh(std::vector<RayTraceTriangle>& triangles, const mat4& model, const std::string& name)
{
    int modelIndex = models.size();
    models.push_back(model);

    updateVerteces(triangles);

    std::vector<RayTraceBVHNode> subTree;
    buildSubtree(subTree, triangles, modelIndex);
    
    std::string resName;
    if (!name.size())
    {
        ++nonameMeshes;
        resName = "Noname mesh";
        resName += std::to_string(nonameMeshes);
    }
    else
    {
        resName = name;
    }

    addSubTree(subTree, resName);
}

void RayTraceBVHTree::updateVerteces(std::vector<RayTraceTriangle>& triangles)
{
    int newStartIndex = verteces.size() / 3;

    for (auto& t : triangles)
    {
        verteces.push_back(t.v1);
        verteces.push_back(t.v2);
        verteces.push_back(t.v3);
        t.index += newStartIndex;
    }
}

RayTraceAABB RayTraceBVHTree::computeAxisAlignBoundingBox(const std::vector<RayTraceTriangle>& triangles) const
{
    vec3 min;
    vec3 max;

    for (const auto& t : triangles)
    {
        vec3_min_n(&min, 3, &t.v1.p, &t.v2.p, &t.v3.p);
        vec3_max_n(&max, 3, &t.v1.p, &t.v2.p, &t.v3.p);
    }

    return RayTraceAABB {min, max};
}

RayTraceBS RayTraceBVHTree::computeBoundingSphere(const std::vector<RayTraceTriangle>& triangles) const
{
    RayTraceAABB RTAABB = computeAxisAlignBoundingBox(triangles);

    vec3 center;
    vec3 dist;
    float radius;

    vec3_sum(&RTAABB.min, &RTAABB.max, &center);
    vec3_scale(&center, 0.5f);

    vec3_diff(&RTAABB.max, &center, &dist);
    radius = vec3_magnitude(&dist);

    return RayTraceBS {center, radius};
}

RayTraceBS RayTraceBVHTree::computeBoundingSphere(const RayTraceBVHNode& node1, const RayTraceBVHNode& node2) const
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
    std::vector<RayTraceTriangle>& rightTriangles) const
{
    // Если меньше 4 треугольников - деление пополам
    if (triangles.size() <= 4)
    {
        size_t mid = triangles.size() / 2;
        leftTriangles.insert(leftTriangles.end(), triangles.begin(), triangles.begin() + mid);
        rightTriangles.insert(rightTriangles.end(), triangles.begin() + mid, triangles.end());
        return;
    }
    else
    {
        // Bounding Box всех треугольников
        RayTraceAABB RTAABB = computeAxisAlignBoundingBox(triangles);

        // Самая длинная ось
        vec3 size;
        int axis = 0;

        // Медиана и среднее значение вдоль выбранной оси
        std::vector<float> centroids;
        float centroid;
        float sum = 0.0f;
        float average;

        std::vector<int> leftIndices, rightIndices;
        float median;

        vec3_diff(&RTAABB.max, &RTAABB.min, &size);
        if (size.y > size.x && size.y > size.z) axis = 1;
        else if (size.z > size.x) axis = 2;

        for (const auto& tri : triangles)
        {
            centroid = (*(&tri.v1.p.x + axis) + *(&tri.v2.p.x + axis) + *(&tri.v3.p.x + axis)) / 3.0f;
            centroids.push_back(centroid);
            sum += centroid;
        }
        average = sum / centroids.size();
        
        median = centroids[triangles.size() / 2];
        
        for (size_t i = 0; i < triangles.size(); ++i)
        {
            if (centroids[i] < median)
                leftIndices.push_back(i);
            else
                rightIndices.push_back(i);
        }

        // Если одно из делений пустое - деление по среднему
        if (leftIndices.empty() || rightIndices.empty())
        {
            leftIndices.clear();
            rightIndices.clear();

            for (size_t i = 0; i < triangles.size(); ++i)
            {
                if (centroids[i] < average)
                    leftIndices.push_back(i);
                else
                    rightIndices.push_back(i);
            }
        }

        // Если одно из делений пустое - деление пополам
        if (leftIndices.empty() || rightIndices.empty()) {
            leftIndices.clear();
            rightIndices.clear();
            size_t mid = triangles.size() / 2;

            for (size_t i = 0; i < triangles.size(); ++i)
            {
                if (i < mid)
                    leftIndices.push_back(i);
                else
                    rightIndices.push_back(i);
            }
        }

        // Заполнение
        for (int index : leftIndices)
        {
            leftTriangles.push_back(triangles[index]);
        }
        for (int index : rightIndices)
        {
            rightTriangles.push_back(triangles[index]);
        }
    }
}

int RayTraceBVHTree::buildSubtree(std::vector<RayTraceBVHNode>& root, const std::vector<RayTraceTriangle>& triangles, int modelIndex) const
{
    RayTraceBVHNode RTnode;
    RayTraceBS RTBS;

    int currentIndex;
    int leftChildIndex;
    int rightChildIndex;

    std::vector<RayTraceTriangle> leftTriangles;
    std::vector<RayTraceTriangle> rightTriangles;

    // Листовой узел: содержит только 1 треугольник
    if (triangles.size() == 1)
    {
        RTBS = computeBoundingSphere(triangles);

        RTnode.center = RTBS.c;
        RTnode.radius = RTBS.r;
        RTnode.leftChild = -1; // Нет потомков
        RTnode.rightChild = -1; // Нет потомков
        RTnode.triangleIndex = triangles[0].index;
        RTnode.modelIndex = modelIndex;

        root.push_back(RTnode);
        return  root.size() - 1;
    }

    // Разделить треугольники
    splitTriangles(triangles, leftTriangles, rightTriangles);

    currentIndex =  root.size();
    root.push_back(RayTraceBVHNode{});

    // Строительство дочерних узлов
    leftChildIndex = buildSubtree(root, leftTriangles, modelIndex);
    rightChildIndex = buildSubtree(root, rightTriangles, modelIndex);

    // Заполнение текущего узла
    RTBS = computeBoundingSphere(triangles);
    RTnode.center = RTBS.c;
    RTnode.radius = RTBS.r;
    RTnode.leftChild = leftChildIndex;
    RTnode.rightChild = rightChildIndex;
    RTnode.triangleIndex = -1; // Не листовой узел
    RTnode.modelIndex = modelIndex;

    root[currentIndex] = RTnode;
    return currentIndex;
}

void RayTraceBVHTree::addSubTree(const std::vector<RayTraceBVHNode>& root, const std::string& name)
{
    // Исходное дерево пустое
    if (nodes.empty())
    {
        // 1. Скопировать поддерево
        nodes = root;

        // 2. Сохранить новый меш
        meshes.insert(std::make_pair(name, 0));
    }
    // В нем присутсвуют другие меши
    else
    {
        int newStartIndexForSubTree; // Новый начальный индекс для добавляемого поддерева в основном массиве
        RayTraceBS RTBS;

        // 1. Сместить все существующие узлы на одну позицию вправо
        nodes.insert(nodes.begin(), RayTraceBVHNode{});

        // 2. Обноить индексы смещенных узлов
        for (size_t i = 1; i < nodes.size(); ++i)
        {
            if (nodes[i].leftChild != -1) nodes[i].leftChild += 1;
            if (nodes[i].rightChild != -1) nodes[i].rightChild += 1;
        }

        // 3. Добавить новое поддерево в конец
        newStartIndexForSubTree = nodes.size();
        nodes.insert(nodes.end(), root.begin(), root.end());

        // 4. Обновить индексы в новом поддереве
        for (size_t i = newStartIndexForSubTree; i < nodes.size(); ++i)
        {
            if (nodes[i].leftChild != -1) nodes[i].leftChild += newStartIndexForSubTree;
            if (nodes[i].rightChild != -1) nodes[i].rightChild += newStartIndexForSubTree;
        }

        // 5. Обновить первый узел как новый корень дерева
        RTBS = computeBoundingSphere(nodes[1], nodes[newStartIndexForSubTree]);
        nodes[0].center = RTBS.c;
        nodes[0].radius = RTBS.r;
        nodes[0].leftChild = 1; // Старый корень теперь смещен вправо
        nodes[0].rightChild = newStartIndexForSubTree; // Корень нового поддерева
        nodes[0].triangleIndex = -1; // это не листовой узел
        nodes[0].modelIndex = -1; // единичная матрица (ну или просто трансформации)

        // 6. Обновить ссылочные данные на корневые узлы мешей в массиве
        for (auto& m : meshes) { ++m.second; }

        // 7. Сохранить новый меш
        meshes.insert(std::make_pair(name, newStartIndexForSubTree));
    }
}

void RayTraceBVHTree::writeBVHTreeToDot(const std::vector<RayTraceBVHNode>& nodes, const std::string& filename)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Error opening file: " << filename << std::endl;
        return;
    }

    file << "digraph BVHTree {\n";
    file << "  node [shape=box];\n";

    for (size_t i = 0; i < nodes.size(); ++i)
    {
        const auto& node = nodes[i];
        file << "  " << i << " [label=\"Node " << i
             << "\\nCenter: (" << node.center.x << ", " << node.center.y << ", " << node.center.z << ")"
             << "\\nRadius: " << node.radius
             << "\\nTriangleIndex: " << node.triangleIndex
             << "\\nModelIndex: " << node.modelIndex
             << "\"];\n";

        if (node.leftChild != -1)
        {
            file << "  " << i << " -> " << node.leftChild << " [label=\"left\"];\n";
        }
        if (node.rightChild != -1)
        {
            file << "  " << i << " -> " << node.rightChild << " [label=\"right\"];\n";
        }
    }

    file << "}\n";
    file.close();
}