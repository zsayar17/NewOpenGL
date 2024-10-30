#include "Window.hpp"

int Window::width;
int Window::height;
float Window::value;
glm::vec3 Window::moveValue;
float Window::xOffSet;
float Window::yOffSet;


Window::Window(int width, int height, const char *title)
{
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Set the OpenGL profile to core
    #if __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #else
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #endif


    this->width = width;
    this->height = height;

    // Create a window
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetCursorPos(window, Window::width / 2.0, Window::height / 2.0);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        std::cout << "Failed to initialize GLAD" << std::endl;

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_STENCIL_TEST);

    // Enabling the blending for transparency
    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW); // models are drawn in counter clockwise order
}

Window::~Window()
{
    glfwTerminate();
}

bool Window::shouldClose()
{
    return glfwWindowShouldClose(window);
}

void Window::clear()
{
    processInput(window);

    glClearColor(0.f, 0.f, 0.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Window::reset()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    Window::width = width;
    Window::height = height;

    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    float cameraSpeed = 1.f * Utils::getDeltaTime();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        Camera::displayCamera->translateLocal(glm::vec3(0, 0, -1) * cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        Camera::displayCamera->translateLocal(glm::vec3(0, 0, 1) * cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        Camera::displayCamera->translateLocal(glm::vec3(-1, 0, 0) * cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        Camera::displayCamera->translateLocal(glm::vec3(1, 0, 0) * cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        Camera::displayCamera->translateLocal(glm::vec3(0, 1, 0) * cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        Camera::displayCamera->translateLocal(glm::vec3(0, -1, 0) * cameraSpeed);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        Camera::displayCamera->rotateLocal(0.5f, glm::vec3(1, 0, 0));
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        Camera::displayCamera->rotateLocal(-0.5f, glm::vec3(1, 0, 0));
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        Camera::displayCamera->rotateLocal(-0.5f, glm::vec3(0, 1, 0));
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        Camera::displayCamera->rotateLocal(0.5f, glm::vec3(0, 1, 0));

    /*if (glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS)
        Light::lights[0]->translateLocal(glm::vec3(0, 0, -1) * cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_PRESS)
        Light::lights[0]->translateLocal(glm::vec3(0, 0, 1) * cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS)
        Light::lights[0]->translateLocal(glm::vec3(-1, 0, 0) * cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS)
        Light::lights[0]->translateLocal(glm::vec3(1, 0, 0) * cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_KP_9) == GLFW_PRESS)
        Light::lights[0]->translateLocal(glm::vec3(0, -1, 0) * cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_KP_7) == GLFW_PRESS)
        Light::lights[0]->translateLocal(glm::vec3(0, 1, 0) * cameraSpeed);*/
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    static double lastX, lastY;
    static bool firstMove = true;
    static const float sensitivity = 0.1f;

    if (firstMove) {
        lastX = xpos;
        lastY = ypos;
        firstMove = false;
        return;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // Y ekseni ters çalışır

    lastX = xpos;
    lastY = ypos;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    std::cout << "x: " << xpos << " y: " << ypos << std::endl;

    // Kamerayı hareket ettirmek için delta değerlerini kullan
    Camera::displayCamera->rotateLocal(xoffset, glm::vec3(0, 1, 0));
    Camera::displayCamera->rotateLocal(yoffset, glm::vec3(1, 0, 0));
}
