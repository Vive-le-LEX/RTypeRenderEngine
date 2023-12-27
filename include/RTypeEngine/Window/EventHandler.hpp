/*
** EPITECH PROJECT, 2023
** RTypeRenderEngine
** File description:
** EventHandler
*/

#ifndef EVENTHANDLER_HPP_
#define EVENTHANDLER_HPP_

#include "RTypeEngine/Window/Events/MouseHandler.hpp"
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
            EventHandler(GLFWwindow *window);
            ~EventHandler() = default;

            void setMouseHandler(MouseHandler &mouseHandler);
            void setKeyboardHandler(KeyboardHandler &keyboardHandler);

            MouseHandler &getMouseHandler();
            KeyboardHandler &getKeyboardHandler();

            void setCloseCallback(std::function<void(void)> callback) {
                _closeCallback = callback;
            }

            friend void glfwSetWindowCloseCallback(GLFWwindow *window, GLFWwindowclosefun cbfun);
        private:
            MouseHandler _mouseHandler;
            KeyboardHandler _keyboardHandler;

            std::function<void(void)> _closeCallback;
            std::function<void(int, int)> _resizeCallback;
    };
} // namespace RTypeEngine

#endif /* !EVENTHANDLER_HPP_ */