/*
** EPITECH PROJECT, 2023
** RTypeRenderEngine
** File description:
** KeyboardHandler
*/

#ifndef KEYBOARDHANDLER_HPP_
    #define KEYBOARDHANDLER_HPP_

    #include <GLFW/glfw3.h>

    #include <iostream>
    #include <optional>
    #include <functional>

namespace RTypeEngine {

    /** @brief All information about a key event
     *
     * @details This struct is given as argument to all callbacks of the KeyboardHandler
     *
     * @param id The platform-specific scancode of the key
     * @param key The key
     * @param isShift Is the shift key pressed
     * @param isCtrl Is the ctrl key pressed
     * @param isAlt Is the alt key pressed
     * @param isSuper Is the super key pressed
     * @param isCapsLock Is the caps lock key pressed
     * @param isNumLock Is the num lock key pressed
     */
    typedef struct KeyState_s {
        int id;
        int key;
        bool isShift;
        bool isCtrl;
        bool isAlt;
        bool isSuper;
        bool isCapsLock;
        bool isNumLock;
    } KeyState;

    /** @brief Overload of the << operator for the KeyState struct
     *
     * This function is used to print all the information of the KeyState struct formatted as follow:
     * KeyState {id: <id>, key: <key>, isShift: <isShift>, isCtrl: <isCtrl>, isAlt: <isAlt>, isSuper: <isSuper>, isCapsLock: <isCapsLock>, isNumLock: <isNumLock>}
     *
     * @param os The output stream
     * @param state The KeyState struct
     * @return std::ostream&
     */
    std::ostream &operator<<(std::ostream &os, const KeyState &state);

    template<typename ArgType>
    std::function<void(ArgType)> mergeFunctions(
        const std::function<void(ArgType)>& func1,
        const std::function<void(ArgType)>& func2) {

        return [=](ArgType arg) {
            func1(arg);
            func2(arg);
        };
    }

    using KeyCallback = std::function<void(const KeyState&)>;
    inline KeyCallback emptyKeyCallback = [](const KeyState &ks) {
        (void)ks;
    };

    /** @brief Handles all keyboard events
     */
    class KeyboardHandler {
        public:
            KeyboardHandler();
            ~KeyboardHandler();

            /** @name Key callbacks setters
             * @brief Set the callback for a specific key
             * @param key The key concerned
             * @param callback The callback to set for the key it can be a lambda or a function but it must take a const KeyState reference as parameter
             */
            ///@{
            void setKeyRepeatCallback(const int &key, std::function<void(const KeyState&)> callback);
            void setKeyPressedCallback(const int &key, std::function<void(const KeyState&)> callback);
            void setKeyReleasedCallback(const int &key, std::function<void(const KeyState&)> callback);

            void setDefaultKeyRepeatCallback(std::function<void(const KeyState&)> callback, const bool &override = false);
            void setDefaultKeyPressedCallback(std::function<void(const KeyState&)> callback, const bool &override = false);
            void setDefaultKeyReleasedCallback(std::function<void(const KeyState&)> callback, const bool &override = false);
            ///@}

            /** @name Key callbacks removers
             * @brief Remove the callback for a specific key
             * @param key The key concerned
             */
            ///@{
            void removeKeyPressedCallback(const int &key);
            void removeKeyReleasedCallback(const int &key);
            void removeKeyRepeatCallback(const int &key);
            ///@}

            /** @name Key state getters
             * @brief Get the state of a specific key
             * @param key The key concerned
             * @return bool
             */
            ///@{
            [[nodiscard]] bool isKeyPressed(const int &key) const;
            [[nodiscard]] bool isKeyReleased(const int &key) const;
            [[nodiscard]] bool isKeyRepeat(const int &key) const;
            ///@}

            /** @brief Set the repeat delay
             *
             * @details Set the delay between two key repeat events
             *
             * @param delay The delay in seconds
             */
            void setRepeatDelay(const double &delay);

            /** @brief Get the repeat delay
             *
             * @details Get the delay between two key repeat events
             *
             * @return double
             */
            [[nodiscard]] const double &getRepeatDelay() const;


            friend class EventHandler;
            friend class Window;
            friend void glfwSetKeyCallback(GLFWwindow* window, GLFWkeyfun cbfun);
            friend class WindowConsole;
        protected:
        private:
            void toggleFocus(KeyCallback &keyPressedCallback, KeyCallback &keyRepeatCallback, KeyCallback &keyReleasedCallback) {
                if (shouldFocus) {
                    _defaultKeyPressedCallback = _tmpKeyPressedCallback;
                    _defaultKeyRepeatCallback = _tmpKeyRepeatCallback;
                    _defaultKeyReleasedCallback = _tmpKeyReleasedCallback;
                } else {
                    _tmpKeyPressedCallback = _defaultKeyPressedCallback;
                    _tmpKeyRepeatCallback = _defaultKeyRepeatCallback;
                    _tmpKeyReleasedCallback = _defaultKeyReleasedCallback;

                    _defaultKeyPressedCallback = keyPressedCallback;
                    _defaultKeyRepeatCallback = keyRepeatCallback;
                    _defaultKeyReleasedCallback = keyReleasedCallback;
                }
                shouldFocus = !shouldFocus;
            }
            bool shouldFocus = false;

            /** @brief Update the KeyboardHandler
             *
             * @details Polls all the keys and call the callbacks if needed
             */
            void update();
            GLint _keys[GLFW_KEY_LAST];
            double _repeatDelay = 0.5;
            double _lastRepeat[GLFW_KEY_LAST];

            KeyCallback _defaultKeyPressedCallback = emptyKeyCallback;
            KeyCallback _defaultKeyRepeatCallback = emptyKeyCallback;
            KeyCallback _defaultKeyReleasedCallback = emptyKeyCallback;
            KeyCallback _tmpKeyPressedCallback = emptyKeyCallback;
            KeyCallback _tmpKeyRepeatCallback = emptyKeyCallback;
            KeyCallback _tmpKeyReleasedCallback = emptyKeyCallback;

            std::optional<KeyCallback> _keyPressedCallbacks[GLFW_KEY_LAST];
            std::optional<KeyCallback> _keyReleasedCallbacks[GLFW_KEY_LAST];
            std::optional<KeyCallback> _keyRepeatCallbacks[GLFW_KEY_LAST];
    };
} // namespace RTypeEngine

#endif /* !KEYBOARDHANDLER_HPP_ */
