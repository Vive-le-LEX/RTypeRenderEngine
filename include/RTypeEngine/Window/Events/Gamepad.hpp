/*
** EPITECH PROJECT, 2024
** RTypeRenderEngine
** File description:
** Gamepad
*/

#ifndef GAMEPAD_HPP_
    #define GAMEPAD_HPP_

    #include <map>
    #include <limits>
    #include <vector>
    #include <iostream>
    #include <functional>
    #include <GLFW/glfw3.h>

    #include "RTypeEngine/System/VirtualMouse.hpp"

namespace RTypeEngine
{
    /**
     * @brief All gamepad buttons
     */
    enum GamepadButton {
        A = GLFW_GAMEPAD_BUTTON_A,
        B = GLFW_GAMEPAD_BUTTON_B,
        X = GLFW_GAMEPAD_BUTTON_X,
        Y = GLFW_GAMEPAD_BUTTON_Y,
        LEFT_BUMPER = GLFW_GAMEPAD_BUTTON_LEFT_BUMPER,
        RIGHT_BUMPER = GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER,
        BACK = GLFW_GAMEPAD_BUTTON_BACK,
        START = GLFW_GAMEPAD_BUTTON_START,
        GUIDE = GLFW_GAMEPAD_BUTTON_GUIDE,
        LEFT_THUMB = GLFW_GAMEPAD_BUTTON_LEFT_THUMB,
        RIGHT_THUMB = GLFW_GAMEPAD_BUTTON_RIGHT_THUMB,
        DPAD_UP = GLFW_GAMEPAD_BUTTON_DPAD_UP,
        DPAD_RIGHT = GLFW_GAMEPAD_BUTTON_DPAD_RIGHT,
        DPAD_DOWN = GLFW_GAMEPAD_BUTTON_DPAD_DOWN,
        DPAD_LEFT = GLFW_GAMEPAD_BUTTON_DPAD_LEFT,
    };

    /**
     * @brief All gamepad axis
     */
    enum GamepadAxis {
        LEFT_X = GLFW_GAMEPAD_AXIS_LEFT_X,
        LEFT_Y = GLFW_GAMEPAD_AXIS_LEFT_Y,
        RIGHT_X = GLFW_GAMEPAD_AXIS_RIGHT_X,
        RIGHT_Y = GLFW_GAMEPAD_AXIS_RIGHT_Y,
        LEFT_TRIGGER = GLFW_GAMEPAD_AXIS_LEFT_TRIGGER,
        RIGHT_TRIGGER = GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER,
    };

    using GamepadButtonCallback = std::function<void(const GamepadButton&)>;
    using GamepadAxisCallback = std::function<void(const GamepadAxis&)>;

    /**
     * @brief Handles a gamepad
     */
    class Gamepad {
        public:
            /**
             * @brief Construct a new Gamepad object
             * @param id The id of the gamepad
             * @note This shouldn't be used directly
             */
            Gamepad(const int &id);
            ~Gamepad() = default;

            /**
             * @brief Get the name of the gamepad
             * @return The name of the gamepad
             */
            const char *getName() const;

            /**
             * @brief Get the id of the gamepad
             * @return The id of the gamepad
             */
            const int &getId() const;

            /** @name Button callbacks adders
             * @brief Add a callback to a button event
             * @param button The GamepadButton affected
             * @param callback The GamepadButtonCallback to add to it
             */
            ///@{
            void addButtonPressCallback(const GamepadButton &button, GamepadButtonCallback *callback);
            void addButtonReleaseCallback(const GamepadButton &button, GamepadButtonCallback *callback);
            void addButtonMaintainCallback(const GamepadButton &button, GamepadButtonCallback *callback);
            ///@}

            /** @name Axis callbacks adder
             * @brief Add a callback to an axis event
             * @param axis The GamepadAxis affected
             * @param callback The pointer to a GamepadAxisCallback
             */
            void addAxisMoveCallback(const GamepadAxis &axis, GamepadAxisCallback *callback);

            /** @name Button callbacks removers
             * @brief Remove a callback from a button event
             * @param button The GamepadButton affected
             * @param callback The pointer to a GamepadButtonCallback
             */
            ///@{
            void removeButtonPressCallback(const GamepadButton &button, GamepadButtonCallback *callback);
            void removeButtonReleaseCallback(const GamepadButton &button, GamepadButtonCallback *callback);
            void removeButtonMaintainCallback(const GamepadButton &button, GamepadButtonCallback *callback);
            ///@}

            /** @name Axis callbacks remover
             * @brief Remove a callback from an axis event
             * @param axis The GamepadAxis affected
             * @param callback The pointer to a GamepadAxisCallback
             */
            void removeAxisMoveCallback(const GamepadAxis &axis, GamepadAxisCallback *callback);

            /**
             * @brief Enable the virtual mouse
            */
            void enableVirtualMouse(void);
            /**
             * @brief Disable the virtual mouse
             */
            void disableVirtualMouse(void);


            friend class GamepadHandler;
        protected:
        private:
            VirtualMouse *_virtualMouse;

            GamepadAxisCallback _virtualMoveCallback = GamepadAxisCallback(
                [this](const GamepadAxis &axis) {
                    auto pos = _virtualMouse->getPosition();
                    _virtualMouse->setPosition(glm::vec2(
                        _axes[GamepadAxis::LEFT_X] + pos.x,
                        _axes[GamepadAxis::LEFT_Y] + pos.y
                    ));
                }
            );
            GamepadButtonCallback _virtualClickCallback = GamepadButtonCallback(
                [this](const GamepadButton &button) {
                    _virtualMouse->click();
                }
            );

            void _update();
            unsigned char _buttons[GLFW_GAMEPAD_BUTTON_LAST + 1];
            float _axes[GLFW_GAMEPAD_AXIS_LAST + 1];

            std::map<GamepadButton, std::vector<GamepadButtonCallback*>> _buttonPressCallbacks;
            std::map<GamepadButton, std::vector<GamepadButtonCallback*>> _buttonReleaseCallbacks;
            std::map<GamepadButton, std::vector<GamepadButtonCallback*>> _buttonMaintainCallbacks;
            std::map<GamepadAxis, std::vector<GamepadAxisCallback*>> _axisMoveCallbacks;

            int _id;
            const char *_name;
            GLFWgamepadstate _state;
    };
} // namespace RTypeEngine

#endif /* !GAMEPAD_HPP_ */
