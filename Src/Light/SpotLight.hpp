#ifndef __SPOTLIGHT_HPP__
#define __SPOTLIGHT_HPP__

#include <iostream>

#include "Light.hpp"

class SpotLight : public Light {
    public:
        SpotLight();
        ~SpotLight();

        void setLightColor(const glm::vec3& color, LightingType type);
        glm::vec3 getLightColor(LightingType type) const;

        void setLightToShader(Shader* shader, int index);
        void setLightLevel(LightDistanceLevel level);
        int getLightLevel() const;

        void setInnerCutOffAngle(float angle);
        void setOuterCutOffAngle(float angle);
        void setCutOffAngles(float innerAngle, float outerAngle);

        float getInnerCutOffAngle() const;
        float getOuterCutOffAngle() const;
        glm::vec2 getCutOffAngles() const;

    private:
        int lightLevel;
        float innerCutOffAngle;
        float outerCutOffAngle;
};

#endif
