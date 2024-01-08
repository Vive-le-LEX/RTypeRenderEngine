/*
** EPITECH PROJECT, 2024
** RTypeRenderEngine
** File description:
** VirtualMouse
*/

#ifndef VIRTUALMOUSE_HPP_
    #define VIRTUALMOUSE_HPP_

    #include <functional>

    #include <GLFW/glfw3.h>
    #include <glm/glm.hpp>

namespace RTypeEngine
{
/**
 * @brief Handles a virtual mouse
 * @details This class is used to handle a virtual mouse. It will redirect a gamepad events to the mouse
 */
class VirtualMouse {
    public:
        /**
         * @brief Construct a new Virtual Mouse object
         * @details The virtual mouse is attached to window
         * @param window The window to handle the mouse on
         */
        VirtualMouse(GLFWwindow *window);
        ~VirtualMouse() = default;

        /**
         * @brief Simulate a click with the mouse
         * @details This function will simulate a click with the mouse
         */
        void click();

        /**
         * @brief Simulate a mouse movement
         * @details This function will set the position of the mouse
         * @param position The position to set
         */
        void setPosition(const glm::vec2 &position);

        /**
         * @brief Get the position of the mouse
         * @details This function will return the position of the mouse
         * @return The position of the mouse
         */
        const glm::vec2 &getPosition() const {
            return _position;
        }

        friend class Gamepad;
    protected:
    private:
        static void _emptyMouseCallback(GLFWwindow *window, int button,
            int action, int mods) {};

        static void _emptyCursorPosCallback(GLFWwindow *window, double xpos,
            double ypos) {};

        GLFWwindow *_window;
        glm::vec2 _position;
};
} /* namespace RTypeEngine */

#endif /* !VIRTUALMOUSE_HPP_ */
