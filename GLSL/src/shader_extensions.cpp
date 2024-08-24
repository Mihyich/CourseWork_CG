#include "shader_extensions.h"

GLvoid uniform_vec2f(GLint location, const vec2 *vec)
{
    glUniform2f(location, vec->x, vec->y);
}

GLvoid uniform_vec3f(GLint location, const vec3 *vec)
{
    glUniform3f(location, vec->x, vec->y, vec->z);
}

GLvoid uniform_vec4f(GLint location, const vec4 *vec)
{
    glUniform4f(location, vec->x, vec->y, vec->z, vec->w);
}

GLvoid uniform_matrix2f(GLint location, const mat2 *mat)
{
    glUniformMatrix2fv(location, 1, GL_FALSE, (float*)mat);
}

GLvoid uniform_matrix3f(GLint location, const mat3 *mat)
{
    glUniformMatrix3fv(location, 1, GL_FALSE, (float*)mat);
}

GLvoid uniform_matrix4f(GLint location, const mat4 *mat)
{
    glUniformMatrix4fv(location, 1, GL_FALSE, reinterpret_cast<const GLfloat*>(mat));
}
