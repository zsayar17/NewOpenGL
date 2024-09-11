#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__


#include "../../Essantials/glad/glad.h"
#include "../../Essantials/Glfw/include/GLFW/glfw3.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Camera/Camera.hpp"
#include "../Utils/Utils.hpp"
//#include "../Light/Light.hpp"


class Window
{
    public:
        GLFWwindow* window;
        static int width, height;

        static float value;
        static glm::vec3 moveValue;
        static float xOffSet, yOffSet;

        Window(int width, int height, const char *title);
        ~Window();

        bool shouldClose();
        void clear();
        void reset();

};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

#endif
