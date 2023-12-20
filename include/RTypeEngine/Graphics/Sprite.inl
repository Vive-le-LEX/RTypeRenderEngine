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

#include "Sprite.hpp"

using namespace RTypeEngine;

/**
 * @brief Create a sprite
 * @param coordinator Coordinator
 * @return Entity
 */
Entity Sprite::create(Coordinator *coordinator) noexcept {
    return coordinator->createEntity();
}

/**
 * @brief Set the texture of a sprite
 * @param sprite Sprite
 * @param path Path to the texture
 * @param coordinator Coordinator
 */
void Sprite::setTexture(Entity &sprite, const std::string &path, Coordinator *coordinator) noexcept {
    float vertices[] = {
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f
    };

    auto mesh = Mesh::createMesh(vertices);
    auto texture = Texture::createTextureFromFile(path);
    glm::vec3 color{ 1.0f, 1.0f, 1.0f };
    auto shader = Shader::createShader("../Glsl/vertex.glsl", "../Glsl/frag.glsl", color);

    coordinator->addComponent(sprite, mesh);
    coordinator->addComponent(sprite, texture);
    coordinator->addComponent(sprite, shader);
}

/**
 * @brief Set the texture rect of a sprite
 * @param sprite Sprite
 * @param rect Rect
 * @param coordinator Coordinator
 */
void Sprite::setTextureRect(Entity &sprite, const RectI &rect, Coordinator *coordinator) noexcept {
    coordinator->addComponent(sprite, rect);
    auto texture = coordinator->getComponent<TextureComponent>(sprite);
    Texture::setTextureRect(texture, rect);
}

/**
 * @brief Draw a sprite
 * @param entity Entity
 * @param coordinator Coordinator
 */
void Sprite::draw(Entity *entity, Coordinator *coordinator) noexcept {
    auto transform = coordinator->getComponent<TransformComponent>(*entity);
    auto texture = coordinator->getComponent<TextureComponent>(*entity);
    auto shader = coordinator->getComponent<ShaderComponent>(*entity);
    auto mesh = coordinator->getComponent<MeshComponent>(*entity);

    Shader::use(shader);
    Shader::setMat4(shader, "transform", transform.transform);
    glBindTexture(GL_TEXTURE_2D, texture.textureId);
    glBindVertexArray(mesh.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
