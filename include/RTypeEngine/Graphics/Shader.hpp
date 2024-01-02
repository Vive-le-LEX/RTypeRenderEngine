/*
 * Copyright (c) 2023 - Kleo
 * Authors:
 * - LEO VILTARD <leo.viltard@epitech.eu>
 * NOTICE: All information contained herein is, and remains
 * the property of Kleo © and its suppliers, if any.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Kleo ©.
*/

#pragma once

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>


namespace RTypeEngine {

    /**
     * @brief ShaderComponent
     * @details This struct is used to store the shader id and the color of the shader
     */
    struct ShaderComponent {
        GLuint shaderId; /**< The OpenGL shader id */
    };

    /**
     * @brief Shader static class
     * @details This class is used to create and delete shaders
     * @details It is also used to set the shader matrix
     * @code{.cpp}
     * auto shader = RTypeEngine::Shader::createShaderFromFile("path/to/vertex/shader", "path/to/fragment/shader");
     * RTypeEngine::Shader::deleteShader(shader);
     * @endcode
     */
    class Shader {
    public:
        Shader() = delete;
        ~Shader() = delete;

        /**
         * @brief Create a shader from a file
         * @param vertexPath Path to the vertex shader
         * @param fragmentPath Path to the fragment shader
         * @return ShaderComponent
         */
        static ShaderComponent createShaderFromFile(const std::string &vertexPath,
                                            const std::string &fragmentPath) {
            ShaderComponent shader;
            std::string vertexCode;
            std::string fragmentCode;
            std::ifstream vShaderFile;
            std::ifstream fShaderFile;

            vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            try {
                vShaderFile.open(vertexPath);
                fShaderFile.open(fragmentPath);
                std::stringstream vShaderStream, fShaderStream;
                vShaderStream << vShaderFile.rdbuf();
                fShaderStream << fShaderFile.rdbuf();
                vShaderFile.close();
                fShaderFile.close();
                vertexCode = vShaderStream.str();
                fragmentCode = fShaderStream.str();

                const char *vShaderCode = vertexCode.c_str();
                const char *fShaderCode = fragmentCode.c_str();

                return createShaderFromMemory(vShaderCode, fShaderCode);
            } catch (std::ifstream::failure &e) {
                std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
            }

            return shader;
        }

        /**
         * @brief Create a shader from a string
         * @param vertexCode The vertex shader code
         * @param fragmentCode The fragment shader code
        */
       static ShaderComponent createShaderFromMemory(const std::string &vertexCode,
                                            const std::string &fragmentCode) {
            ShaderComponent shader;

            const char *vShaderCode = vertexCode.c_str();
            const char *fShaderCode = fragmentCode.c_str();

            GLuint vertex, fragment;
            GLint success;
            GLchar infoLog[512];

            vertex = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex, 1, &vShaderCode, nullptr);
            glCompileShader(vertex);
            glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
                std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                          << infoLog << std::endl;
            }

            fragment = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment, 1, &fShaderCode, nullptr);
            glCompileShader(fragment);
            glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
                std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                          << infoLog << std::endl;
            }

            shader.shaderId = glCreateProgram();
            glAttachShader(shader.shaderId, vertex);
            glAttachShader(shader.shaderId, fragment);
            glLinkProgram(shader.shaderId);
            glGetProgramiv(shader.shaderId, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader.shaderId, 512, nullptr, infoLog);
                std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                          << infoLog << std::endl;
            }

            glDeleteShader(vertex);
            glDeleteShader(fragment);

            return shader;
        }

        /**
         * @brief Set the shader matrix
         * @param shader The shader to set
         * @param name The name of the uniform matrix in the shader
         * @param mat The matrix to set
         */
        static void setMat4(ShaderComponent &shader, const std::string &name,
                            const glm::mat4 &mat);

        /**
         * @brief Delete a shader
         * @param shader The shader to delete
         */
        static void deleteShader(ShaderComponent &shader) {
            glDeleteProgram(shader.shaderId);
        }
    private:
    };
}
