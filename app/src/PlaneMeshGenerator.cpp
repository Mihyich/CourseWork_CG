#include "PlaneMeshGenerator.h"

void genPlaneMeshVertices(std::vector<vec3>& vertices, float size)
{
    vertices.clear();

    vertices = {
        { -0.5f * size, 0.0f, -0.5f * size },
        {  0.5f * size, 0.0f, -0.5f * size },
        {  0.5f * size, 0.0f,  0.5f * size },
        { -0.5f * size, 0.0f,  0.5f * size }
    };
}

void genPlaneMeshNormales(std::vector<vec3>& normales)
{
    normales.clear();

    normales = {
        { 0.0f, 1.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f },
    };
}

void genPlaneMeshIndeces(std::vector<unsigned int>& indeces)
{
    indeces.clear();

    indeces = {
        0, 1, 2,
        2, 3, 0
    };
}

void genPlaneMeshVNI(std::vector<vec3>& vertices, std::vector<vec3>& normales, std::vector<unsigned int>& indeces, float size)
{
    genPlaneMeshVertices(vertices, size);
    genPlaneMeshNormales(normales);
    genPlaneMeshIndeces(indeces);
}

bool GenPlaneMesh(GLuint &planeVAO, GLuint &planeVBO, GLuint &planeEBO, float size)
{   
    float planeVertices[] = {
        // Позиции                         // Нормали
        -0.5f * size, 0.0f, -0.5f * size,  0.0f, 1.0f, 0.0f,
         0.5f * size, 0.0f, -0.5f * size,  0.0f, 1.0f, 0.0f,
         0.5f * size, 0.0f,  0.5f * size,  0.0f, 1.0f, 0.0f,
        -0.5f * size, 0.0f,  0.5f * size,  0.0f, 1.0f, 0.0f,
    };

    unsigned int planeIndices[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLuint VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(planeIndices), planeIndices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    if (VAO && VBO && EBO)
    {
        if (planeVAO) glDeleteVertexArrays(1, &planeVAO);
        if (planeVBO) glDeleteBuffers(1, &planeVBO);
        if (planeEBO) glDeleteBuffers(1, &planeEBO);

        planeVAO = VAO;
        planeVBO = VBO;
        planeEBO = EBO;

        return true;
    }

    return false;
}