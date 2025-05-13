#include "Light.h"

bool genLightUBO(const Light &light, GLuint& lightUBO)
{
    GLuint UBO = 0;

    glGenBuffers(1, &UBO);
    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(Light), &light, GL_STATIC_DRAW);

    if (UBO)
    {
        if (lightUBO) glDeleteBuffers(1, &lightUBO);

        lightUBO = UBO;

        return true;
    }

    return false;
}

void setLightUBO_type(GLuint UBO, int type)
{
    if (!UBO)
        return;

    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferSubData(GL_UNIFORM_BUFFER, 64, 4, &type); 
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glMemoryBarrier(GL_UNIFORM_BARRIER_BIT);
}

void setLightUBO_position(GLuint UBO, const vec3& position)
{
    if (!UBO)
        return;

    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, 12, &position); 
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glMemoryBarrier(GL_UNIFORM_BARRIER_BIT);
}

void setLightUBO_direction(GLuint UBO, const vec3& direction)
{
    if (!UBO)
        return;

    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferSubData(GL_UNIFORM_BUFFER, 16, 12, &direction); 
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glMemoryBarrier(GL_UNIFORM_BARRIER_BIT);
}

void setLightUBO_color(GLuint UBO, const vec3& color)
{
    if (!UBO)
        return;

    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferSubData(GL_UNIFORM_BUFFER, 32, 12, &color); 
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glMemoryBarrier(GL_UNIFORM_BARRIER_BIT);
}

void setLightUBO_radius(GLuint UBO, float radius)
{
    if (!UBO)
        return;

    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferSubData(GL_UNIFORM_BUFFER, 48, 4, &radius); 
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glMemoryBarrier(GL_UNIFORM_BARRIER_BIT);
}

void setLightUBO_intensity(GLuint UBO, float intensity)
{
    if (!UBO)
        return;

    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferSubData(GL_UNIFORM_BUFFER, 52, 4, &intensity); 
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glMemoryBarrier(GL_UNIFORM_BARRIER_BIT);
}

void setLightUBO_innerCutoff(GLuint UBO, float innerCutoff)
{
    if (!UBO)
        return;

    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferSubData(GL_UNIFORM_BUFFER, 56, 4, &innerCutoff); 
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glMemoryBarrier(GL_UNIFORM_BARRIER_BIT);
}

void setLightUBO_outerCutoff(GLuint UBO, float outerCutoff)
{
    if (!UBO)
        return;

    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferSubData(GL_UNIFORM_BUFFER, 60, 4, &outerCutoff); 
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glMemoryBarrier(GL_UNIFORM_BARRIER_BIT);
}