#ifndef LIGHT_H
#define LIGHT_H

#include "LightStruct.h"

#include "winapi_GLextensions.h"

bool genLightUBO(const Light &light, GLuint& lightUBO);

void setLightUBO_type(GLuint UBO, int type);

void setLightUBO_position(GLuint UBO, const vec3& position);

void setLightUBO_radius(GLuint UBO, float radius);

void setLightUBO_color(GLuint UBO, const vec3& color);

void setLightUBO_intensity(GLuint UBO, float intensity);

void setLightUBO_direction(GLuint UBO, const vec3& direction);

void setLightUBO_innerCutoff(GLuint UBO, float innerCutoff);

void setLightUBO_outerCutoff(GLuint UBO, float outerCutoff);

#endif // LIGHT_H
