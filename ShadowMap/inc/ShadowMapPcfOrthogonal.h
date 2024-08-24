#ifndef SHADOW_MAP_PCF_ORTHOGONAL_H
#define SHADOW_MAP_PCF_ORTHOGONAL_H

#include "Vector3D.h"
#include "Matrix4D.h"

#include "shader.h"
#include "shader_extensions.h"

#include "DepthBufferStruct.h"

#include "winapi_GLextensions.h"

struct ShadowMapPcfOrthogonalRenderData
{
    DepthBuffer* depthBuffer; 
    GLsizei* client_width;
    GLsizei* client_height;

    Shader* shaderDepthPass;
    Shader* shaderRenderPass;
    Shader* shaderDepthDebug;

    mat4* view;
    mat4* projection;

    mat4* lightView;
    mat4* lightProjection;

    GLuint* quadVAO;

    GLuint* planeVAO;
    mat4* planeModel;

    GLuint* modelVAO;
    GLsizei* modelIndexCount;
    mat4* modelModel;
};

void ShadowMapPcfOrthogonal(ShadowMapPcfOrthogonalRenderData& data);

void ShadowMapPcfOrthogonalDebug(ShadowMapPcfOrthogonalRenderData& data);

#endif // SHADOW_MAP_PCF_ORTHOGONAL_H