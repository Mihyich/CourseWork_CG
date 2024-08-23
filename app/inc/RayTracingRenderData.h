#ifndef RAY_TRACING_RENDER_DATA_H
#define RAY_TRACING_RENDER_DATA_H

#include "winapi_GLextensions.h"

#include "shader.h"
#include "shader_extensions.h"

#include "Matrix4D.h"

struct RayTracingRenderData
{
    GLuint* VertexSSBO;
    GLuint* MatrixSSBO;
    GLuint* BvhSSBO;
    GLuint* rayTracedTexture;

    int nodeCount;

    GLsizei* texture_width;
    GLsizei* texture_height;

    GLsizei* client_width;
    GLsizei* client_height;

    Shader* shader;

    mat4* view;
    mat4* projection;
};

#endif // RAY_TRACING_RENDER_DATA_H