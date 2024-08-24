#ifndef RAY_TRACING_HARD_RENDER_DATA_H
#define RAY_TRACING_HARD_RENDER_DATA_H

#include "winapi_GLextensions.h"

#include "shader.h"
#include "shader_extensions.h"

#include "Vector3D.h"
#include "Matrix4D.h"

struct RayTracingHardRenderData
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

    Shader* shaderDebugBvh;
    Shader* shaderRayTracing;
    Shader* shaderImageOut;

    vec3* viewPos;
    mat4* view;
    mat4* projection;

    GLuint* quadVAO;
};

#endif // RAY_TRACING_HARD_RENDER_DATA_H