/*
** EPITECH PROJECT, 2024
** RTypeRenderEngine
** File description:
** VirtualMouse
*/

#include "RTypeEngine/System/VirtualMouse.hpp"

VirtualMouse::VirtualMouse(GLFWwindow *window)
{
    _window = window;
    _position = glm::vec2(0, 0);
}

VirtualMouse::~VirtualMouse()
{
}

void VirtualMouse::click()
{
    auto oldCallback = glfwSetMouseButtonCallback(_window, _emptyMouseCallback);

    if (oldCallback)
        oldCallback(_window, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS, 0);

    glfwSetMouseButtonCallback(_window, oldCallback);
}

void VirtualMouse::setPosition(const glm::vec2 &position)
{
    auto oldCallback = glfwSetCursorPosCallback(_window, _emptyCursorPosCallback);
    if (oldCallback)
        oldCallback(_window, position.x, position.y);
    _position = position;
    glfwSetCursorPos(_window, position.x, position.y);
    glfwSetCursorPosCallback(_window, oldCallback);
}
