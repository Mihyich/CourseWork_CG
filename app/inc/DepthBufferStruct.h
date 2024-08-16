#ifndef DEPTH_BUFFER_STRUCT_H
#define DEPTH_BUFFER_STRUCT_H

#include "winapi_GLextensions.h"

struct DepthBuffer
{
    GLuint Texture;
    GLuint FBO;
    GLsizei width;
    GLsizei height;
};

#endif // DEPTH_BUFFER_STRUCT_H