#include <iostream>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Essantials/glad/glad.h"
#include "../Essantials/Glfw/include/GLFW/glfw3.h"

#include "Game.hpp"

int main()
{
    Window window(800, 680, "AhmetEngine");
    Game game;


    game.setup();

    float deltaTime = 0.0f;
    float lastFrame = glfwGetTime();
    int frames = 0;

    while (!window.shouldClose())
    {
        deltaTime = glfwGetTime() - lastFrame;
        frames++;
        if (deltaTime >= 1.0f)
        {
            std::cout << "FPS: " << (1.0f / deltaTime) * frames << std::endl;
            lastFrame = glfwGetTime();
            frames = 0;
        }

        Utils::calculateDeltaTime();

        window.clear();

        game.update();
        game.draw();

        window.reset();
    }
}
