#ifndef RAY_TRACING_DEBUG_H
#define RAY_TRACING_DEBUG_H

#include "winapi_GLextensions.h"

#include "shader.h"
#include "shader_extensions.h"

#include "Matrix4D.h"

struct RayTracingDebugRenderData
{
    GLuint* VertexSSBO;
    GLuint* MatrixSSBO;
    GLuint* BvhSSBO;

    GLsizei* client_width;
    GLsizei* client_height;

    Shader* shader;

    mat4* view;
    mat4* projection;
};

void RayTracingDrawBvh(RayTracingDebugRenderData& data);

#endif // RAY_TRACING_DEBUG_H