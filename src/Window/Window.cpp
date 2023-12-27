/*
** EPITECH PROJECT, 2023
** RTypeRenderEngine
** File description:
** main
*/

#include "RTypeEngine/Window/Window.hpp"

using namespace RTypeEngine;

bool Window::_wasInit = false;

void Window::initOpenGL() {
    if (_wasInit)
        return;
    if (!glfwInit())
        throw std::runtime_error("Failed to initialize GLFW");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    _wasInit = true;
}

Window::Window(int width, int height, const char *title, GLFWmonitor *monitor,
               GLFWwindow *share) : _isOpen(true) {

    if (!_wasInit)
        Window::initOpenGL();
    _window = glfwCreateWindow(width, height, title, monitor, share);
    if (!_window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(_window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
    _viewport = glm::ivec4(0, 0, width, height);

    glfwSetErrorCallback([](int error, const char *description) {
        std::cerr << "Internal GLFW Error " << error << ": " << description
                  << std::endl;
        std::cerr << "Internal GLFW Error " << error << ": " << description
                  << std::endl;
    });
    glViewport(_viewport.x, _viewport.y, _viewport.z, _viewport.w);
    _eventHandler = std::make_unique<EventHandler>(_window);
    glfwSetWindowUserPointer(_window, _eventHandler.get());

    glfwSetInputMode(glfwGetCurrentContext(), GLFW_STICKY_MOUSE_BUTTONS,
                     GLFW_TRUE);
    glfwSetInputMode(glfwGetCurrentContext(), GLFW_LOCK_KEY_MODS,
                     GLFW_TRUE);
    glfwSwapInterval(0);
    glEnable(GL_DEPTH_TEST);
}

// void Window::setCallbacks(void) {
//     glfwSetFramebufferSizeCallback(_window, [](GLFWwindow *window, int width, int height) {
//         Window *w = static_cast<Window *>(glfwGetWindowUserPointer(window));
//         w->setViewport(glm::ivec4(0, 0, width, height));
//     });
//     glfwSetCursorEnterCallback(_window, [](GLFWwindow *window, int entered) {
//         Window *w = static_cast<Window *>(glfwGetWindowUserPointer(window));
//         w->getMouseHandler().updateMouseEnter(entered);
//     });
//     glfwSetCursorPosCallback(_window, [](GLFWwindow *window, double xpos, double ypos) {
//         Window *w = static_cast<Window *>(glfwGetWindowUserPointer(window));
//         w->getMouseHandler().updateMousePos(xpos, ypos);
//     });
//     glfwSetMouseButtonCallback(_window, [](GLFWwindow *window, int button, int action, int mods) {
//         Window *w = static_cast<Window *>(glfwGetWindowUserPointer(window));
//         w->getMouseHandler().updateMouseClick(button, action, mods);
//     });
//     glfwSetScrollCallback(_window, [](GLFWwindow *window, double xoffset, double yoffset) {
//         Window *w = static_cast<Window *>(glfwGetWindowUserPointer(window));
//         w->getMouseHandler().updateMouseScroll(xoffset, yoffset);
//     });
//     glfwSetWindowCloseCallback(_window, [](GLFWwindow *window) {
//         Window *w = static_cast<Window *>(glfwGetWindowUserPointer(window));
//         w->close();
//     });
// }

Window::~Window() {
    glfwDestroyWindow(_window);
    glfwTerminate();
}

const bool &Window::isOpen() const {
    return _isOpen;
}

void Window::close() {
    _isOpen = false;
}

const glm::ivec4 &Window::getViewport() const {
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

void Window::display() {
    static auto lastTime = std::chrono::high_resolution_clock::now();
    glfwSwapBuffers(_window);
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto usSpent = std::chrono::duration_cast<std::chrono::microseconds>(
            currentTime - lastTime);
    if (_frameRateLimit > 0) {
        auto usPerFrame = std::chrono::microseconds(1000000 / _frameRateLimit);
        if (usSpent < usPerFrame) {
            std::this_thread::sleep_for(usPerFrame - usSpent);
            currentTime = std::chrono::high_resolution_clock::now();
        }
    }
    _deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(
            currentTime - lastTime).count();
    lastTime = currentTime;
}

void Window::setFramerateLimit(const int &limit) {
    _frameRateLimit = limit;
}

const int Window::getFramerate() const {
    return 1 / _deltaTime;
}

const double &Window::getDeltaTime() const {
    return _deltaTime;
}

void Window::pollEvents() {
    glfwPollEvents();
}