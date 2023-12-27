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

#include "glm/glm.hpp"
#include <iostream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

namespace RTypeEngine {

    /**
     *  @brief Mesh component
     *  @param VBO Vertex Buffer Object
     *  @param VAO Vertex Array Object
     *  @param EBO Element Buffer Object
     *  @param vertices Vertices of the mesh
     */
    struct MeshComponent {
        GLuint VBO;
        GLuint VAO;
    };

    /**
     * @brief Mesh static class
     * @details This class is used to create and delete meshes
     * @details It is also used to bind and unbind meshes
     */
    class Mesh {
    public:
        Mesh() = delete;

        ~Mesh() = delete;

        static MeshComponent createMesh(const float *vertices) noexcept;

        static void deleteMesh(MeshComponent &mesh) noexcept;

        static void bindMesh(MeshComponent &mesh) noexcept;

        static void unbindMesh() noexcept;
    };
} // namespace RTypeEngine
