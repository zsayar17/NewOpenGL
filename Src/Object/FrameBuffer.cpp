#include "FrameBuffer.hpp"

/*int FrameBuffer::frameBufferCounter = 0;
int FrameBuffer::usingFrameBuffer = -1;

FrameBuffer::FrameBuffer()
{
    frameBufferCounter++;
    id = frameBufferCounter;

    glGenFramebuffers(1, &FBO);
}

FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &FBO);
}

void FrameBuffer::use()
{
    if (usingFrameBuffer != id)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        usingFrameBuffer = id;
    }
}
*/
