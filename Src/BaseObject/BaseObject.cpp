#include "BaseObject.hpp"

unsigned int BaseObject::objectCounter = 0;
Shader* BaseObject::mainShaderProgram = NULL;

BaseObject::BaseObject()
{
    if (mainShaderProgram == NULL) {
        mainShaderProgram = new Shader("VertexShader", "FragmentShader");
    }

    shaderProgram = mainShaderProgram;

    translateModel = glm::mat4(1.0f);
    rotateModel = glm::mat4(1.0f);
    scaleModel = glm::mat4(1.0f);

    worldPosition = glm::vec3(0.0f);
    localPosition = glm::vec3(0.0f);

    worldRotation = glm::vec3(0.0f);
    localRotation = glm::vec3(0.0f, -90.0f, 0.0f);

    scaleValue = glm::vec3(1.0f);

    localFront = glm::vec3(0.0f, 0.0f, -1.0f);
    localUp = glm::vec3(0.0f, 1.0f, 0.0f);

    objectID = objectCounter;
    objectCounter++;
}

BaseObject::~BaseObject()
{

}

void BaseObject::bindShader(Shader *shader)
{
    shaderProgram = shader;
}

void BaseObject::translateWorld(glm::vec3 axes)
{
    translateModel = glm::translate(translateModel, axes);

    worldPosition += axes;
}

void BaseObject::rotateWorld(float angle, glm::vec3 axes)
{
    rotateModel = glm::rotate(rotateModel, glm::radians(angle), axes);

    worldRotation += axes * angle;
}

void BaseObject::translateLocal(glm::vec3 axes)
{
    glm::vec3 prevLocalPosition = localPosition;

    if (axes.x) localPosition += glm::normalize(glm::cross(localFront, localUp)) * axes.x;
    if (axes.y) localPosition += localUp * axes.y;
    if (axes.z) localPosition -= localFront * axes.z;

    translateModel = glm::translate(translateModel, localPosition - prevLocalPosition);
}

void BaseObject::rotateLocal(float angle, glm::vec3 axes)
{
    localRotation += axes * angle;

    localFront.x = cos(glm::radians(localRotation.y)) * cos(glm::radians(localRotation.x));
    localFront.y = sin(glm::radians(localRotation.x));
    localFront.z = sin(glm::radians(localRotation.y)) * cos(glm::radians(localRotation.x));

    localFront = glm::normalize(localFront);

    rotateModel = glm::rotate(rotateModel, glm::radians(-angle), axes);
}

void BaseObject::scale(glm::vec3 axes)
{
    scaleModel = glm::scale(scaleModel, axes);

    this->scaleValue += axes;
}

glm::vec3 BaseObject::getPosition() const
{
    return worldPosition + localPosition;
}

glm::vec3 BaseObject::getLocalPosition() const
{
    return localPosition;
}

glm::vec3 BaseObject::getWorldPosition() const
{
    return worldPosition;
}

glm::vec3 BaseObject::getLocalRotation() const
{
    return localRotation;
}

glm::vec3 BaseObject::getWorldRotation() const
{
    return worldRotation;
}

glm::vec3 BaseObject::getFront() const
{
    return localFront;
}

glm::mat4 BaseObject::getModelMatrix() const
{
    return translateModel * rotateModel * scaleModel;
}

void BaseObject::setWorldPosition(glm::vec3 position)
{
    translateModel = glm::translate(translateModel, position - worldPosition);
    worldPosition = position;
}

void BaseObject::setWorldRotation(glm::vec3 rotation)
{
    rotateModel = glm::rotate(rotateModel, glm::radians(rotation.x - worldRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateModel = glm::rotate(rotateModel, glm::radians(rotation.y - worldRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateModel = glm::rotate(rotateModel, glm::radians(rotation.z - worldRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    worldRotation = rotation;
}

void BaseObject::setLocalPosition(glm::vec3 position)
{
    translateModel = glm::translate(translateModel, position - localPosition);
    localPosition = position;
}

void BaseObject::setLocalRotation(glm::vec3 rotation)
{
    rotateModel = glm::rotate(rotateModel, glm::radians(rotation.x - localRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateModel = glm::rotate(rotateModel, glm::radians(rotation.y - localRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateModel = glm::rotate(rotateModel, glm::radians(rotation.z - localRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    localRotation = rotation;
}
