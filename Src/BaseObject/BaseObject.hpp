#ifndef __BASEOBJECT_HPP__
#define __BASEOBJECT_HPP__

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../Essantials/glad/glad.h"
#include "../../Essantials/Glfw/include/GLFW/glfw3.h"
#include "../Object/Object.hpp"
#include "../Shader/Shader.hpp"
#include "../Object/UniformBufferObject.hpp"
#include "../Utils/Constants.hpp"

class BaseObject
{
    public:
        BaseObject();
        virtual ~BaseObject();

        const BaseObject& operator=(const BaseObject& object);

        virtual void draw() { };

        void setWorldPosition(glm::vec3 position);
        void setWorldRotation(glm::vec3 rotation);
        void translateWorld(glm::vec3 axes);
        void rotateWorld(float angle, glm::vec3 axes);

        void setLocalPosition(glm::vec3 position);
        void setLocalRotation(glm::vec3 rotation);
        void translateLocal(glm::vec3 axes);
        void rotateLocal(float angle, glm::vec3 axes);

        void scale(glm::vec3 axes);

        glm::vec3 getPosition() const;
        glm::vec3 getLocalPosition() const;
        glm::vec3 getWorldPosition() const;

        glm::vec3 getLocalRotation() const;
        glm::vec3 getWorldRotation() const;

        glm::vec3 getFront() const;

        glm::mat4 getModelMatrix() const;



        void bindShader(Shader *shader);

        void bindShaderToUBO(const std::string& bufferName);

        protected:
            static Shader *mainShaderProgram;
            Shader *shaderProgram;

            glm::mat4 translateModel;
            glm::mat4 rotateModel;
            glm::mat4 scaleModel;

            glm::vec3 worldPosition;
            glm::vec3 worldRotation;

            glm::vec3 localPosition;
            glm::vec3 localRotation;

            glm::vec3 scaleValue;

            glm::vec3 localFront;
            glm::vec3 localUp;

            static unsigned int objectCounter;
            int                 objectID;

};

#endif
