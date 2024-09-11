#include "Utils.hpp"
#include <iostream>

float Utils::deltaTime = 0;
float Utils::lastFrame = 0;

void Utils::calculateDeltaTime()
{
    float currentFrame = glfwGetTime();

    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

float Utils::getDeltaTime()
{
    return deltaTime;
}
