#ifndef RAY_TRACING_RENDER_DATA_H
#define RAY_TRACING_RENDER_DATA_H

#include "winapi_GLextensions.h"

#include "shader.h"
#include "shader_extensions.h"

#include "Matrix4D.h"

struct RayTracingDebugRenderData
{
    GLuint* VertexSSBO;
    GLuint* MatrixSSBO;
    GLuint* BvhSSBO;

    int nodeCount;

    GLsizei* client_width;
    GLsizei* client_height;

    Shader* shader;

    mat4* view;
    mat4* projection;
};

struct RayTracingHardRenderData
{
    GLuint* VertexSSBO;
    GLuint* MatrixSSBO;
    GLuint* BvhSSBO;
    GLuint* RayTracedTexture;

    GLsizei* client_width;
    GLsizei* client_height;

    Shader* shaderRayTracing;
    Shader* shaderImageOut;

    vec3* viewPos;
    mat4* view;
    mat4* projection;
};

#endif // RAY_TRACING_RENDER_DATA_H