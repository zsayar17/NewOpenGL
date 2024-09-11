#include "Light.hpp"
#include "../Primitves/Cube.hpp"


std::vector< std::pair<LightType, Light*> > Light::lights;
Shader *Light::lightShader = NULL;

float Light::LightAttenuationValues[LIGHT_DISTANCE_LEVEL_COUNT][LIGHT_ATTENUATION_COUNT] = {
        { 0.14f, 0.07f },
        { 0.09f, 0.032f },
        { 0.07f, 0.017f }
};

Light::Light(LightType type) {
    if (lightShader == NULL)
        lightShader = new Shader("VertexShader", "LightFragmentShader");

    lightCube.bindShader(lightShader);
    lights.push_back( std::pair<LightType, Light*>(type, this) );
}

Light::~Light() {
    for (unsigned int i = 0; i < lights.size(); i++) {
        if (lights[i].second == this) {
            lights.erase(lights.begin() + i);
            break;
        }
    }
}

void Light::setLightColor(glm::vec3 color, LightingType type) {
    lightColors[type] = color;
}

glm::vec3 Light::getLightColor(LightingType type) const {
    return lightColors[type];
}

void Light::draw() {
    lightCube.draw();
}

void Light::setWorldPosition(glm::vec3 position) {
    lightCube.setWorldPosition(position);
    BaseObject::setWorldPosition(position);
}

void Light::setLocalPosition(glm::vec3 position) {
    lightCube.setLocalPosition(position);
    BaseObject::setLocalPosition(position);
}

void Light::setWorldRotation(glm::vec3 rotation) {
    lightCube.setWorldRotation(rotation);
    BaseObject::setWorldRotation(rotation);
}

void Light::setLocalRotation(glm::vec3 rotation) {
    lightCube.setLocalRotation(rotation);
    BaseObject::setLocalRotation(rotation);
}

void Light::translateWorld(glm::vec3 axes) {
    lightCube.translateWorld(axes);
    BaseObject::translateWorld(axes);
}

void Light::rotateWorld(float angle, glm::vec3 axes) {
    lightCube.rotateWorld(angle, axes);
    BaseObject::rotateWorld(angle, axes);
}

void Light::translateLocal(glm::vec3 axes) {
    lightCube.translateLocal(axes);
    BaseObject::translateLocal(axes);
}

void Light::rotateLocal(float angle, glm::vec3 axes) {
    lightCube.rotateLocal(angle, axes);
    BaseObject::rotateLocal(angle, axes);
}

void Light::scale(glm::vec3 axes) {
    lightCube.scale(axes);
    BaseObject::scale(axes);
}

glm::vec3 Light::getPosition() const {
    return lightCube.getPosition();
}

glm::vec3 Light::getFront() const {
    return lightCube.getFront();
}

void Light::setLightsToShader(Shader* shader) {
    int types[LIGHTING_COUNT];
    memset(types, 0, sizeof(types));

    for (unsigned int i = 0; i < lights.size(); i++) {
        lights[i].second->setLightToShader(shader, types[lights[i].first]);
        types[lights[i].first]++;
    }
}
