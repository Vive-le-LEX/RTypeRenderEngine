/*
** EPITECH PROJECT, 2023
** RTypeRenderEngine
** File description:
** Window
*/

#ifndef WINDOW_HPP_
    #define WINDOW_HPP_

    #include <iostream>
    #include <stdexcept>
    #include <glm/glm.hpp>
    #include <glad/glad.h>
    #include <GLFW/glfw3.h>

namespace RTypeEngine
{
    // void onNativeResizeCallback(GLFWwindow *window, int width, int height);

    class Window {
        public:
            static void initOpenGL();

            Window() = delete;
            Window(const Window &cpy) = delete;
            Window &operator=(const Window &src) = delete;

            Window(int width, int height, const char *title, GLFWmonitor *monitor = NULL, GLFWwindow *share = NULL);
            ~Window();

            GLFWwindow *getNativeWindow(void) const {
                return _window;
            }

            bool shouldClose(void) const;
            void close(void);

            const glm::ivec4 &getViewport(void) const;
            void setViewport(const glm::ivec4 &viewport);

            void clear(const glm::vec4 &c = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)) const;

        private:
            GLFWwindow *_window = NULL;
            static bool _wasInit;
            bool _shouldClose;

            glm::ivec4 _viewport;
    };
} // namespace RTypeEngine

#endif /* !WINDOW_HPP_ */
