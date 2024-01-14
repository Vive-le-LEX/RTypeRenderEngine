/*
** EPITECH PROJECT, 2023
** RTypeRenderEngine
** File description:
** EventHandler
*/

#ifndef EVENTHANDLER_HPP_
#define EVENTHANDLER_HPP_

#include "RTypeEngine/Window/Events/MouseHandler.hpp"
#include "RTypeEngine/Window/Events/GamepadHandler.hpp"
#include "RTypeEngine/Window/Events/KeyboardHandler.hpp"

namespace RTypeEngine
{
    /**
     * \brief Handles all events related to the window
     * \details It handles global window events such as resize or close.
     * \details For the mouse and keyboard events, it uses the MouseHandler and KeyboardHandler classes.
     */
    class EventHandler {
        public:
            /**
             * @brief Construct a new Event Handler object
             * @details It initializes the mouse and keyboard handlers
             * @param window The window to handle events on
             */
            explicit EventHandler(GLFWwindow *window);
            ~EventHandler() = default;

            /**
             * @brief Set the mouse handler
             * @details This function will set the mouse handler
             * @param mouseHandler The mouse handler to set
             */
            void setMouseHandler(MouseHandler &mouseHandler);

            /**
             * @brief Set the keyboard handler
             * @details This function will set the keyboard handler
             * @param keyboardHandler The keyboard handler to set
             */
            void setKeyboardHandler(KeyboardHandler &keyboardHandler);

            /**
             * @brief Get the mouse handler
             * @details This function will return the mouse handler
             * @return The mouse handler
             */
            [[nodiscard]] MouseHandler &getMouseHandler();

            /**
             * @brief Get the keyboard handler
             * @details This function will return the keyboard handler
             * @return The keyboard handler
             */
            [[nodiscard]] KeyboardHandler &getKeyboardHandler();

            /**
             * @brief Set the window close callback
             * @details This function will set the window close callback
             * @param callback The callback to set
             */
            void setCloseCallback(std::function<void(void)> callback) {
                _closeCallback = callback;
            }

            /**
             * @brief Set the window move callback
             * @details This function will set the window move callback
             * @param callback The callback to set
             */
            void setWindowMoveCallback(std::function<void(int, int)> callback) {
                _windowPosCallback = callback;
            }

            void removeWindowMoveCallback() {
                _windowPosCallback = [](int, int) {};
            }

            /**
             * @brief Update the event handler
             * @note You should never call this function directly. Use @ref RTypeEngine::Window::pollEvents instead
             */
            void update() {
                _keyboardHandler.update();
                _gamepadHandler.update();
            }

            friend void glfwSetWindowCloseCallback(GLFWwindow *window, GLFWwindowclosefun cbfun);
        private:
            MouseHandler _mouseHandler;
            KeyboardHandler _keyboardHandler;
            GamepadHandler _gamepadHandler;

            std::function<void(void)> _closeCallback = []() {};
            std::function<void(int, int)> _resizeCallback = [](int, int) {};
            std::function<void(int, int)> _windowPosCallback = [](int, int) {};
    };
} // namespace RTypeEngine

#endif /* !EVENTHANDLER_HPP_ */
