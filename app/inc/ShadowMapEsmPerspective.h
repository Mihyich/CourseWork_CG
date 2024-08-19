#ifndef SHADOW_MAP_ESM_PERSPECTIVE_H
#define SHADOW_MAP_ESM_PERSPECTIVE_H

#include "Vector3D.h"
#include "Matrix4D.h"

#include "shader.h"
#include "shader_extensions.h"

#include "DepthBufferStruct.h"

#include "winapi_GLextensions.h"

struct ShadowMapEsmPerspectiveRenderData
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

void ShadowMapEsmPerspective(ShadowMapEsmPerspectiveRenderData& data);

void ShadowMapEsmPerspectiveDebug(ShadowMapEsmPerspectiveRenderData& data);


#endif // SHADOW_MAP_ESM_PERSPECTIVE_H