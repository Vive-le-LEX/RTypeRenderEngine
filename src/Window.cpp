/*
** EPITECH PROJECT, 2023
** RTypeRenderEngine
** File description:
** main
*/

#include "Window.hpp"

using namespace RTypeEngine;

bool Window::_wasInit = false;

void Window::initOpenGL() {
    if (_wasInit)
        return;
    if (!glfwInit())
        throw std::runtime_error("Failed to initialize GLFW");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(
        GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE
    );
    _wasInit = true;
}

Window::Window(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share) : _shouldClose(false) {
    if (!_wasInit)
        throw std::runtime_error("RTypeEngine::Window::initGlfw() must be called before creating a window");
    _window = glfwCreateWindow(width, height, title, monitor, share);
    if (!_window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
    _viewport = glm::ivec4(0, 0, width, height);
    glfwSetErrorCallback([](int error, const char *description) {
        std::cerr << "Internal GLFW Error " << error << ": " << description << std::endl;
    });
    glViewport(_viewport.x, _viewport.y, _viewport.z, _viewport.w);
    glfwSetWindowUserPointer(_window, this);
    // setCallbacks();

    glfwSetInputMode(glfwGetCurrentContext(), GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
    glfwSetInputMode(glfwGetCurrentContext(), GLFW_STICKY_KEYS, 1);
    glfwSwapInterval(0);
    glEnable(GL_DEPTH_TEST);
}

Window::~Window() {
    glfwDestroyWindow(_window);
}

// bool Window::shouldClose(void) const {
//     return glfwWindowShouldClose(_window) || _shouldClose;
// }

// void Window::close(void) {
//     _shouldClose = true;
// }

// const glm::ivec4 &Window::getViewport(void) const {
//     return _viewport;
// }

// void Window::setViewport(const glm::ivec4 &viewport) {
//     _viewport = viewport;
//     glViewport(_viewport.x, _viewport.y, _viewport.z, _viewport.w);
// }

// void Window::clear(const glm::vec4 &c) const {
//     glClearColor(c.r, c.g, c.b, c.a);
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// }
