#ifndef SHADOWMAP_H
#define SHADOWMAP_H

#include "Vector3D.h"
#include "Matrix4D.h"

#include "shader.h"
#include "shader_extensions.h"

#include "DepthBufferStruct.h"

#include "winapi_GLextensions.h"

struct ShadowMapPerspectiveRenderData
{
    DepthBuffer* depthBuffer; 
    GLfloat bias;
    GLsizei client_width;
    GLsizei client_height;

    Shader* shaderDepthPass;
    Shader* shaderRenderPass;
    Shader* shaderDepthDebug;

    mat4* view;
    mat4* projection;

    mat4* lightView;
    mat4* lightProjection;

    GLuint quadVAO;
    GLsizei quadVerticesCount;

    GLuint planeVAO;
    GLsizei planeIndexCount;
    mat4* planeModel;

    GLuint modelVAO;
    GLsizei modelIndexCount;
    mat4* modelModel;
};

void ShadowMapPerspective(ShadowMapPerspectiveRenderData& data);

void ShadowMapPerspectiveDebug(ShadowMapPerspectiveRenderData& data);


#endif // SHADOWMAP_H