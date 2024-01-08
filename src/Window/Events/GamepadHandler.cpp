/*
** EPITECH PROJECT, 2024
** RTypeRenderEngine
** File description:
** GamepadHandler
*/

#include "RTypeEngine/Window/Events/GamepadHandler.hpp"

namespace RTypeEngine
{
    GamepadHandler::GamepadHandler()
    {
        for (int i = GLFW_JOYSTICK_1; i < GLFW_JOYSTICK_LAST + 1; i++) {
            if (glfwJoystickPresent(i) && glfwJoystickIsGamepad(i)) {
                _gamepads[i] = new Gamepad(i);
            } else {
                _gamepads[i] = nullptr;
            }
        }
    }

    GamepadHandler::~GamepadHandler()
    {
        for (int i = GLFW_JOYSTICK_1; i < GLFW_JOYSTICK_LAST + 1; i++) {
            if (_gamepads[i] != nullptr) {
                delete _gamepads[i];
            }
        }
    }

    void GamepadHandler::_removeGamepad(const int &id)
    {
        if (_gamepads[id] != nullptr) {
            delete _gamepads[id];
            _gamepads[id] = nullptr;
        }
    }

    void GamepadHandler::_addGamepad(const int &id)
    {
        if (_gamepads[id] == nullptr) {
            _gamepads[id] = new Gamepad(id);
        }
    }

    void GamepadHandler::update()
    {
        for (int i = GLFW_JOYSTICK_1; i < GLFW_JOYSTICK_LAST + 1; i++) {
            if (_gamepads[i] != nullptr) {
                _gamepads[i]->_update();
            }
        }
    }
} // namespace RTypeengine
