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

}

void setLightUBO_position(GLuint UBO, const vec3& position)
{

}

void setLightUBO_radius(GLuint UBO, float radius)
{

}

void setLightUBO_color(GLuint UBO, const vec3& color)
{

}

void setLightUBO_intensity(GLuint UBO, float intensity)
{

}

void setLightUBO_direction(GLuint UBO, const vec3& direction)
{

}

void setLightUBO_innerCutoff(GLuint UBO, float innerCutoff)
{

}

void setLightUBO_outerCutoff(GLuint UBO, float outerCutoff)
{

}