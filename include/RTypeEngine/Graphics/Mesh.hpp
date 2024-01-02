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

#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "RTypeEngine/Window.hpp"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

namespace RTypeEngine {

    /**
     *  @brief Mesh component
     */
    struct MeshComponent {
        GLuint VBO; /**< The OpenGL VBO id */
        GLuint VAO; /**< The OpenGL VAO id */
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

        /**
         * @brief Create a basic rectangle mesh to draw a Sprite (2 triangles)
         * @return MeshComponent
         */
        static MeshComponent createMesh(int memoryMethod = GL_STATIC_DRAW) noexcept {
            MeshComponent mesh;

            float vertices[] = {
                0.0f, 1.0f, 0.0f, 1.0f,
                1.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f, 1.0f,
                1.0f, 1.0f, 1.0f, 1.0f,
                1.0f, 0.0f, 1.0f, 0.0f
            };

            glGenVertexArrays(1, &mesh.VAO);
            glGenBuffers(1, &mesh.VBO);
            glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, memoryMethod);

            glBindVertexArray(mesh.VAO);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
            return mesh;
        }

        /**
         * @brief Delete a mesh
         * @param mesh The mesh to delete
         * @details This function deletes the VAO and the VBO of the mesh
         */
        static void deleteMesh(MeshComponent &mesh) noexcept {
            glDeleteVertexArrays(1, &mesh.VAO);
            glDeleteBuffers(1, &mesh.VBO);
        };

        /**
         * @brief Bind a mesh
         * @param mesh The mesh to bind
         */
        static void bindMesh(MeshComponent &mesh) noexcept {
            glBindVertexArray(mesh.VAO);
        }

        /**
         * @brief Unbind a mesh
        */
        static void unbindMesh() noexcept {
            glBindVertexArray(0);
        }
    };
} // namespace RTypeEngine
