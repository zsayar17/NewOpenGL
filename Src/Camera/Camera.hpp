#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>
#include "../../Essantials/glad/glad.h"
#include "../../Essantials/Glfw/include/GLFW/glfw3.h"

#include "../Window/Window.hpp"
#include "../BaseObject/BaseObject.hpp"
#include "../Shader/Shader.hpp"
#include "../Object/Object.hpp"
#include "../Object/UniformBufferObject.hpp"

class Camera : public BaseObject
{
    public:
        static Camera* displayCamera;

        Camera();
        const Camera& operator=(const Camera& camera);

        void draw() {}
        glm::mat4 getViewMatrix(bool getExceptTranlate = false) const;
        void setDisplayCamera();

        void updateCamera();

    private:
        glm::vec3 eyeVec;
        glm::vec3 upVec;
        glm::vec3 frontVec;
        glm::mat4 projection;

        float yaw, pitch;
};

#endif
