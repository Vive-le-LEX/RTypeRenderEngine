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

#include "Mesh.hpp"

using namespace RTypeEngine;

/**
 * @brief Create a mesh
 * @param vertices Vertices array
 * @return Mesh
 */
MeshComponent Mesh::createMesh(const float *vertices) noexcept {
    MeshComponent mesh = {0, 0};

    glGenVertexArrays(1, &mesh.VAO);
    glBindVertexArray(mesh.VAO);

    glGenBuffers(1, &mesh.VBO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *) (3 * sizeof(float)));

    glBindVertexArray(0);

    return mesh;
}

/**
 * @brief Delete a mesh
 * @param mesh Mesh to delete
 */
void Mesh::deleteMesh(MeshComponent &mesh) noexcept {
    glDeleteVertexArrays(1, &mesh.VAO);
    glDeleteBuffers(1, &mesh.VBO);
}

/**
 * @brief Bind a mesh
 * @param mesh Mesh to bind
 */
void Mesh::bindMesh(MeshComponent &mesh) noexcept {
    glBindVertexArray(mesh.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
}

/**
 * @brief Unbind meshes
 */
void Mesh::unbindMesh() noexcept {
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
