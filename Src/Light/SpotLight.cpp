#include "SpotLight.hpp"

SpotLight::SpotLight() : Light(SPOT) {
    lightLevel = MEDIUM;

    innerCutOffAngle = 12.5f;
    outerCutOffAngle = 17.5f;
}

SpotLight::~SpotLight() {

}

void SpotLight::setLightColor(const glm::vec3& color, LightingType type) {
    Light::setLightColor(color, type);
}

glm::vec3 SpotLight::getLightColor(LightingType type) const {
    return Light::getLightColor(type);
}

void SpotLight::setLightLevel(LightDistanceLevel level) {
    lightLevel = level;
}

int SpotLight::getLightLevel() const {
    return lightLevel;
}

void SpotLight::setInnerCutOffAngle(float angle) {
    innerCutOffAngle = angle;
}

void SpotLight::setOuterCutOffAngle(float angle) {
    outerCutOffAngle = angle;
}

void SpotLight::setCutOffAngles(float innerAngle, float outerAngle) {
    innerCutOffAngle = innerAngle;
    outerCutOffAngle = outerAngle;
}

float SpotLight::getInnerCutOffAngle() const {
    return innerCutOffAngle;
}

float SpotLight::getOuterCutOffAngle() const {
    return outerCutOffAngle;
}

glm::vec2 SpotLight::getCutOffAngles() const {
    return glm::vec2(innerCutOffAngle, outerCutOffAngle);
}

void SpotLight::setLightToShader(Shader* shader, int index) {
    std::stringstream ss;
    glm::vec3 position(getPosition());
    glm::vec3 direction(getFront());
    glm::vec3 ambient(getLightColor(AMBIENT));
    glm::vec3 diffuse(getLightColor(DIFUSE));
    glm::vec3 specular(getLightColor(SPECULAR));
    glm::vec3 cameraPos(Camera::displayCamera->getPosition());

    position = glm::vec3(Camera::displayCamera->getPosition());
    direction = glm::vec3(Camera::displayCamera->getFront());

    ss << "spotLights[" << index << "].";
    std::string prefix = ss.str();

    shader->setVec3(prefix + "position", position);
    shader->setVec3(prefix + "direction", direction);
    shader->setVec3(prefix + "ambient", ambient);
    shader->setVec3(prefix + "diffuse", diffuse);
    shader->setVec3(prefix + "specular", specular);
    shader->setFloat(prefix + "innerCutOff", glm::cos(glm::radians(innerCutOffAngle)));
    shader->setFloat(prefix + "outerCutOff", glm::cos(glm::radians(outerCutOffAngle)));
    shader->setFloat(prefix + "constant", 1.0f);
    shader->setFloat(prefix + "linear", Light::LightAttenuationValues[lightLevel][LINEAR]);
    shader->setFloat(prefix + "quadratic", Light::LightAttenuationValues[lightLevel][QUADRATIC]);

    shader->setVec3("viewPos", cameraPos);
}

