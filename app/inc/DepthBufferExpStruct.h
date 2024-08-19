#ifndef DEPTH_BUFFER_EXP_STRUCT_H
#define DEPTH_BUFFER_EXP_STRUCT_H

#include "winapi_GLextensions.h"

struct DepthBufferExp
{
    GLuint Texture;
    GLuint RBO;
    GLuint FBO;
    GLsizei width;
    GLsizei height;
};

#endif // DEPTH_BUFFER_EXP_STRUCT_H