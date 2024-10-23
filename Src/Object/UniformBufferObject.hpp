#ifndef __UNIFORM_BUFFER_OBJECT_HPP__
#define __UNIFORM_BUFFER_OBJECT_HPP__

#include <iostream>
#include <vector>
#include <unordered_map>
#include "../../Essantials/glad/glad.h"

class UniformBufferObject;

typedef std::unordered_map<std::string, UniformBufferObject*> UniformBufferMapList;

class UniformBufferObject
{
    private:
        static int bindingPointCounter;
        static UniformBufferMapList uniformBufferObjects;

        unsigned int UBO;
        unsigned int bindingPoint;
        unsigned int prevOffset;

        std::vector<int> containShaderIds;

        UniformBufferObject(size_t size);

    public:
        static void createUniformBufferObject(size_t size, const std::string& name);
        static void addShaderToUniformBuffer(int shaderId, const std::string& bufferName);
        static void setData(const std::string& bufferName, size_t size, size_t offset, void* data);

        static bool DoesConsistTheBuffer(const std::string& bufferName);
};


#endif
