#include "ExpDepthBufferGenerator.h"

bool GenExpDepthFrameBuffer(DepthBufferExp &DB, GLsizei width, GLsizei height)
{
    GLuint depthMap = 0;
    GLuint depthMapFBO = 0;
    GLuint depthRBO = 0;
    float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };

    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, width, height, 0, GL_RED, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glGenFramebuffers(1, &depthMapFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glGenRenderbuffers(1, &depthRBO);
    glBindRenderbuffer(GL_RENDERBUFFER, depthRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRBO);

    if (depthMap && depthMapFBO && depthRBO)
    {
        if (DB.Texture) glDeleteTextures(1, &DB.Texture);
        if (DB.RBO) glDeleteRenderbuffers(1, &DB.FBO);
        if (DB.FBO) glDeleteFramebuffers(1, &DB.FBO);

        DB.Texture = depthMap;
        DB.FBO = depthMapFBO;
        DB.width = width;
        DB.height = height;

        return true;
    }

    if (depthMap) glDeleteTextures(1, &depthMap);
    if (depthRBO) glDeleteRenderbuffers(1, &depthRBO);
    if (depthMapFBO) glDeleteFramebuffers(1, &depthMapFBO);

    return false;
}