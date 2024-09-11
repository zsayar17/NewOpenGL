#include "Cube.hpp"
#include "../Light/Light.hpp"


Object* Cube::mainObject = NULL;

Cube::Cube()
{
    material = NULL;

    if (!mainObject) {
        mainObject = new Object();
        createCube();
    }

    object = mainObject;
}

Cube::~Cube()
{

}

void Cube::bindObject(Object *object)
{
    this->object = object;
}

void Cube::createCube()
{
    float vertices[] = {
    // Back face
     0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f,  1.0f, 1.0f, // top-right
     0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f,  1.0f, 0.0f, // bottom-right
    -0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f,  0.0f, 0.0f, // Bottom-left
    -0.5f, -0.5f, -0.5f, 0.f, 0.f, -1.f,  0.0f, 0.0f, // bottom-left
    -0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f,  0.0f, 1.0f, // top-left
     0.5f,  0.5f, -0.5f, 0.f, 0.f, -1.f,  1.0f, 1.0f, // top-right
    // Front face
     0.5f, -0.5f,  0.5f, 0.f, 0.f, 1.f,  1.0f, 0.0f, // bottom-right
     0.5f,  0.5f,  0.5f, 0.f, 0.f, 1.f,  1.0f, 1.0f, // top-right
    -0.5f, -0.5f,  0.5f, 0.f, 0.f, 1.f,  0.0f, 0.0f, // bottom-left
    -0.5f,  0.5f,  0.5f, 0.f, 0.f, 1.f,  0.0f, 1.0f, // top-left
    -0.5f, -0.5f,  0.5f, 0.f, 0.f, 1.f,  0.0f, 0.0f, // bottom-left
     0.5f,  0.5f,  0.5f, 0.f, 0.f, 1.f,  1.0f, 1.0f, // top-right
    // Left face
    -0.5f,  0.5f, -0.5f, -1.f, 0.f, 0.f,  1.0f, 1.0f, // top-left
    -0.5f, -0.5f, -0.5f, -1.f, 0.f, 0.f,  0.0f, 1.0f, // bottom-left
    -0.5f,  0.5f,  0.5f, -1.f, 0.f, 0.f,  1.0f, 0.0f, // top-right
    -0.5f, -0.5f,  0.5f, -1.f, 0.f, 0.f,  0.0f, 0.0f, // bottom-right
    -0.5f,  0.5f,  0.5f, -1.f, 0.f, 0.f,  1.0f, 0.0f, // top-right
    -0.5f, -0.5f, -0.5f, -1.f, 0.f, 0.f,  0.0f, 1.0f, // bottom-left
    // Right face
     0.5f, -0.5f, -0.5f, 1.f, 0.f, 0.f,  0.0f, 1.0f, // bottom-right
     0.5f,  0.5f, -0.5f, 1.f, 0.f, 0.f,  1.0f, 1.0f, // top-right
     0.5f,  0.5f,  0.5f, 1.f, 0.f, 0.f,  1.0f, 0.0f, // top-left
     0.5f,  0.5f,  0.5f, 1.f, 0.f, 0.f,  1.0f, 0.0f, // top-left
     0.5f, -0.5f,  0.5f, 1.f, 0.f, 0.f,  0.0f, 0.0f, // bottom-left
     0.5f, -0.5f, -0.5f, 1.f, 0.f, 0.f,  0.0f, 1.0f, // bottom-right
    // Bottom face
     0.5f, -0.5f, -0.5f, 0.f, -1.f, 0.f,  1.0f, 1.0f, // top-left
     0.5f, -0.5f,  0.5f, 0.f, -1.f, 0.f,  1.0f, 0.0f, // bottom-left
    -0.5f, -0.5f, -0.5f, 0.f, -1.f, 0.f,  0.0f, 1.0f, // top-right
    -0.5f, -0.5f,  0.5f, 0.f, -1.f, 0.f,  0.0f, 0.0f, // bottom-right
    -0.5f, -0.5f, -0.5f, 0.f, -1.f, 0.f,  0.0f, 1.0f, // top-right
     0.5f, -0.5f,  0.5f, 0.f, -1.f, 0.f,  1.0f, 0.0f, // bottom-left
    // Top face
    0.5f,  0.5f,  0.5f, 0.f, 1.f, 0.f,  1.0f, 0.0f, // bottom-right
    0.5f,  0.5f, -0.5f, 0.f, 1.f, 0.f,  1.0f, 1.0f, // top-right
    -0.5f,  0.5f, -0.5f, 0.f, 1.f, 0.f,  0.0f, 1.0f, // top-left
     0.5f,  0.5f,  0.5f, 0.f, 1.f, 0.f,  1.0f, 0.0f, // bottom-right
    -0.5f,  0.5f, -0.5f, 0.f, 1.f, 0.f,  0.0f, 1.0f, // top-left
    -0.5f,  0.5f,  0.5f, 0.f, 1.f, 0.f,  0.0f, 0.0f, // bottom-left
};
    /*float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };*/


    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    mainObject->bindVBO(sizeof(vertices), vertices, GL_STATIC_DRAW);
    mainObject->bindEBO(sizeof(indices), indices, GL_STATIC_DRAW);

    mainObject->bindAttribute(3, 8 * sizeof(float), 0);
    mainObject->bindAttribute(3, 8 * sizeof(float), 3 * sizeof(float));
    mainObject->bindAttribute(2, 8 * sizeof(float), 6 * sizeof(float));
}

void Cube::bindMaterial(Material *material)
{
    this->material = material;

    shaderProgram->use();
    material->bindToShader(*shaderProgram);
}

void Cube::draw()
{
    glm::mat4 model;
    glm::mat4 view;

    shaderProgram->use();
    object->use();

    if (material != NULL)
        material->activateTextures();

    model = getModelMatrix();
    view = Camera::displayCamera->getViewMatrix();

    shaderProgram->setMat4("model", model);
    shaderProgram->setMat4("view", view);

    Light::setLightsToShader(shaderProgram);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}
