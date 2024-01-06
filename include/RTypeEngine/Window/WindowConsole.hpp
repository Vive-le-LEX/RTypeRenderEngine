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
    class WindowConsole {
    public:
        WindowConsole(GLFWwindow *window, glm::mat4 *projection, double *deltaTime, KeyboardHandler &keyboardHandler);
        ~WindowConsole();

        void switchState();
        const bool isOpen();

        const void display();

        void registerProgram(LuaProgram *program) {
            _programs[program->getName()] = program;
        }
    protected:
    private:
        void add_prev_line(const std::string &line);

        KeyboardHandler *_keyboardHandler;
        Font _font = Font::createFont("/home/qbriand/delivery/RType/RTypeRenderEngine/gameExample/RTypeGame/COMIC.TTF");
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
