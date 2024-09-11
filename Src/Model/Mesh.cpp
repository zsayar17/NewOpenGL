#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material* material)
{
    this->vertices = vertices;
    this->indices = indices;
    this->material = material;

    setupMesh();
}

Mesh::~Mesh()
{

}

void Mesh::setupMesh()
{
    object = new Object();

    object->bindVBO(vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    object->bindEBO(indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    object->bindAttribute(3, sizeof(Vertex), 0);
    object->bindAttribute(3, sizeof(Vertex), offsetof(Vertex, Normal));
    object->bindAttribute(2, sizeof(Vertex), offsetof(Vertex, TexCoords));
}

void Mesh::draw()
{
    object->use();

    if (material != NULL)
        material->activateTextures();

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
