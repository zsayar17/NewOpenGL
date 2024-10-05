#ifndef __FRAMEBUFFER_OBJECT_HPP__
#define __FRAMEBUFFER_OBJECT_HPP__

#include <iostream>
#include <vector>
#include "../Window/Window.hpp"
#include "../Shader/Shader.hpp"
#include "Object.hpp"

class FrameBuffer
{
    private:
        static float quadVertices[];
        static Shader* shaderProgram;

        unsigned int color_texture;
        unsigned int fbo;
        unsigned int rbo;
        Object* object;

    public:
        FrameBuffer(int width, int height);
        ~FrameBuffer();

        void bind();
        void unbind();

        void draw();
};

#endif
