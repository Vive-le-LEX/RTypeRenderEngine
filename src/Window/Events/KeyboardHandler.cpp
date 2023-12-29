/*
** EPITECH PROJECT, 2023
** RTypeRenderEngine
** File description:
** KeyboardHandler
*/

#include "RTypeEngine/Window/Events/KeyboardHandler.hpp"

namespace RTypeEngine
{
    KeyboardHandler::KeyboardHandler()
    {
        for (int i = 0; i < GLFW_KEY_LAST; i++) {
            _keys[i] = GLFW_RELEASE;
            _keyPressedCallbacks[i] = std::nullopt;
            _keyReleasedCallbacks[i] = std::nullopt;
            _keyRepeatCallbacks[i] = std::nullopt;
        }
    }

    KeyboardHandler::~KeyboardHandler()
    {
    }

    void KeyboardHandler::_updateKey(GLFWwindow *window, const int &key, const int &scancode, const int &action, const int &mods)
    {
        if (key < 0 || key >= GLFW_KEY_LAST)
            return;
        KeyState currentState = {
            .id = scancode,
            .key = key,
            .isShift = (bool)(mods & GLFW_MOD_SHIFT),
            .isCtrl = (bool)(mods & GLFW_MOD_CONTROL),
            .isAlt = (bool)(mods & GLFW_MOD_ALT),
            .isSuper = (bool)(mods & GLFW_MOD_SUPER),
            .isCapsLock = (bool)(mods & GLFW_MOD_CAPS_LOCK),
            .isNumLock = (bool)(mods & GLFW_MOD_NUM_LOCK)
        };
        _keys[key] = action;
        if (action == GLFW_PRESS && _keyPressedCallbacks[key].has_value()) {
            _keyPressedCallbacks[key].value()(currentState);
        } else if (action == GLFW_RELEASE && _keyReleasedCallbacks[key].has_value()) {
            _keyReleasedCallbacks[key].value()(currentState);
        }
        if (_keys[key] & (GLFW_PRESS | GLFW_REPEAT) && _keyRepeatCallbacks[key].has_value()) {
            _keyRepeatCallbacks[key].value()(currentState);
        }
    }

    void KeyboardHandler::setKeyPressedCallback(const int &key, std::function<void(const KeyState&)> callback)
    {
        _keyPressedCallbacks[key] = callback;
    }

    void KeyboardHandler::setKeyReleasedCallback(const int &key, std::function<void(const KeyState&)> callback)
    {
        _keyReleasedCallbacks[key] = callback;
    }

    void KeyboardHandler::setKeyRepeatCallback(const int &key, std::function<void(const KeyState&)> callback)
    {
        _keyRepeatCallbacks[key] = callback;
    }

    void KeyboardHandler::removeKeyPressedCallback(const int &key)
    {
        _keyPressedCallbacks[key] = std::nullopt;
    }

    void KeyboardHandler::removeKeyReleasedCallback(const int &key)
    {
        _keyReleasedCallbacks[key] = std::nullopt;
    }

    void KeyboardHandler::removeKeyRepeatCallback(const int &key)
    {
        _keyRepeatCallbacks[key] = std::nullopt;
    }

    bool KeyboardHandler::isKeyPressed(const int &key) const
    {
        return _keys[key] == GLFW_PRESS;
    }

    bool KeyboardHandler::isKeyReleased(const int &key) const
    {
        return _keys[key] == GLFW_RELEASE;
    }

    bool KeyboardHandler::isKeyRepeat(const int &key) const
    {
        return _keys[key] == GLFW_REPEAT;
    }

    std::ostream &operator<<(std::ostream &os, const KeyState &state)
    {
        os << "KeyState { id: " << state.id << ", key: " << state.key << ", isShift: " << state.isShift << ", isCtrl: " << state.isCtrl << ", isAlt: " << state.isAlt << ", isSuper: " << state.isSuper << ", isCapsLock: " << state.isCapsLock << ", isNumLock: " << state.isNumLock << " }";
        return os;
    }
} // namespace RTypeEngine
