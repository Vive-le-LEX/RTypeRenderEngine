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

    void KeyboardHandler::update()
    {
        for (int i = 0; i < GLFW_KEY_LAST; i++) {
            auto &pressCallback = _keyPressedCallbacks[i];
            auto &releaseCallback = _keyReleasedCallbacks[i];
            auto &repeatCallback = _keyRepeatCallbacks[i];
            bool hasPressCallback = pressCallback.has_value();
            bool hasReleaseCallback = releaseCallback.has_value();
            bool hasRepeatCallback = repeatCallback.has_value();

            if (!hasPressCallback && !hasReleaseCallback && !hasRepeatCallback)
                continue;
            int newKeyState = glfwGetKey(glfwGetCurrentContext(), i);
            int keycode = glfwGetKeyScancode(i);
            KeyState ks = {
                .id = keycode,
                .key = i,
                .isShift = (bool)(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS),
                .isCtrl = (bool)(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS),
                .isAlt = (bool)(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_ALT) == GLFW_PRESS || glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT_ALT) == GLFW_PRESS),
                .isSuper = (bool)(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_SUPER) == GLFW_PRESS || glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT_SUPER) == GLFW_PRESS),
                .isCapsLock = (bool)(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_CAPS_LOCK) == GLFW_PRESS),
                .isNumLock = (bool)(glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_NUM_LOCK) == GLFW_PRESS)
            };
            if (newKeyState == GLFW_PRESS && _keys[i] == GLFW_REPEAT && hasRepeatCallback) {
                repeatCallback.value()(ks);
            } else if ((hasPressCallback || hasRepeatCallback) && newKeyState == GLFW_PRESS) {
                if (_keys[i] == GLFW_RELEASE && hasPressCallback)
                    pressCallback.value()(ks);
                if (_keys[i] == GLFW_PRESS && hasRepeatCallback) {
                    _keys[i] = GLFW_REPEAT;
                    repeatCallback.value()(ks);
                }
            } else if (hasReleaseCallback && newKeyState == GLFW_RELEASE && _keys[i] == GLFW_PRESS) {
                releaseCallback.value()(ks);
            }
            _keys[i] = newKeyState;
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
