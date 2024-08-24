#ifndef SHADOW_MAP_VSM_ORTHOGONAL_H
#define SHADOW_MAP_VSM_ORTHOGONAL_H

#include "Vector3D.h"
#include "Matrix4D.h"

#include "shader.h"
#include "shader_extensions.h"

#include "DepthBufferStruct.h"

#include "winapi_GLextensions.h"

struct ShadowMapVsmOrthogonalRenderData
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

void ShadowMapVsmOrthogonal(ShadowMapVsmOrthogonalRenderData& data);

void ShadowMapVsmOrthogonalDebug(ShadowMapVsmOrthogonalRenderData& data);


#endif // SHADOW_MAP_VSM_ORTHOGONAL_H