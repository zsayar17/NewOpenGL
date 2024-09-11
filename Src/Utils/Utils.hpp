#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include "../../Essantials/Glfw/include/GLFW/glfw3.h"

class Utils
{
    public:
        static void calculateDeltaTime();
        static float getDeltaTime();
    private:
        static float lastFrame, deltaTime;
};

#endif
