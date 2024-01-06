/*
** EPITECH PROJECT, 2024
** RTypeRenderEngine
** File description:
** WindowConsole
*/

#include "RTypeEngine/Window/WindowConsole.hpp"

namespace RTypeEngine {

WindowConsole::WindowConsole(GLFWwindow *win, glm::mat4 *projection, double *deltaTime, KeyboardHandler &keyboardHandler)
    :   _isOpen(false),
        _finishedAnimation(true),
        _deltaTime(deltaTime),
        _keyboardHandler(&keyboardHandler)
{
    _text = new Text("RType> ", _font, glm::vec2(100.0f, 100.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 24);
    _projection = glm::value_ptr(*projection);
    _model = glm::mat4(1.0f);
    int width, height;
    glfwGetWindowSize(win, &width, &height);
    _consoleHeight = height / 2;
    _consoleWidth = width - 20;

    _maxPrevLines = std::floor((float)_consoleHeight / 29.0f) - 1;
    _prevLines.reserve(_maxPrevLines);
    size_t totalSize = _consoleWidth * _consoleHeight * 4;
    _shader = Shader::createShaderFromMemory(_vertexShader, _fragmentShader);
    _mesh = Mesh::createMesh();
    _model[0][0] = _consoleWidth;
    _model[1][1] = _consoleHeight;

    _animationYStateFinished = glm::vec4(10.0f, -_consoleHeight - 10.0f, 0.0f, 1.0f);
    _animationYStateOpen = glm::vec4(10.0f, 75.0f, 0.0f, 1.0f);
    _model[3] = _animationYStateFinished;

    _entryBuffer = "";

    for (int i = 0; i < _maxPrevLines; i++) {
        _prevLines.push_back(nullptr);
    }

    _pressCallback = [&](KeyState state) {
        if (state.key == GLFW_KEY_F10) {
            switchState();
        }
        if (!_isOpen) return;
        if (state.key == GLFW_KEY_ENTER) {
            std::string command = _entryBuffer;
            _entryBuffer = "";
            if (command == "exit") {
                _text->setText("RType> ");
                switchState();
                return;
            } else if (command == "cls" || command == "clear") {
                for (auto &prevLine : _prevLines) {
                    if (prevLine != nullptr) {
                        delete prevLine;
                        prevLine = nullptr;
                    }
                }
                _text->setText("RType> ");
                return;
            }
            add_prev_line(_text->getText());
            if (command == "programs") {
                add_prev_line("  Available programs:");
                for (auto &program : _programs) {
                    add_prev_line("   - " + program.first);
                }
            } else if (command == "help") {
                add_prev_line("  Available commands:");
                add_prev_line("   - exit; close the console");
                add_prev_line("   - cls | clear; clear the console");
                add_prev_line("   - help; display this help");
                add_prev_line("   - programs; list all lua registered programs");
            } else if (_programs.find(command) != _programs.end()) {
                _programs[command]->run();
            }
            _entryBuffer = "";
            _text->setText("RType> ");
        } else if (state.key == GLFW_KEY_BACKSPACE) {
            if (_entryBuffer.size() > 0) {
                _entryBuffer.pop_back();
                _text->setText("RType> " + _entryBuffer);
            }
        } else if (state.key == GLFW_KEY_SPACE) {
            _entryBuffer += " ";
            _text->setText("RType> " + _entryBuffer);
        }
        if (!(state.key > GLFW_KEY_A - 1 && state.key < GLFW_KEY_Z + 1))
            return;
        _entryBuffer += state.isShift ? state.key : state.key + 32;
        _text->setText("RType> " + _entryBuffer);
    };
}

void WindowConsole::add_prev_line(const std::string &line) {
    for (int i = _maxPrevLines - 1; i > 0; i--) {
        _prevLines[i] = _prevLines[i - 1];
        if (_prevLines[i - 1] == nullptr) continue;
        auto &oldPos = _prevLines[i - 1]->getPosition();
        oldPos.y -= 29.0f;
    }
    glm::vec2 pos = _text->getPosition();
    pos.y -= 29.0f;
    _prevLines[0] = new Text(line, _font, pos, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 24);
}

WindowConsole::~WindowConsole() {
}

void WindowConsole::switchState() {
    _finishedAnimation = false;
    _isOpen = !_isOpen;
}

const bool WindowConsole::isOpen() {
    return _isOpen && _finishedAnimation;
}

const void WindowConsole::display() {
    if (!_finishedAnimation) {
        glm::vec4 *target;
        if (_isOpen) target = &_animationYStateOpen;
        else target = &_animationYStateFinished;

        glm::vec4 current = _model[3];
        auto res = glm::mix(current, *target, 10.0f * *_deltaTime);
        _model[3] = res;
        if (glm::distance(_model[3], *target) < 1.0f) {
            _model[3] = *target;
            _finishedAnimation = true;
            _keyboardHandler->toggleFocus(_pressCallback, emptyKeyCallback, emptyKeyCallback);
        }
        res.x += 10.0f;
        res.y += _consoleHeight - 29.0f;
        _text->setPosition(res);

        for (auto &prevLine : _prevLines) {
            if (prevLine != nullptr) {
                res.y -= 29.0f;
                prevLine->setPosition(res);
            }
        }
    }
    if (!_isOpen && _finishedAnimation)
        return;
    glUseProgram(_shader.shaderId);
    _projectionLoc = glGetUniformLocation(_shader.shaderId, "projection");
    int _modelLoc = glGetUniformLocation(_shader.shaderId, "model");
    glUniformMatrix4fv(_projectionLoc, 1, GL_FALSE, _projection);
    glUniformMatrix4fv(_modelLoc, 1, GL_FALSE, glm::value_ptr(_model));
    glBindVertexArray(_mesh.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    _text->draw(_projection);
    for (auto &prevLine : _prevLines) {
        if (prevLine == nullptr) continue;
        prevLine->draw(_projection);
    }
}
}  // namespace RTypeEngine
