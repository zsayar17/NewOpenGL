#include "Object.hpp"

unsigned int Object::objectCounter = 0;
unsigned int Object::usingObject = -1;

Object::Object()
{
    glGenVertexArrays(1, &VAO); // Generate a vertex array object
    glGenBuffers(1, &VBO); // Generate a buffer
    glGenBuffers(1, &EBO); // Generate a buffer

    attributeIndex = 0;
    id = objectCounter;
    objectCounter++;
}

Object::~Object()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Object::bindVBO(int size, void* vertices, int usage)
{
    glBindVertexArray(VAO); // Bind the vertex array object
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind the buffer to the GL_ARRAY_BUFFER target
    glBufferData(GL_ARRAY_BUFFER, size, vertices, usage); // Copy the vertices data into the buffer and set the usage type
}

void Object::bindEBO(int size, void* indices, int usage)
{
    glBindVertexArray(VAO); // Bind the vertex array object
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // Bind the buffer to the GL_ELEMENT_ARRAY_BUFFER target
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, usage); // Copy the indices data into the buffer and set the usage type
}

void Object::bindAttribute(int size, int stride, int offset)
{
    glBindVertexArray(VAO); // Bind the vertex array object
    glVertexAttribPointer(attributeIndex, size, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(offset));
    glEnableVertexAttribArray(attributeIndex++);
}

void Object::use() const
{
    if (usingObject != id)
    {
        glBindVertexArray(VAO);
        usingObject = id;
    }
}
