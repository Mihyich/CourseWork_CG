#ifndef SHADER_EXTENSIONS_H
#define SHADER_EXTENSIONS_H

#include <iostream>
#include <string>
#include <gl/gl.h>

#include "shader.h"

#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"

#include "Matrix2D.h"
#include "Matrix3D.h"
#include "Matrix4D.h"

GLvoid uniform_vec2f(GLint location, const vec2 *vec);

GLvoid uniform_vec3f(GLint location, const vec3 *vec);

GLvoid uniform_vec4f(GLint location, const vec4 *vec);

GLvoid uniform_matrix2f(GLint location, const mat2 *mat);

GLvoid uniform_matrix3f(GLint location, const mat3 *mat);

GLvoid uniform_matrix4f(GLint location, const mat4 *mat);

#endif // !SHADER_EXTENSIONS_H

