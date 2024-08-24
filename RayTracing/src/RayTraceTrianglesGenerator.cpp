#include "RayTraceTrianglesGenerator.h"

bool genRayTraceTriangles(
    std::vector<RayTraceTriangle>& triangles,
    const std::vector<vec3>& vertices,
    const std::vector<vec3>& normales,
    const std::vector<unsigned int>& indeces)
{
    RayTraceTriangle RTT;

    if (!indeces.size() || indeces.size() % 3)
        return false;

    if (vertices.size() != normales.size())
        return false;

    triangles.clear();

    for (size_t i = 0; i < indeces.size(); i += 3)
    {
        RTT.v1.p = vertices[indeces[i + 0]];
        RTT.v2.p = vertices[indeces[i + 1]];
        RTT.v3.p = vertices[indeces[i + 2]];

        RTT.v1.n = normales[indeces[i + 0]];
        RTT.v2.n = normales[indeces[i + 1]];
        RTT.v3.n = normales[indeces[i + 2]];

        RTT.index = i / 3;

        triangles.push_back(RTT);
    }

    return true;
}