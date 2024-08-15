#ifndef DEPTH_BUFFER_GENERATOR_H
#define DEPTH_BUFFER_GENERATOR_H

#include "winapi_GLextensions.h"

struct DepthBuffer
{
    GLuint Texture;
    GLuint FBO;
    GLsizei width;
    GLsizei height;
};

bool GenDepthFrameBuffer(DepthBuffer &DB, GLsizei width, GLsizei height);

#endif // DEPTH_BUFFER_GENERATOR_H