#include "RayTracingDebug.h"

void genPointVBO(GLuint& VAO, GLuint& VBO)
{
    vec3 pos = {0, 0, 0};

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(pos), &pos.x, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    glBindVertexArray(0);
}

int calcMaxEmitCount(int outComponentCount)
{
    GLint totalOutComponentCount;
    glGetIntegerv(GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS, &totalOutComponentCount);
    return totalOutComponentCount / outComponentCount;
}

void RayTracingDrawBvh(RayTracingRenderData& data)
{
    // В любом случае чтобы запустить шеометрический шейдер, нужно вызвать отрисовку хотя бы точки
    static GLuint pointVAO = 0;
    static GLuint pointVBO = 0;
    if (!pointVBO) genPointVBO(pointVAO, pointVBO);

    const int outComponentCount = 7; // кол-во компонентов на вершину в геом. шейдере на 1 emit
    static int MaxEmitCount = 0; // максимально возможное кол-во emit при текущем кол-ве emit

    if (!MaxEmitCount) MaxEmitCount = calcMaxEmitCount(outComponentCount);

    int enableNodeBatch = MaxEmitCount / 39;
    int completeBatch = data.nodeCount / enableNodeBatch;
    int extraNodeCount = data.nodeCount - completeBatch * enableNodeBatch;
    int startNodeIndex = 0;
    int endNodeIndex = 0;

    glViewport(0, 0, *data.client_width, *data.client_height);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    data.shader->use();

    uniform_matrix4f(data.shader->get_uniform_location("view"), data.view);
    uniform_matrix4f(data.shader->get_uniform_location("projection"), data.projection);

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, *data.VertexSSBO);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, *data.MatrixSSBO);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, *data.BvhSSBO);

    glBindVertexArray(pointVAO);
    for (int i = 0; i < completeBatch; ++i)
    {
        startNodeIndex = i * enableNodeBatch;
        endNodeIndex = startNodeIndex + enableNodeBatch - 1;

        glUniform1i(data.shader->get_uniform_location("startNodeIndex"), startNodeIndex);
        glUniform1i(data.shader->get_uniform_location("endNodeIndex"), endNodeIndex);

        // Вызов отрисовки одной точки, ЧТО ВЫЗОВЕТ ГЕОМЕТРИЧЕСКИЙ ШЕЙДЕР ОДИН РАЗ
        glDrawArrays(GL_POINTS, 0, 1);
    }

    if (extraNodeCount > 0)
    {
        startNodeIndex = data.nodeCount - extraNodeCount;
        endNodeIndex = data.nodeCount - 1;

        glUniform1i(data.shader->get_uniform_location("startNodeIndex"), startNodeIndex);
        glUniform1i(data.shader->get_uniform_location("endNodeIndex"), endNodeIndex);

        // Вызов отрисовки одной точки, ЧТО ВЫЗОВЕТ ГЕОМЕТРИЧЕСКИЙ ШЕЙДЕР ОДИН РАЗ
        glDrawArrays(GL_POINTS, 0, 1);
    }

    glBindVertexArray(0);

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, 0);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, 0);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, 0);
}