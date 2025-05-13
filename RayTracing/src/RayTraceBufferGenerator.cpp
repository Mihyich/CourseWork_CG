#include "RayTraceBufferGenerator.h"

bool genRayTraceVertexSSBO(const std::vector<RayTraceVertexTringle>& verteces, GLuint& SSBO)
{
    GLuint nSSBO = 0;
    glGenBuffers(1, &nSSBO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, nSSBO);
    glBufferData(GL_SHADER_STORAGE_BUFFER, verteces.size() * sizeof(RayTraceVertexTringle), verteces.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    if (nSSBO)
    {
        if (SSBO) glDeleteBuffers(1, &SSBO);

        SSBO = nSSBO;

        return true;
    }

    return false;
}

bool genRayTraceMatrixSSBO(const std::vector<mat4>& matrices, GLuint& SSBO)
{
    GLuint nSSBO = 0;
    glGenBuffers(1, &nSSBO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, nSSBO);
    glBufferData(GL_SHADER_STORAGE_BUFFER, matrices.size() * sizeof(mat4), matrices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    if (nSSBO)
    {
        if (SSBO) glDeleteBuffers(1, &SSBO);

        SSBO = nSSBO;

        return true;
    }

    return false;
}

bool genRayTraceBvhSSBO(const std::vector<RayTraceBVHNode>& bvh, GLuint& SSBO)
{
    GLuint nSSBO = 0;
    glGenBuffers(1, &nSSBO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, nSSBO);
    glBufferData(GL_SHADER_STORAGE_BUFFER, bvh.size() * sizeof(RayTraceBVHNode), bvh.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    if (nSSBO)
    {
        if (SSBO) glDeleteBuffers(1, &SSBO);

        SSBO = nSSBO;

        return true;
    }

    return false;
}