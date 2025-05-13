#include "RayTracingSoft.h"

void TracingPath(RayTracingSoftRenderData& data)
{
    data.shaderRayTracing->use();

    glUniform1i(data.shaderRayTracing->get_uniform_location("curFrameIndex"), data.curFrameIndex);
    glUniform1i(data.shaderRayTracing->get_uniform_location("shadowRayCount"), data.shadowRayCount);
    uniform_vec3f(data.shaderRayTracing->get_uniform_location("viewPos"), data.viewPos);
    uniform_matrix4f(data.shaderRayTracing->get_uniform_location("view"), data.view);
    uniform_matrix4f(data.shaderRayTracing->get_uniform_location("projection"), data.projection);

    // нулевой буфер отведен для UBO с освещением
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, *data.VertexSSBO);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, *data.MatrixSSBO);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, *data.BvhSSBO);
    glBindImageTexture(4, *data.rayTracedTexture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);

    GLuint workGroupSizeX = (*data.texture_width + 15) / 16;
    GLuint workGroupSizeY = (*data.texture_height + 15) / 16;

    glDispatchCompute(workGroupSizeX, workGroupSizeY, 1);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, 0);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, 0);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, 0);
}

void OutputPath(RayTracingSoftRenderData& data)
{
    mat4 quadModel; mat4_set_ordinary(&quadModel);

    glViewport(0, 0, *data.client_width, *data.client_height);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_DEPTH_BUFFER_BIT);

    data.shaderImageOut->use();
    uniform_matrix4f(data.shaderImageOut->get_uniform_location("model"), &quadModel);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, *data.rayTracedTexture);

    glBindVertexArray(*data.quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glBindVertexArray(0);
}

void RayTracingSoft(RayTracingSoftRenderData& data)
{
    if (data.curFrameIndex < data.shadowRayCount)
    {
        TracingPath(data);
        ++data.curFrameIndex;
    }
    
    OutputPath(data);
}