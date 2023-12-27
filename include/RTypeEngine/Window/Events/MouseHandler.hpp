/*
** EPITECH PROJECT, 2023
** opengl
** File description:
** MouseHandler
*/

#ifndef MOUSEHANDLER_HPP_
    #define MOUSEHANDLER_HPP_

    #include <vector>
    #include <iostream>
    #include <optional>
    #include <functional>
    #include <glm/glm.hpp>
    #include <GLFW/glfw3.h>

namespace RTypeEngine
{
    using MouseMovedCallback = std::function<void(glm::vec2)>;
    /// @brief The cursor mode
    enum CursorMode {
        NORMAL = GLFW_CURSOR_NORMAL, /*!< The cursor is visible and behaves normally. */
        HIDDEN = GLFW_CURSOR_HIDDEN, /*!< The cursor is hidden when over the client area of the window but is not restricted to that area, and behaves normally otherwise. */
        DISABLED = GLFW_CURSOR_DISABLED /*!< The cursor is hidden when over the client area of the window but is not restricted to that area, and when moved offers no visual indication of its position to the user. */
    };

    /// @brief The mouse buttons
    enum MouseClick {
        LEFT = GLFW_MOUSE_BUTTON_LEFT,
        RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
        MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE,
        BUTTON4 = GLFW_MOUSE_BUTTON_4,
        BUTTON5 = GLFW_MOUSE_BUTTON_5,
        BUTTON6 = GLFW_MOUSE_BUTTON_6,
        BUTTON7 = GLFW_MOUSE_BUTTON_7,
        BUTTON8 = GLFW_MOUSE_BUTTON_8,
        NB_BUTTONS = BUTTON8 + 1,
    };

    /// @brief The mouse click types
    enum MouseClickType {
        MOUSE_PRESS = GLFW_PRESS,
        MOUSE_RELEASE = GLFW_RELEASE,
        MOUSE_REPEAT = GLFW_REPEAT,
        MOUSE_TYPE_LAST = MOUSE_REPEAT + 1
    };

    /**
     * @brief Handles all mouse events
     * @details It handles all mouse events such as mouse move, mouse click, mouse scroll, etc.
     * @details It also handles the cursor mode.
     * @details Mouse buttons are handled by this class
     */
    class MouseHandler {
        public:
            MouseHandler();
            ~MouseHandler() = default;
            /** @name Raw motion
             */
            ///@{
            /**
             * @brief Check if the raw motion is supported
             * @return bool
             */
            const bool &canUseRawMotion(void) const;

            /**
             * @brief Check if the raw motion is enabled
             * @return bool
             */
            const bool &isUsingRawMotion(void) const;

            /**
             * @brief Enable or disable the raw motion
             * @param rawInput
             */
            void setRawMotionUse(const bool &rawInput);
            ///@}

            /** @name Cursor mode
             * @brief Getters and setters for the cursor mode
             */
            ///@{
            /**
             * @brief Get the cursor mode
             * @return CursorMode
             */
            const CursorMode &getCursorMode(void) const;

            /**
             * @brief Set the cursor mode
             * @param mode
             */
            void setCursorMode(const CursorMode &mode);
            ///@}

            /**
             * @brief Sets the mouse scroll callback
             * @param callback The callback taking the x and y offset as parameters
             */
            void setMouseScrollCallback(const std::function<void(const double&, const double&)> &callback);
            /**
             * @brief Removes the mouse scroll callback
             */
            void removeMouseScrollCallback(void);

            /**
             * @brief Get the last mouse position
             * @return glm::vec2
             */
            const glm::vec2 &getLastMousePos(void) const;

            /** @name Mouse move callbacks setters & removers
             */
            ///@{
            void setMouseMovedCallback(const MouseMovedCallback& callback);
            void removeMouseMovedCallback(void);
            ///@}

            /** @name Mouse enter callbacks setters & removers
             * @brief Set the callback for when the mouse enters the window
             */
            ///@{
            void setMouseEnterCallback(const std::function<void()> &callback);
            void removeMouseEnterCallback(void);
            ///@}

            /** @name Mouse leave callbacks setters & removers
             * @brief Set the callback for when the mouse leaves the window
             */
            void setMouseLeaveCallback(const std::function<void()> &callback);
            void removeMouseLeaveCallback(void);
            ///@}

            /** @name Mouse click callbacks setters & removers
             * @brief Set the callback for when a mouse button is pressed or released
             */
            ///@{
            void setMouseClickCallback(const MouseClick &button, const MouseClickType &type, const std::function<void()> &callback);
            void removeMouseClickCallback(const MouseClick &button, const MouseClickType &type);
            ///@}

            /**
             * @brief Returns True if the mouse is inside the window
             * @return bool
             */
            const bool &isMouseEntered(void) const {
                return _mouseIn;
            }

            /**
             * @brief Returns the last mouse modifiers
             * @return int
             */
            const int &getLastMouseModifiers(void) const {
                return _lastMouseModifiers;
            }

            friend class EventHandler;
            friend void glfwSetCursorEnterCallback(GLFWwindow *window, int entered);
            friend void glfwSetCursorPosCallback(GLFWwindow *window, GLFWcursorposfun cbfun);
            friend void glfwSetMouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
        private:
            bool _rawInput = false;
            bool _canUseRawInput = glfwRawMouseMotionSupported();
            bool _mouseIn = false;
            int _lastMouseModifiers = 0;

            std::optional<std::function<void(const double&, const double&)>> _mouseScrollCallback = std::nullopt;
            std::optional<MouseMovedCallback> _mouseMovedCallback = std::nullopt;

            std::optional<std::function<void()>> _mouseClickEvents[MOUSE_TYPE_LAST][NB_BUTTONS];

            std::optional<std::function<void()>> _mouseEnterCallback = std::nullopt;
            std::optional<std::function<void()>> _mouseLeaveCallback = std::nullopt;

            CursorMode _cursorMode = CursorMode::NORMAL;
            glm::vec2 _lastMousePos = glm::vec2(0.0f, 0.0f);

            void updateMousePos(const double &x, const double &y);
            void updateMouseEnter(const bool &entered);
            void updateMouseClick(const int &button, const int &type, const int &mods);
            void updateMouseScroll(const double &x, const double &y);
    };
} // namespace RTypeEngine

#endif /* !MOUSEHANDLER_HPP_ */
