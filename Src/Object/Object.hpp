#pragma once

#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

#include <iostream>
#include <vector>
#include "../../Essantials/glad/glad.h"

class Object
{
    private:
        static bool flipVertically;

        unsigned int VBO;
        unsigned int VAO;
        unsigned int EBO;
        int attributeIndex;

        static unsigned int objectCounter;
        static unsigned int usingObject;
        unsigned int id;

    public:
        Object();
        ~Object();

        void bindVBO(int size, void* vertices, int usage);
        void bindEBO(int size, void* indices, int usage);
        void bindAttribute(int size, int stride, int offset);
        void use();
};

#endif
