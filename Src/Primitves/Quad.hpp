#ifndef __QUAD_HPP__
#define __QUAD_HPP__

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <utility>
#include <sstream>

#include "../../Essantials/glad/glad.h"
#include "../../Essantials/Glfw/include/GLFW/glfw3.h"
#include "../BaseObject/BaseObject.hpp"
#include "../Object/Object.hpp"
#include "../Material/Material.hpp"
#include "../Camera/Camera.hpp"

class Quad : public BaseObject
{
    public:
        Quad();
        ~Quad();

        void bindMaterial(Material *material);
        void bindObject(Object *object);
        void draw();

    private:
        static Object *mainObject;
        static Shader *mainShaderProgram;
        Material *material;
        Object *object;

        static void createQuad();
};

#endif
