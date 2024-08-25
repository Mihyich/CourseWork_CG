#include "ShadowMapPcfPerspective.h"

void DepthPass(ShadowMapPcfRenderData& data)
{
    glViewport(0, 0, data.depthBuffer->width, data.depthBuffer->height);

    glBindFramebuffer(GL_FRAMEBUFFER, data.depthBuffer->FBO);
    glClear(GL_DEPTH_BUFFER_BIT);

    data.shaderDepthPass->use();
    uniform_matrix4f(data.shaderDepthPass->get_uniform_location("view"), data.lightView);
    uniform_matrix4f(data.shaderDepthPass->get_uniform_location("projection"), data.lightProjection);

    glBindVertexArray(*data.modelVAO);
    uniform_matrix4f(data.shaderDepthPass->get_uniform_location("model"), data.modelModel);
    glDrawElements(GL_TRIANGLES, *data.modelIndexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void RenderPass(ShadowMapPcfRenderData& data)
{
    glViewport(0, 0, *data.client_width, *data.client_height);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    data.shaderRenderPass->use();
    uniform_matrix4f(data.shaderRenderPass->get_uniform_location("view"), data.view);
    uniform_matrix4f(data.shaderRenderPass->get_uniform_location("projection"), data.projection);
    uniform_matrix4f(data.shaderRenderPass->get_uniform_location("lightView"), data.lightView);
    uniform_matrix4f(data.shaderRenderPass->get_uniform_location("lightProjection"), data.lightProjection);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, data.depthBuffer->Texture);

    glBindVertexArray(*data.modelVAO);
    uniform_matrix4f(data.shaderRenderPass->get_uniform_location("model"), data.modelModel);
    glDrawElements(GL_TRIANGLES, *data.modelIndexCount, GL_UNSIGNED_INT, 0);

    glBindVertexArray(*data.planeVAO);
    uniform_matrix4f(data.shaderRenderPass->get_uniform_location("model"), data.planeModel);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void DebugPass(ShadowMapPcfRenderData& data)
{
    mat4 quadModel; mat4_set_ordinary(&quadModel);

    glViewport(0, 0, *data.client_width, *data.client_height);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    data.shaderDepthDebug->use();
    uniform_matrix4f(data.shaderDepthDebug->get_uniform_location("model"), &quadModel);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, data.depthBuffer->Texture);

    glBindVertexArray(*data.quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glBindVertexArray(0);
}

void ShadowMapPcfPerspective(ShadowMapPcfRenderData& data)
{
    DepthPass(data);
    RenderPass(data);
}

void ShadowMapPcfPerspectiveDebug(ShadowMapPcfRenderData& data)
{
    DepthPass(data);
    DebugPass(data);
}