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

#include "RTypeECS/Types.hpp"
#include "RTypeECS/Coordinator.hpp"

namespace RTypeEngine {
    /**
     * @brief Wrapper around the ECS entity for Sprites
     * @details This Sprite class is a wrapper around the entity handled by the ECS and the registered systems
     * @details It also has a static method draw that draws the sprite
     *
     * @code{.cpp}
     * auto texture = RTypeEngine::Texture::createTextureFromFile("path/to/texture.png");
     * auto shader = RTypeEngine::Shader::createShaderFromFile("path/to/vertex/shader", "path/to/fragment/shader");
     *
     * auto sprite = RTypeEngine::Sprite(texture, shader);
     * RTypeEngine::Sprite::draw(sprite);
     * @endcode
     */
    class Sprite {
        public:
            /**
             * @brief Create a sprite
             * @param textureComponent The texture component of the sprite
             * @param shaderComponent The shader component of the sprite
             */
            Sprite(TextureComponent &textureComponent, ShaderComponent &shaderComponent) {
                entity = _coordinator->createEntity();
                if (!didSpriteSpawned) {
                    _coordinator->addComponent(entity, Mesh::createMesh());
                    didSpriteSpawned = true;
                }
                _coordinator->addComponent(entity, textureComponent);
                _coordinator->addComponent(entity, RectI{0, 0, textureComponent.width, textureComponent.height});
                _coordinator->addComponent(entity, shaderComponent);
                auto transform = Transform::createTransform();
                transform.transform = glm::scale(transform.transform, glm::vec3(textureComponent.width, textureComponent.height, 1.0f));
                _coordinator->addComponent(entity, transform);
            }
            ~Sprite() = default;

            /**
             * @brief Draw the sprite given in parameter
             * @param entity The entity to draw
             */
            static void draw(const Window &window, const Entity &entity) {
                auto &coord = *_coordinator;
                auto &mesh = coord.getComponent<MeshComponent>(entity);
                auto &rect = coord.getComponent<RectI>(entity);
                auto &shader = coord.getComponent<ShaderComponent>(entity);
                auto &texture = coord.getComponent<TextureComponent>(entity);
                auto &transform = coord.getComponent<TransformComponent>(entity);

                glUseProgram(shader.shaderId);
                int rectLoc = glGetUniformLocation(shader.shaderId, "rect");
                int projectionLoc = glGetUniformLocation(shader.shaderId, "projection");
                int modelLoc = glGetUniformLocation(shader.shaderId, "model");

                glUniform4i(rectLoc, rect.x, rect.y, rect.width, rect.height);
                glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(window._getProjection()));
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform.transform));

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture.textureId);

                glBindVertexArray(mesh.VAO);
                glDrawArrays(GL_TRIANGLES, 0, 6);
                glBindVertexArray(0);
            }

            /**
             * @brief Handles the cast to Entity
             */
            operator Entity() const {
                return entity;
            }
        private:
            Entity entity;
    };
}
