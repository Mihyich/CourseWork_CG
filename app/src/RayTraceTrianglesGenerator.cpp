#include "RayTraceTrianglesGenerator.h"

bool genRayTraceTriangles(
    std::vector<RayTraceTriangle>& triangles,
    std::vector<vec3>& vertices,
    std::vector<vec3>& normales,
    std::vector<unsigned int>& indeces)
{
    unsigned int index;
    RayTraceTriangle RTT;

    if (!indeces.size() || indeces.size() % 3)
        return false;

    if (vertices.size() != normales.size())
        return false;

    triangles.clear();

    for (size_t i = 0; i < indeces.size(); i += 3)
    {
        index = indeces[i];

        RTT.v1.p = vertices[index];
        RTT.v2.p = vertices[index + 1];
        RTT.v3.p = vertices[index + 2];

        RTT.v1.n = normales[index];
        RTT.v2.n = normales[index + 1];
        RTT.v3.n = normales[index + 2];

        RTT.index = i / 3;

        triangles.push_back(RTT);
    }

    return true;
}