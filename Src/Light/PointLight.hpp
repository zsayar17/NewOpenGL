#ifndef __POINTLIGHT_HPP__
#define __POINTLIGHT_HPP__

#include <iostream>

#include "Light.hpp"

class PointLight : public Light {
    public:
        PointLight();
        ~PointLight();

        void setLightColor(const glm::vec3& color, LightingType type);
        glm::vec3 getLightColor(LightingType type) const;

        void setLightToShader(Shader* shader, int index);
        void setLightLevel(LightDistanceLevel level);
        int getLightLevel() const;

    private:
        int lightLevel;
};

#endif
