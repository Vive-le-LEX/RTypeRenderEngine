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


namespace RTypeEngine {

    /**
     * \brief ShaderComponent
     * \details This struct is used to store the shader id and the color of the shader
     * \param shaderId Shader id
     * \param color Color of the shader
     */
    struct ShaderComponent {
        GLuint shaderId;
        glm::vec3 color;
    };

    /**
     * \brief Shader static class
     * \details This class is used to create and delete shaders
     * \details It is also used to set the shader matrix
     */
    class Shader {
    public:
        static ShaderComponent createShader(const std::string &vertexPath,
                                            const std::string &fragmentPath,
                                            glm::vec3 &color);

        static void setMat4(ShaderComponent &shader, const std::string &name,
                            const glm::mat4 &mat);

        static void deleteShader(ShaderComponent &shader);

        static void use(ShaderComponent &shader);

        static GLuint _id;
    private:
    };

}
