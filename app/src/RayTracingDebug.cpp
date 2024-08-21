#include "RayTracingDebug.h"

void RayTracingDrawBvh(RayTracingDebugRenderData& data)
{
    glViewport(0, 0, *data.client_width, *data.client_height);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    data.shader->use();

    uniform_matrix4f(data.shader->get_uniform_location("view"), data.view);
    uniform_matrix4f(data.shader->get_uniform_location("projection"), data.projection);

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, *data.VertexSSBO);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, *data.MatrixSSBO);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, *data.BvhSSBO);

    // Вызов отрисовки одной точки, ЧТО ВЫЗОВЕТ ГЕОМЕТРИЧЕСКИЙ ШЕЙДЕР ОДИН РАЗ
    glDrawArrays(GL_POINTS, 0, 1);

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, 0);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, 0);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, 0);
}