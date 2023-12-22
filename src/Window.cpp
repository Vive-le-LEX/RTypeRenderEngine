/*
** EPITECH PROJECT, 2023
** RTypeRenderEngine
** File description:
** main
*/

#include "Window.hpp"
#include "Window/Window.hpp"

using namespace RTypeEngine;

/**
 * @brief Initialize GLFW
 */
bool Window::_wasInit = false;

/**
 * @brief Initialize GLFW
 */
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

/**
 * @brief Create a window
 * @param width Window width
 * @param height Window height
 * @param title Window title
 * @param monitor Monitor
 * @param share Share
 */
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
    });
    glViewport(_viewport.x, _viewport.y, _viewport.z, _viewport.w);
    glfwSetWindowUserPointer(_window, this);
    // setCallbacks();

    glfwSetInputMode(glfwGetCurrentContext(), GLFW_STICKY_MOUSE_BUTTONS,
                     GLFW_TRUE);
    glfwSetInputMode(glfwGetCurrentContext(), GLFW_STICKY_KEYS, 1);
    glfwSwapInterval(0);
    glEnable(GL_DEPTH_TEST);
    // std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
}

/**
 * @brief Destroy a window
 */
Window::~Window() {
    glfwDestroyWindow(_window);
    glfwTerminate();
}

/**
 * @brief Check if the window is open
 * @return true if open, false otherwise
 */
const bool &Window::isOpen() const {
    return _isOpen;
}

/**
 * @brief Close the window
 */
void Window::close() {
    _isOpen = false;
}

/**
 * @brief Get the viewport
 * @return glm::ivec4
 */
const glm::ivec4 &Window::getViewport() const {
    return _viewport;
}

/**
 * @brief Set the viewport
 * @param viewport Viewport
 */
void Window::setViewport(const glm::ivec4 &viewport) {
    _viewport = viewport;
    glViewport(_viewport.x, _viewport.y, _viewport.z, _viewport.w);
}

/**
 * @brief Clear the window
 * @param c Color
 */
void Window::clear(const glm::vec4 &c) const {
    glClearColor(c.r, c.g, c.b, c.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**
 * @brief Display the window
 */
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

/**
 * @brief Set the framerate limit
 * @param limit Framerate limit
 */
void Window::setFramerateLimit(const int &limit) {
    _frameRateLimit = limit;
}

/**
 * @brief Get the framerate
 * @return int
 */
const int Window::getFramerate() const {
    return 1 / _deltaTime;
}

/**
 * @brief Get the delta time
 * @return double
 */
const double &Window::getDeltaTime() const {
    return _deltaTime;
}
