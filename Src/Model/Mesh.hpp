#ifndef __MESH_HPP__
#define __MESH_HPP__

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "../../Essantials/glad/glad.h"
#include "../../Essantials/Glfw/include/GLFW/glfw3.h"
#include "../Object/Object.hpp"
#include "../Light/Light.hpp"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Mesh
{
    public:
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material* material);
        ~Mesh();
        void draw();
        void drawInstanced(int count);

        const Object& getObject() const;

    protected:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        Object* object;
        Material* material;

    private:
        void setupMesh();
};

#endif
