#ifndef RAY_TRACE_BVH_GENERATOR_H
#define RAY_TRACE_BVH_GENERATOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "Vector3D.h"
#include "Matrix4D.h"

#include "RayTraceTriangleStruct.h"
#include "RayTraceBoundingSphereStruct.h"
#include "RayTraceBoundingAabbStruct.h"
#include "RayTraceBvhStruct.h"

#include "RayTraceBoundingAabb.h"

class RayTraceBVHTree
{
private:
    std::vector<RayTraceVertexTringle> verteces;
    std::vector<mat4> models;
    std::vector<RayTraceBVHNode> nodes;
    
    std::map<std::string, int> meshes;
    int nonameMeshes = 0;

public:

    void addMesh(std::vector<RayTraceTriangle>& triangles, const mat4& model, const std::string& name);

private:
    void updateVerteces(std::vector<RayTraceTriangle>& triangles);

    RayTraceBS computeBoundingSphere(const std::vector<RayTraceTriangle>& triangles) const;

    RayTraceBS computeBoundingSphere(const RayTraceBS& RTBS1, const RayTraceBS& RTBS2) const;

    RayTraceBS computeBoundingSphere(const RayTraceBVHNode& node1, const RayTraceBVHNode& node2) const;

    void splitTriangles(
        const std::vector<RayTraceTriangle>& triangles,
        std::vector<RayTraceTriangle>& leftTriangles,
        std::vector<RayTraceTriangle>& rightTriangles) const;

    int buildSubtree(std::vector<RayTraceBVHNode>& root, const std::vector<RayTraceTriangle>& triangles, int modelIndex) const;

    void addSubTree(const std::vector<RayTraceBVHNode>& root, const std::string& name);

public:
    const std::vector<RayTraceVertexTringle>& getVerteces() const;

    const std::vector<mat4>& getMatrices() const;

    const std::vector<RayTraceBVHNode>& getBvh() const;

    void writeBVHTreeToDot(const std::string& filename) const;

    bool checkLinkRanges() const;

    bool checkCycles() const;

    bool checkBoundingSpheres() const;

private:
    int getNextNodeIndex(int currentIndex) const;
    
    bool isTriangleInsideSphere(const RayTraceVertexTringle& triangle, const RayTraceBS& sphere) const;

    bool isPointInsideSphere(const vec3& point, const RayTraceBS& sphere) const;

    bool isSphereInsideSphere(const RayTraceBS& inner, const RayTraceBS& outer) const;
};

#endif // RAY_TRACE_BVH_GENERATOR_H