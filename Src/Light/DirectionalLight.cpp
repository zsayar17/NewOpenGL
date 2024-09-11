#include "DirectionalLight.hpp"

DirectionalLight::DirectionalLight() : Light(DIRECTIONAL) {

}

DirectionalLight::~DirectionalLight() {

}

void DirectionalLight::setLightColor(const glm::vec3& color, LightingType type) {
    Light::setLightColor(color, type);
}

glm::vec3 DirectionalLight::getLightColor(LightingType type) const {
    return Light::getLightColor(type);
}

void DirectionalLight::setLightToShader(Shader* shader, int index) {
    std::stringstream ss;
    glm::vec3 direction(-0.2f, -1.0f, -0.3f);
    glm::vec3 ambient(getLightColor(AMBIENT));
    glm::vec3 diffuse(getLightColor(DIFUSE));
    glm::vec3 specular(getLightColor(SPECULAR));
    glm::vec3 cameraPos(Camera::displayCamera->getPosition());

    ss << "directionalLights[" << index << "].";
    std::string prefix = ss.str();

    shader->setVec3(prefix + "direction", direction);
    shader->setVec3(prefix + "ambient", ambient);
    shader->setVec3(prefix + "diffuse", diffuse);
    shader->setVec3(prefix + "specular", specular);

    shader->setVec3("viewPos", cameraPos);
}


