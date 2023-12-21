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

#include "Shader.hpp"

using namespace RTypeEngine;


/**
 * @brief Create a shader object
 * @param vertexPath Path to the vertex shader file
 * @param fragmentPath Path to the fragment shader file
 * @param color Color of the shader
 * @return Shader object
 */
ShaderComponent Shader::createShader(const std::string &vertexPath,
                                     const std::string &fragmentPath,
                                     glm::vec3 &color) {
    ShaderComponent shader{};
    int successStatus = 1;
    char infoLog[512];
    std::ifstream vertexFile(vertexPath);
    std::ifstream fragmentFile(fragmentPath);

    if (!vertexFile.is_open() || !fragmentFile.is_open()) {
        std::cerr << "Failed to open shader files" << std::endl;

        return shader;
    }

    std::string vertexSource(
            (std::istreambuf_iterator<char>(vertexFile)),
            std::istreambuf_iterator<char>());
    std::string fragmentSource(
            (std::istreambuf_iterator<char>(fragmentFile)),
            std::istreambuf_iterator<char>());
    const GLchar *vertexSourceC = vertexSource.c_str();
    const GLchar *fragmentSourceC = fragmentSource.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSourceC, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successStatus);
    if (!successStatus) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "Failed to compile vertex shader" << std::endl;
        std::cerr << infoLog << std::endl;
        return shader;
    }
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSourceC, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successStatus);
    if (!successStatus) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "Failed to compile vertex shader" << std::endl;
        std::cerr << infoLog << std::endl;
        return shader;
    }

    _id = glCreateProgram();
    shader.shaderId = _id;
    shader.color = color;
    glAttachShader(_id, vertexShader);
    glAttachShader(_id, fragmentShader);
    glLinkProgram(_id);
    glGetProgramiv(_id, GL_LINK_STATUS, &successStatus);
    if (!successStatus) {
        glGetProgramInfoLog(_id, 512, NULL, infoLog);
        std::cerr << "Failed to link shader program" << std::endl;
        std::cerr << infoLog << std::endl;
        return shader;
    }
    return shader;
}

/**
 * @brief Delete a shader
 * @param shader Shader to delete
 */
void Shader::deleteShader(ShaderComponent &shader) {
    glDeleteProgram(shader.shaderId);
}

/**
 * @brief Use a shader
 * @param shader Shader to use
 */
void Shader::use(ShaderComponent &shader) {
    glUseProgram(shader.shaderId);
}

/**
 * @brief Set the shader matrix
 * @param shader Shader to use
 * @param name Name of the matrix
 * @param mat Matrix to set
 */
void Shader::setMat4(ShaderComponent &shader, const std::string &name,
                     const glm::mat4 &mat) {
    glUniformMatrix4fv(glGetUniformLocation(shader.shaderId, name.c_str()), 1,
                       GL_FALSE,
                       glm::value_ptr(mat));
}
