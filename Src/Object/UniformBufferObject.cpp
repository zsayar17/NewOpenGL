#include "UniformBufferObject.hpp"

int UniformBufferObject::bindingPointCounter = 0;
UniformBufferMapList UniformBufferObject::uniformBufferObjects;

UniformBufferObject::UniformBufferObject(size_t size)
{
    bindingPoint = bindingPointCounter++;
    prevOffset = 0;

    glGenBuffers(1, &UBO);
    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindBufferRange(GL_UNIFORM_BUFFER, bindingPoint, UBO, 0, size);
}

void UniformBufferObject::createUniformBufferObject(size_t size, const std::string& name)
{
    if (uniformBufferObjects.find(name) != uniformBufferObjects.end())
    {
        std::cout << "This name is already exist" << std::endl;
        return;
    }

    uniformBufferObjects[name] = new UniformBufferObject(size);
}

void UniformBufferObject::addShaderToUniformBuffer(int shaderId, const std::string& bufferName)
{
    unsigned int uniformBlockIndex;
    UniformBufferMapList::iterator iterator;

    iterator = uniformBufferObjects.find(bufferName);
    if (iterator == uniformBufferObjects.end())
    {
        std::cout << "Buffer name has not implemented yet" << std::endl;
        return;
    }

    std::vector<int>& shaderIdVector = iterator->second->containShaderIds;

    for (size_t i = 0; i < shaderIdVector.size(); i++)
        if (shaderIdVector[i] == shaderId) return;

    uniformBlockIndex = glGetUniformBlockIndex(shaderId, bufferName.c_str());
    glUniformBlockBinding(shaderId, uniformBlockIndex, iterator->second->bindingPoint);
}

void UniformBufferObject::setData(const std::string& bufferName, size_t size, size_t offset, void* data)
{
    UniformBufferMapList::iterator iterator;

    iterator = uniformBufferObjects.find(bufferName);
    if (iterator == uniformBufferObjects.end())
    {
        std::cout << "Buffer name has not implemented yet" << std::endl;
        return;
    }

    glBindBuffer(GL_UNIFORM_BUFFER, iterator->second->UBO);
    glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

bool UniformBufferObject::DoesConsistTheBuffer(const std::string& bufferName)
{
    return uniformBufferObjects.find(bufferName) != uniformBufferObjects.end();
}

