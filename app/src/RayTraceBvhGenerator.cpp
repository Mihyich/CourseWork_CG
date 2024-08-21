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
    RayTraceVertexTringle RTVT;
    int newStartIndex = verteces.size();

    for (auto& t : triangles)
    {
        RTVT.v1 = t.v1;
        RTVT.v2 = t.v2;
        RTVT.v3 = t.v3;

        verteces.push_back(RTVT);

        t.index += newStartIndex;
    }
}

RayTraceAABB RayTraceBVHTree::computeAxisAlignBoundingBox(const std::vector<RayTraceTriangle>& triangles) const
{
    vec3 min = {__FLT_MAX__, __FLT_MAX__, __FLT_MAX__};
    vec3 max = {-__FLT_MAX__, -__FLT_MAX__, -__FLT_MAX__};

    for (const auto& t : triangles)
    {
       min.x = std::min(min.x, std::min(t.v1.p.x, std::min(t.v2.p.x, t.v3.p.x)));
       min.y = std::min(min.y, std::min(t.v1.p.y, std::min(t.v2.p.y, t.v3.p.y)));
       min.z = std::min(min.z, std::min(t.v1.p.z, std::min(t.v2.p.z, t.v3.p.z)));

       max.x = std::max(max.x, std::max(t.v1.p.x, std::max(t.v2.p.x, t.v3.p.x)));
       max.y = std::max(max.y, std::max(t.v1.p.y, std::max(t.v2.p.y, t.v3.p.y)));
       max.z = std::max(max.z, std::max(t.v1.p.z, std::max(t.v2.p.z, t.v3.p.z)));
    }

    return RayTraceAABB {min, max};
}

RayTraceBS RayTraceBVHTree::computeBoundingSphere(const std::vector<RayTraceTriangle>& triangles) const
{
    RayTraceAABB RTAABB = computeAxisAlignBoundingBox(triangles);

    vec3 center;
    vec3 dist;
    float radius;

    vec3_sum_scaled_n(&center, 0.5f, 2, &RTAABB.min, &RTAABB.max);

    vec3_diff(&RTAABB.max, &RTAABB.min, &dist);
    radius = vec3_magnitude(&dist) / 2.f;

    return RayTraceBS {center, radius};
}

RayTraceBS RayTraceBVHTree::computeBoundingSphere(const RayTraceBS& RTBS1, const RayTraceBS& RTBS2) const
{
    vec3 dist;
    vec3 center;
    float radius;

    vec3_diff(&RTBS1.c, &RTBS2.c, &dist);
    radius = (vec3_magnitude(&dist) + RTBS1.r + RTBS2.r) / 2.f;

    vec3_sum_scaled_n(&center, 0.5f, 2, &RTBS1.c, &RTBS2.c);

    return RayTraceBS {center, radius};
}

RayTraceBS RayTraceBVHTree::computeBoundingSphere(const RayTraceBVHNode& node1, const RayTraceBVHNode& node2) const
{
    return computeBoundingSphere(node1.BS, node2.BS);
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

    int currentIndex;
    int leftChildIndex;
    int rightChildIndex;

    std::vector<RayTraceTriangle> leftTriangles;
    std::vector<RayTraceTriangle> rightTriangles;

    // Листовой узел: содержит только 1 треугольник
    if (triangles.size() == 1)
    {
        RTnode.BS = computeBoundingSphere(triangles);
        RTnode.CI = { -1, -1 }; // Нет потомков
        RTnode.DI = { triangles[0].index, modelIndex };

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
    RTnode.BS = computeBoundingSphere(triangles);
    RTnode.CI = { leftChildIndex, rightChildIndex };
    RTnode.DI = { -1, modelIndex }; // Не листовой узел

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

        // 1. Сместить все существующие узлы на одну позицию вправо
        nodes.insert(nodes.begin(), RayTraceBVHNode{});

        // 2. Обноить индексы смещенных узлов
        for (size_t i = 1; i < nodes.size(); ++i)
        {
            if (nodes[i].CI.left != -1) nodes[i].CI.left += 1;
            if (nodes[i].CI.right != -1) nodes[i].CI.right += 1;
        }

        // 3. Добавить новое поддерево в конец
        newStartIndexForSubTree = nodes.size();
        nodes.insert(nodes.end(), root.begin(), root.end());

        // 4. Обновить индексы в новом поддереве
        for (size_t i = newStartIndexForSubTree; i < nodes.size(); ++i)
        {
            if (nodes[i].CI.left != -1) nodes[i].CI.left += newStartIndexForSubTree;
            if (nodes[i].CI.right != -1) nodes[i].CI.right += newStartIndexForSubTree;
        }

        // 5. Обновить первый узел как новый корень дерева
        nodes[0].BS = { {0.f, 0.f, 0.f}, 0.f }; // Узел не в меше, ограничивающий объем не нужен
        nodes[0].CI.left = 1; // Старый корень теперь смещен вправо
        nodes[0].CI.right = newStartIndexForSubTree; // Корень нового поддерева
        nodes[0].DI.triangle = -1; // это не листовой узел
        nodes[0].DI.matrix = -1; // Узел не в меше, матрица не нужна

        // 6. Обновить ссылочные данные на корневые узлы мешей в массиве
        for (auto& m : meshes) { ++m.second; }

        // 7. Сохранить новый меш
        meshes.insert(std::make_pair(name, newStartIndexForSubTree));
    }
}

const std::vector<RayTraceVertexTringle>& RayTraceBVHTree::getVerteces() const
{
    return this->verteces;
}

const std::vector<mat4>& RayTraceBVHTree::getMatrices() const
{
    return this->models;
}

const std::vector<RayTraceBVHNode>& RayTraceBVHTree::getBvh() const
{
    return this->nodes;
}

void RayTraceBVHTree::writeBVHTreeToDot(const std::string& filename) const
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
             << "\\nCenter: (" << node.BS.c.x << ", " << node.BS.c.y << ", " << node.BS.c.z << ")"
             << "\\nRadius: " << node.BS.r
             << "\\nTriangleIndex: " << node.DI.triangle
             << "\\nModelIndex: " << node.DI.matrix
             << "\"];\n";

        if (node.CI.left != -1)
        {
            file << "  " << i << " -> " << node.CI.left << " [label=\"left\"];\n";
        }
        if (node.CI.right != -1)
        {
            file << "  " << i << " -> " << node.CI.right << " [label=\"right\"];\n";
        }
    }

    file << "}\n";
    file.close();
}