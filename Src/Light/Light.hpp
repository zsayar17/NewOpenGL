#ifndef __LIGHT_HPP__
#define __LIGHT_HPP__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <utility>
#include <cstring>

#include "../BaseObject/BaseObject.hpp"
#include "../Primitves/Cube.hpp"

enum LightingType {
    DIFUSE,
    SPECULAR,
    AMBIENT,
    LIGHTING_COUNT
};

enum LightType {
    POINT,
    DIRECTIONAL,
    SPOT,
    LIGHT_COUNT
};

enum LightDistanceLevel {
    SHORT,
    MEDIUM,
    LONG,
    LIGHT_DISTANCE_LEVEL_COUNT
};

enum LightAttenuation {
    LINEAR,
    QUADRATIC,
    LIGHT_ATTENUATION_COUNT
};

class Light : public BaseObject {
    public:
        static std::vector< std::pair<LightType, Light*> > lights;

        Light(LightType type);
        virtual ~Light();

        void setWorldPosition(glm::vec3 position);
        void setWorldRotation(glm::vec3 rotation);

        void setLocalPosition(glm::vec3 position);
        void setLocalRotation(glm::vec3 rotation);

        void translateWorld(glm::vec3 axes);
        void rotateWorld(float angle, glm::vec3 axes);

        void translateLocal(glm::vec3 axes);
        void rotateLocal(float angle, glm::vec3 axes);

        void scale(glm::vec3 axes);


        glm::vec3 getPosition() const;
        glm::vec3 getFront() const;


        void draw();

        static void setLightsToShader(Shader* shader);

    protected:
        static float LightAttenuationValues[LIGHT_DISTANCE_LEVEL_COUNT][LIGHT_ATTENUATION_COUNT];
        Cube lightCube;

        void setLightColor(glm::vec3 color, LightingType type = AMBIENT);
        glm::vec3 getLightColor(LightingType type = AMBIENT) const;


    private:

        static Shader *lightShader;
        glm::vec3 lightColors[LIGHTING_COUNT];
        float shininess;

        virtual void setLightToShader(Shader* shader, int index) = 0;
};

#endif
