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

Window::Window(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share) : _isOpen(true) {
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
    // std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
}

Window::~Window() {
    glfwDestroyWindow(_window);
    glfwTerminate();
}

const bool &Window::isOpen(void) const {
    return _isOpen;
}

void Window::close(void) {
    _isOpen = false;
}

const glm::ivec4 &Window::getViewport(void) const {
    return _viewport;
}

void Window::setViewport(const glm::ivec4 &viewport) {
    _viewport = viewport;
    glViewport(_viewport.x, _viewport.y, _viewport.z, _viewport.w);
}

void Window::clear(const glm::vec4 &c) const {
    glClearColor(c.r, c.g, c.b, c.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::display(void) {
    static auto lastTime = std::chrono::high_resolution_clock::now();
    glfwSwapBuffers(_window);
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto usSpent = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastTime);
    if (_frameRateLimit > 0) {
        auto usPerFrame = std::chrono::microseconds(1000000 / _frameRateLimit);
        if (usSpent < usPerFrame) {
            std::this_thread::sleep_for(usPerFrame - usSpent);
            currentTime = std::chrono::high_resolution_clock::now();
        }
    }
    _deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - lastTime).count();
    lastTime = currentTime;
}

void Window::setFramerateLimit(const int &limit) {
    _frameRateLimit = limit;
}

const int Window::getFramerate(void) const {
    return 1 / _deltaTime;
}

const double &Window::getDeltaTime(void) const {
    return _deltaTime;
}
