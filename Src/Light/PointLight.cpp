#include "PointLight.hpp"

PointLight::PointLight() : Light(POINT) {
    lightLevel = MEDIUM;
}

PointLight::~PointLight() {

}

void PointLight::setLightColor(const glm::vec3& color, LightingType type) {
    Light::setLightColor(color, type);
}

glm::vec3 PointLight::getLightColor(LightingType type) const {
    return Light::getLightColor(type);
}

void PointLight::setLightLevel(LightDistanceLevel level) {
    lightLevel = level;
}

int PointLight::getLightLevel() const {
    return lightLevel;
}

void PointLight::setLightToShader(Shader* shader, int index) {
    std::stringstream ss;
    glm::vec3 position(getPosition());
    glm::vec3 ambient(getLightColor(AMBIENT));
    glm::vec3 diffuse(getLightColor(DIFUSE));
    glm::vec3 specular(getLightColor(SPECULAR));
    glm::vec3 cameraPos(Camera::displayCamera->getPosition());

    ss << "pointLights[" << index << "].";
    std::string prefix = ss.str();
    //std::cout << Light::LightAttenuationValues[lightLevel][LINEAR] << std::endl;

    shader->setVec3(prefix + "position", position);
    shader->setVec3(prefix + "ambient", ambient);
    shader->setVec3(prefix + "diffuse", diffuse);
    shader->setVec3(prefix + "specular", specular);
    shader->setFloat(prefix + "constant", 1.0f);
    shader->setFloat(prefix + "linear", Light::LightAttenuationValues[lightLevel][LINEAR]);
    shader->setFloat(prefix + "quadratic", Light::LightAttenuationValues[lightLevel][QUADRATIC]);

    shader->setVec3("viewPos", cameraPos);
}
