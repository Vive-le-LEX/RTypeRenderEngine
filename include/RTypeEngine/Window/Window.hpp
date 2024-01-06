/*
 * Copyright (c) 2023 - Kleo
 * Authors:
 * - LEO VILTARD <leo.viltard@epitech.eu>
 * NOTICE: All information contained herein is, and remains
 * the property of Kleo © and its suppliers, if any.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Kleo ©.
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <thread>
#include <chrono>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "RTypeEngine/Window/EventHandler.hpp"
#include "RTypeEngine/Window/WindowConsole.hpp"

namespace RTypeEngine {
    /**
     * @brief Window class
     * @details This class is used to create and delete windows
     * @details It is also used to set the viewport, clear the window and display the window
     */
    class Window {
    public:
        /**
         * @brief Initialize OpenGL
         * @note This function is called automatically when creating a window for the first time
         */
        static void initOpenGL();

        Window() = delete;

        Window(const Window &cpy) = delete;

        Window &operator=(const Window &src) = delete;

        /**
         * @brief Create a new window
         * @param width
         * @param height
         * @param title
         * @param monitor
         * @param share
         */
        Window(int width, int height, const char *title,
               GLFWmonitor *monitor = NULL, GLFWwindow *share = NULL);

        ~Window();

        /**
         * @brief Get the native window pointer
         * @return GLFWwindow *
         */
        GLFWwindow *getNativeWindow(void) const {
            return _window;
        }

        /**
         * @brief Check if the window is open
         * @return bool
         */
        const bool &isOpen(void) const;

        /**
         * @brief Close the window
         */
        void close(void);

        /**
         * @brief Get the window viewport
         * @return glm::ivec4
         */
        const glm::ivec4 &getViewport(void) const;

        /**
         * @brief Set the window viewport
         * @param viewport
         */
        void setViewport(const glm::ivec4 &viewport);

        /**
         * @brief Clear the window with a color
         * @details The color is black by default
         * @param c The color to clear the window with. Default to black
         */
        void
        clear(const glm::vec4 &c = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)) const;

        /**
         * @brief Display the window
         */
        void display(void);

        /**
         * @brief Get the window framerate limit
         * @return int The framerate limit
         */
        const int getFramerate(void) const;

        /**
         * @brief Set the window framerate limit
         * @details The framerate limit is 60 by default and can be set to 0 to enable uncapped framerate
         * @param limit
         */
        void setFramerateLimit(const int &limit);

        /**
         * @brief Get the window delta time
         * @return double
         */
        const double &getDeltaTime(void) const;

        /**
         * @brief Poll the window events
         */
        void pollEvents(void);

        /**
         * @brief Get the window event handler
         * @return EventHandler &
         */
        EventHandler &getEventHandler(void) {
            return *_eventHandler;
        }

        const glm::mat4 &getProjection(void) const {
            return _projection;
        }

        /**
         * @brief Get the window console
         * @return WindowConsole &
         */
        WindowConsole &getWindowConsole(void) {
            return *_windowConsole;
        }

        friend class Sprite;
        friend class Text;

    private:
        std::unique_ptr<EventHandler> _eventHandler;
        std::unique_ptr<WindowConsole> _windowConsole;
        GLFWwindow *_window = NULL;

        static bool _wasInit;
        bool _isOpen;

        glm::ivec4 _viewport;
        glm::mat4 _projection;

        double _deltaTime = 0.0f;

        int _frameRateLimit = 60;

        unsigned int _lastTexture = 0;


        void _setProjection(const glm::mat4 &projection) {
            _projection = projection;
        }

        void _initMembers(void);
    };
} // namespace RTypeEngine

#endif /* !WINDOW_HPP_ */
