/*
** EPITECH PROJECT, 2023
** RTypeRenderEngine
** File description:
** MouseHandler
*/

#include "RTypeEngine/Window/Events/MouseHandler.hpp"

namespace RTypeEngine {
    MouseHandler::MouseHandler() {
        for (int y = 0; y < MouseClickType::MOUSE_TYPE_LAST; y++)
            for (int x = 0; x < MouseClick::NB_BUTTONS; x++)
                _mouseClickEvents[y][x] = std::nullopt;
    }
    const bool &MouseHandler::canUseRawMotion(void) const {
        return _canUseRawInput;
    }

    const bool &MouseHandler::isUsingRawMotion(void) const {
        return _rawInput;
    }

    void MouseHandler::setRawMotionUse(const bool &rawInput) {
        if (rawInput == _rawInput)
            return;
        if (rawInput) {
            if (!_canUseRawInput)
                std::cerr << "Raw mouse motion is not supported on this platform" << std::endl;
            glfwSetInputMode(glfwGetCurrentContext(), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
        } else {
            glfwSetInputMode(glfwGetCurrentContext(), GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
        }
        _rawInput = rawInput;
    }

    const CursorMode &MouseHandler::getCursorMode(void) const {
        return _cursorMode;
    }

    void MouseHandler::setCursorMode(const CursorMode &mode) {
        if (mode == _cursorMode)
            return;
        glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, mode);
        _cursorMode = mode;
    }

    void MouseHandler::updateMousePos(const double &x, const double &y) {
        static glm::vec2 _deltaMove = glm::vec2(x, y);
        _deltaMove = glm::vec2(x, y) - _lastMousePos;
        if (_mouseMovedCallback.has_value())
            _mouseMovedCallback.value()(_deltaMove);
        _lastMousePos = glm::vec2(x, y);
    }

    void MouseHandler::updateMouseEnter(const bool &entered) {
        if (entered && !_mouseIn) {
            if (_mouseEnterCallback.has_value())
                _mouseEnterCallback.value()();
        } else if (!entered && _mouseIn) {
            if (_mouseLeaveCallback.has_value())
                _mouseLeaveCallback.value()();
        }
        _mouseIn = entered;
    }

    void MouseHandler::updateMouseClick(const int &button, const int &type, const int &mods) {
        _lastMouseModifiers = mods;
        if (_mouseClickEvents[type][button].has_value())
            _mouseClickEvents[type][button].value()();
    }

    void MouseHandler::updateMouseScroll(const double &x, const double &y) {
        if (_mouseScrollCallback.has_value())
            _mouseScrollCallback.value()(x, y);
    }

    void MouseHandler::setMouseScrollCallback(const std::function<void(const double &, const double &)> &callback) {
        _mouseScrollCallback = callback;
    }

    void MouseHandler::removeMouseScrollCallback(void) {
        _mouseScrollCallback = std::nullopt;
    }

    void MouseHandler::setMouseMovedCallback(const MouseMovedCallback &callback) {
        _mouseMovedCallback = callback;
    }

    void MouseHandler::removeMouseMovedCallback(void) {
        _mouseMovedCallback = std::nullopt;
    }

    void MouseHandler::setMouseEnterCallback(const std::function<void()> &callback) {
        _mouseEnterCallback = callback;
    }

    void MouseHandler::removeMouseEnterCallback(void) {
        _mouseEnterCallback = std::nullopt;
    }

    void MouseHandler::setMouseLeaveCallback(const std::function<void()> &callback) {
        _mouseLeaveCallback = callback;
    }

    void MouseHandler::removeMouseLeaveCallback(void) {
        _mouseLeaveCallback = std::nullopt;
    }

    void MouseHandler::setMouseClickCallback(const MouseClick &button, const MouseClickType &type, const std::function<void()> &callback) {
        _mouseClickEvents[type][button] = callback;
    }

    void MouseHandler::removeMouseClickCallback(const MouseClick &button, const MouseClickType &type) {
        _mouseClickEvents[type][button] = std::nullopt;
    }
}  // namespace RTypeEngine
