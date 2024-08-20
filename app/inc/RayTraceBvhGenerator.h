#ifndef RAY_TRACE_BVH_GENERATOR_H
#define RAY_TRACE_BVH_GENERATOR_H

#include <vector>

#include "RayTraceBvhStruct.h"
#include "Matrix4D.h"

class RayTraceBVHTree
{
public:
    std::vector<RayTraceBVHNode> nodes;
    std::vector<mat4> models;

    void addMesh(const std::vector<RayTraceTriangle>& triangles, const mat4& model);

private:
    int buildBVH(const std::vector<RayTraceTriangle>& triangles, int modelIndex);

    RayTraceBS computeBoundingSphere(const std::vector<RayTraceTriangle>& triangles);

    RayTraceBS computeBoundingSphere(const RayTraceBVHNode& node1, const RayTraceBVHNode& node2);

    void splitTriangles(
        const std::vector<RayTraceTriangle>& triangles,
        std::vector<RayTraceTriangle>& leftTriangles,
        std::vector<RayTraceTriangle>& rightTriangles);

    int buildSubtree(const std::vector<RayTraceTriangle>& triangles, int modelIndex);

    void updateTree(int newSubtreeRoot);
};

#endif // RAY_TRACE_BVH_GENERATOR_H