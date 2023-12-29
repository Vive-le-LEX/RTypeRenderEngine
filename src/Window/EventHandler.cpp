/*
** EPITECH PROJECT, 2023
** RTypeRenderEngine
** File description:
** EventHandler
*/

#include "RTypeEngine/Window/EventHandler.hpp"

namespace RTypeEngine
{
    EventHandler::EventHandler(GLFWwindow *window) : _mouseHandler(), _keyboardHandler()
    {
        glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height) {
            EventHandler *e = static_cast<EventHandler *>(glfwGetWindowUserPointer(window));
            e->_resizeCallback(width, height);
        });
        glfwSetCursorEnterCallback(window, [](GLFWwindow *window, int entered) {
            EventHandler *e = static_cast<EventHandler *>(glfwGetWindowUserPointer(window));
            e->_mouseHandler.updateMouseEnter(entered);
        });
        glfwSetCursorPosCallback(window, [](GLFWwindow *window, double xpos, double ypos) {
            EventHandler *e = static_cast<EventHandler *>(glfwGetWindowUserPointer(window));
            e->_mouseHandler.updateMousePos(xpos, ypos);
        });
        glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int button, int action, int mods) {
            EventHandler *e = static_cast<EventHandler *>(glfwGetWindowUserPointer(window));
            e->_mouseHandler.updateMouseClick(button, action, mods);
        });
        glfwSetScrollCallback(window, [](GLFWwindow *window, double xoffset, double yoffset) {
            EventHandler *e = static_cast<EventHandler *>(glfwGetWindowUserPointer(window));
            e->_mouseHandler.updateMouseScroll(xoffset, yoffset);
        });
        glfwSetWindowCloseCallback(window, [](GLFWwindow *window) {
            EventHandler *e = static_cast<EventHandler *>(glfwGetWindowUserPointer(window));
            e->_closeCallback();
        });
    }

    void EventHandler::setMouseHandler(MouseHandler &mouseHandler)
    {
        _mouseHandler = mouseHandler;
    }

    void EventHandler::setKeyboardHandler(KeyboardHandler &keyboardHandler)
    {
        _keyboardHandler = keyboardHandler;
    }

    MouseHandler &EventHandler::getMouseHandler()
    {
        return _mouseHandler;
    }

    KeyboardHandler &EventHandler::getKeyboardHandler()
    {
        return _keyboardHandler;
    }
} // namespace RTypeEngine
