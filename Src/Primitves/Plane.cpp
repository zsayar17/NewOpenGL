#include "Plane.hpp"

Object* Plane::mainObject = NULL;

Plane::Plane()
{
    material = NULL;

    if (!mainObject)
    {
        mainObject = new Object();
        createPlane();
    }

    object = mainObject;
}

Plane::~Plane()
{
}

void Plane::createPlane()
{
    float planeVertices[] = {
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
        5.0f, -0.5f,  5.0f,  2.0f, 0.0f,

         5.0f, -0.5f, -5.0f,  2.0f, 2.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
    };



    mainObject->bindVBO(sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);

    mainObject->bindAttribute(3, 5 * sizeof(float), 0);
    mainObject->bindAttribute(2, 5 * sizeof(float), 3 * sizeof(float));
}

void Plane::bindMaterial(Material *material)
{
    this->material = material;

    shaderProgram->use();
    material->bindToShader(*shaderProgram);
}

void Plane::bindObject(Object *object)
{
    this->object = object;
}

void Plane::draw()
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

    glDrawArrays(GL_TRIANGLES, 0, 6);
}
