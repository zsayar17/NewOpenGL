#ifndef __DIRECTIONALLIGHT_HPP__
#define __DIRECTIONALLIGHT_HPP__

#include <iostream>

#include "Light.hpp"

class DirectionalLight : public Light {
    public:
        DirectionalLight();
        ~DirectionalLight();

        void setLightColor(const glm::vec3& color, LightingType type);
        glm::vec3 getLightColor(LightingType type) const;

        void setLightToShader(Shader* shader, int index);
};

#endif
