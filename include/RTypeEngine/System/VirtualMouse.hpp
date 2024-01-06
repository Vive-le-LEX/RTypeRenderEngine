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

class VirtualMouse {
    public:
        VirtualMouse(GLFWwindow *window);
        ~VirtualMouse();

        void click();
        void setPosition(const glm::vec2 &position);
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

#endif /* !VIRTUALMOUSE_HPP_ */
