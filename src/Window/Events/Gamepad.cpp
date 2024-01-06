/*
** EPITECH PROJECT, 2024
** RTypeRenderEngine
** File description:
** Gamepad
*/

#include "RTypeEngine/Window/Events/Gamepad.hpp"

namespace RTypeEngine {
    Gamepad::Gamepad(const int &id) : _id(id) {
        _name = glfwGetGamepadName(id);
        _virtualMouse = nullptr;
        glfwGetGamepadState(_id, &_state);

        for (int i = 0; i < GLFW_GAMEPAD_BUTTON_LAST + 1; i++) {
            _buttons[i] = _state.buttons[i];
        }
        for (int i = 0; i < GLFW_GAMEPAD_AXIS_LAST + 1; i++) {
            _axes[i] = _state.axes[i];
        }
        enableVirtualMouse();
    }

    Gamepad::~Gamepad() {
    }

    void Gamepad::enableVirtualMouse() {
        if (_virtualMouse == nullptr) {
            _virtualMouse = new VirtualMouse(glfwGetCurrentContext());
            addAxisMoveCallback(GamepadAxis::LEFT_X, &_virtualMoveCallback);
            addAxisMoveCallback(GamepadAxis::LEFT_Y, &_virtualMoveCallback);
            addButtonPressCallback(GamepadButton::X, &_virtualClickCallback);
        }
    }

    void Gamepad::disableVirtualMouse() {
        if (_virtualMouse != nullptr) {
            removeAxisMoveCallback(GamepadAxis::LEFT_X, &_virtualMoveCallback);
            removeAxisMoveCallback(GamepadAxis::LEFT_Y, &_virtualMoveCallback);
            removeButtonPressCallback(GamepadButton::X, &_virtualClickCallback);
            delete _virtualMouse;
            _virtualMouse = nullptr;
        }
    }

    const char *Gamepad::getName() const {
        return _name;
    }

    const int &Gamepad::getId() const {
        return _id;
    }

    void Gamepad::_update() {
        int res = glfwGetGamepadState(_id, &_state);
        for (int i = 0; i < GLFW_GAMEPAD_BUTTON_LAST + 1; i++) {
            u_char buttonState = _state.buttons[i];
            if (buttonState == GLFW_PRESS && _buttons[i] == GLFW_RELEASE) {
                _buttons[i] = GLFW_PRESS;
                if (_buttonPressCallbacks.find(static_cast<GamepadButton>(i)) != _buttonPressCallbacks.end()) {
                    for (auto &callback : _buttonPressCallbacks[static_cast<GamepadButton>(i)]) {
                        (*callback)(static_cast<GamepadButton>(i));
                    }
                }
            } else if (buttonState == GLFW_RELEASE && _buttons[i] == GLFW_PRESS) {
                _buttons[i] = GLFW_RELEASE;
                if (_buttonReleaseCallbacks.find(static_cast<GamepadButton>(i)) != _buttonReleaseCallbacks.end()) {
                    for (auto &callback : _buttonReleaseCallbacks[static_cast<GamepadButton>(i)]) {
                        (*callback)(static_cast<GamepadButton>(i));
                    }
                }
            } else if (buttonState == GLFW_PRESS && _buttons[i] == GLFW_PRESS) {
                if (_buttonMaintainCallbacks.find(static_cast<GamepadButton>(i)) != _buttonMaintainCallbacks.end()) {
                    for (auto &callback : _buttonMaintainCallbacks[static_cast<GamepadButton>(i)]) {
                        (*callback)(static_cast<GamepadButton>(i));
                    }
                }
            }
        }
        for (int i = 0; i < GLFW_GAMEPAD_AXIS_LAST + 1; i++) {
            float axisState = _state.axes[i];
            float diff = std::abs(axisState - _axes[i]);
            if (diff > std::numeric_limits<float>::epsilon()) {
                _axes[i] = axisState;
                if (_axisMoveCallbacks.find(static_cast<GamepadAxis>(i)) != _axisMoveCallbacks.end()) {
                    for (auto &callback : _axisMoveCallbacks[static_cast<GamepadAxis>(i)]) {
                        (*callback)(static_cast<GamepadAxis>(i));
                    }
                }
            }
        }
    }

    void Gamepad::addButtonPressCallback(const GamepadButton &button, GamepadButtonCallback *callback) {
        _buttonPressCallbacks[button].push_back(callback);
    }

    void Gamepad::addButtonReleaseCallback(const GamepadButton &button, GamepadButtonCallback *callback) {
        _buttonReleaseCallbacks[button].push_back(callback);
    }

    void Gamepad::addButtonMaintainCallback(const GamepadButton &button, GamepadButtonCallback *callback) {
        _buttonMaintainCallbacks[button].push_back(callback);
    }

    void Gamepad::addAxisMoveCallback(const GamepadAxis &axis, GamepadAxisCallback *callback) {
        _axisMoveCallbacks[axis].push_back(callback);
    }

    void Gamepad::removeButtonPressCallback(const GamepadButton &button, GamepadButtonCallback *callback) {
        auto &callbacks = _buttonPressCallbacks[button];
        auto it = std::find(callbacks.begin(), callbacks.end(), callback);
        if (it != callbacks.end()) {
            callbacks.erase(it);
        }
    }

    void Gamepad::removeButtonReleaseCallback(const GamepadButton &button, GamepadButtonCallback *callback) {
        auto &callbacks = _buttonReleaseCallbacks[button];
        auto it = std::find(callbacks.begin(), callbacks.end(), callback);
        if (it != callbacks.end()) {
            callbacks.erase(it);
        }
    }

    void Gamepad::removeButtonMaintainCallback(const GamepadButton &button, GamepadButtonCallback *callback) {
        auto &callbacks = _buttonMaintainCallbacks[button];
        auto it = std::find(callbacks.begin(), callbacks.end(), callback);
        if (it != callbacks.end()) {
            callbacks.erase(it);
        }
    }

    void Gamepad::removeAxisMoveCallback(const GamepadAxis &axis, GamepadAxisCallback *callback) {
        auto &callbacks = _axisMoveCallbacks[axis];
        auto it = std::find(callbacks.begin(), callbacks.end(), callback);
        if (it != callbacks.end()) {
            callbacks.erase(it);
        }
    }
}  // namespace RTypeEngine
