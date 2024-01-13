/*
** EPITECH PROJECT, 2024
** RTypeRenderEngine
** File description:
** WindowConsole
*/

#ifndef WINDOWCONSOLE_HPP_
    #define WINDOWCONSOLE_HPP_

    #include <map>
    #include <iostream>
    #include "glad/glad.h"
    #include "GLFW/glfw3.h"
    #include <glm/glm.hpp>
    #include "RTypeEngine/System/Scripting.hpp"
    #include "RTypeEngine/Window/Events/KeyboardHandler.hpp"
    #include "RTypeEngine/Graphics/Transform.hpp"
    #include "RTypeEngine/Graphics/Texture.hpp"
    #include "RTypeEngine/Graphics/Shader.hpp"
    #include "RTypeEngine/Graphics/Mesh.hpp"
    #include "RTypeEngine/Graphics/Text.hpp"

namespace RTypeEngine {
    /**
     * @brief Handles the native console interpreter
     * @details This class is used to handle the console. It will display the console and handle the input
     */
    class WindowConsole {
    public:
        /**
         * @brief Construct a new Window Console object
         * @details This constructor initialize the console with the given parameters
         * @param window The window to display the console on
         * @param projection The projection matrix of the window
         * @param deltaTime The deltaTime of the window
         * @param keyboardHandler The keyboardHandler of the window
         *
         * @note You should never call this constructor directly. Use your Window class to get the console
         */
        WindowConsole(GLFWwindow *window, glm::mat4 *projection, double *deltaTime, KeyboardHandler &keyboardHandler);
        ~WindowConsole() = default;

        /**
         * @brief Switch the console state
         * @details This function will toggle if the console is shown or not
         */
        void switchState();

        /**
         * @brief Check if the console is open
         * @details This function will update the console. It will handle the input and display the console
         */
        const bool isOpen() const;

        /**
         * @brief Draws the console
         * @details This function will draw the console on the window he is attached to
         */
        const void display();

        /**
         * @brief Register a LuaProgram to the console
         * @details This function will register a program to the console. It will be able to be called from the console, list it by typing "help" in the console
         * @details Execute it by just typing the name of the program in the console
         * @param program The pointer to the program to register
         */
        void registerProgram(LuaProgram *program) {
            _programs[program->getName()] = program;
        }
    protected:
    private:
        void add_prev_line(const std::string &line);

        KeyboardHandler *_keyboardHandler;
        Font _font = Font::createFontFromAssets("./INTERNAL_COMIC.TTF");
        Text *_text;

        bool _isOpen;
        bool _finishedAnimation;

        int _consoleWidth;
        int _consoleHeight;

        double *_deltaTime;

        glm::vec4 _animationYStateOpen;
        glm::vec4 _animationYStateFinished;

        std::string _entryBuffer;

        ShaderComponent _shader;
        MeshComponent _mesh;
        int _projectionLoc;
        glm::f32 *_projection;
        glm::mat4 _model;

        std::vector<Text*> _prevLines;
        size_t _maxPrevLines;

        std::map<std::string, LuaProgram*> _programs;
        KeyCallback _pressCallback;

        static constexpr const char *_vertexShader = "#version 330 core\n"
                                                     "layout (location = 0) in vec4 vertex;\n"
                                                     "out vec2 TexCoords;\n"
                                                     "uniform mat4 model;\n"
                                                     "uniform mat4 projection;\n"
                                                     "void main()\n"
                                                     "{\n"
                                                     "    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);\n"
                                                     "    TexCoords = vertex.zw;\n"
                                                     "}\0";
        static constexpr const char *_fragmentShader = "#version 330 core\n"
                                                       "out vec4 FragColor;\n"
                                                       "in vec2 TexCoords;\n"
                                                       "void main()\n"
                                                       "{\n"
                                                       "    FragColor = vec4(0.2, 0.2, 0.2, 0.8);\n"
                                                       "}\n\0";
    };
}  // namespace RTypeEngine
#endif /* !WINDOWCONSOLE_HPP_ */
