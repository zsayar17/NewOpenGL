#include "Camera.hpp"

Camera* Camera::displayCamera = NULL;

Camera::Camera()
{
    if (!displayCamera) setDisplayCamera();

    eyeVec   = glm::vec3(0.0f, 0.0f, 3.0f);
    frontVec = glm::vec3(0.0f, 0.0f, -1.0f);
    upVec = glm::vec3(0, 1, 0);

    projection = glm::perspective(glm::radians(45.0f), (float)Window::width / (float)Window::height, 0.1f, 100.0f);
}

const Camera& Camera::operator=(const Camera& camera)
{
    eyeVec = camera.eyeVec;
    upVec = camera.upVec;
    frontVec = camera.frontVec;
    projection = camera.projection;

    BaseObject::operator=(camera);

    return *this;
}

glm::mat4 Camera::getViewMatrix(bool getExceptProjection) const {
    if (getExceptProjection)
        return projection * glm::mat4(glm::mat3(glm::lookAt(localPosition + worldPosition, worldPosition + localPosition + localFront, upVec)));
    return projection * glm::lookAt(localPosition + worldPosition, worldPosition + localPosition + localFront, upVec);
}

void Camera::setDisplayCamera()
{
    displayCamera = this;
}
