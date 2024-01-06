/*
** EPITECH PROJECT, 2024
** RTypeRenderEngine
** File description:
** GamepadHandler
*/

#ifndef GAMEPADHANDLER_HPP_
    #define GAMEPADHANDLER_HPP_

    #include <array>
    #include <iostream>
    #include <GLFW/glfw3.h>

    #include "RTypeEngine/Window/Events/Gamepad.hpp"

namespace RTypeEngine
{
    class GamepadHandler {
        public:
            GamepadHandler();
            ~GamepadHandler();

            friend class EventHandler;
            friend void glfwSetJoystickCallback(int id, int event);
        protected:
        private:
            void update();

            void _removeGamepad(const int &id);
            void _addGamepad(const int &id);

            std::array<Gamepad*, GLFW_JOYSTICK_LAST + 1> _gamepads;
    };
} // namespace RTypeEngine

#endif /* !GAMEPADHANDLER_HPP_ */
