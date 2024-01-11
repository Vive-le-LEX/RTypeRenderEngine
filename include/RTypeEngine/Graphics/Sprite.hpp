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
#include "RTypeEngine/Window.hpp"
#include "RTypeECS/Coordinator.hpp"
#include "RTypeEngine/System/Core.hpp"

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
         * @param parent The parent entity to copy the texture and shader from
         */
        Sprite(TextureComponent &textureComponent,
               ShaderComponent &shaderComponent, Entity parent = -1) {
            entity = _coordinator->createEntity();
            if (entity) {
                _coordinator->copyComponent<MeshComponent>(0, entity);
            } else {
                _coordinator->addComponent(entity, Mesh::createMesh());
            }
            if (parent != -1) {
                _coordinator->copyComponent<TextureComponent>(parent, entity);
                _coordinator->copyComponent<ShaderComponent>(parent, entity);
            } else {
                _coordinator->addComponent(entity, textureComponent);
                _coordinator->addComponent(entity, shaderComponent);
            }
            RectI rect = {0, 0, textureComponent.width,
                          textureComponent.height};
            _coordinator->addComponent(entity, rect);
            auto transform = Transform::createTransform();
            _coordinator->addComponent(entity, transform);
        }

        ~Sprite() = default;

        /**
         * @brief Check if the point is in the sprite
         * @param entity The entity to check
         * @param point The point to check
         */
        static bool
        isPointInRect(RTypeEngine::Sprite &entity, const glm::vec2 &point) {
            auto &transform = _coordinator->getComponent<TransformComponent>(
                    entity);
            auto &rect = _coordinator->getComponent<RectI>(entity);

            auto pos = RTypeEngine::Transform::getPosition(transform);
            auto scale = RTypeEngine::Transform::getScale(transform);

            auto maxPos = pos +
                          glm::vec3(rect.width * scale.x, rect.height * scale.y,
                                    0.0f);
            return (point.x >= pos.x && point.x <= maxPos.x &&
                    point.y >= pos.y && point.y <= maxPos.y);
        }

        /**
         * @brief Draw the sprite given in parameter
         * @param window The window to draw on
         * @param entity The entity to draw
         */
        static void draw(const Window &window, const Entity &entity) {
            prepareDraw(window, entity);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        /**
         * @brief Draw the multiple times the sprite given in parameter
         */
        static void
        draw(const Window &window, const Entity &entity, const int &count) {
            prepareDraw(window, entity);
            glDrawArraysInstanced(GL_TRIANGLES, 0, 6, count);
        }

        /**
         * @brief Get the position of Sprite on the screen
         * @param entity Sprite to get the position
         * @return Position of the Sprite
         */
        static glm::vec3 getPosition(const Entity &entity) {
            auto &transform = _coordinator->getComponent<TransformComponent>(entity);
            return Transform::getPosition(transform);
        }

        /**
         * @brief Set the position of Sprite on the screen
         * @param entity Sprite to set the position
         * @param pos Position to set
         */
        static void setPosition(const Entity &entity, glm::vec3 &pos) {
            auto &transform = _coordinator->getComponent<TransformComponent>(entity);
            Transform::setPosition(transform, pos);
        }

        /**
         * @brief Get the position of Sprite on the screen
         * @param entity 
         * @return Position of the Sprite
         */
        static glm::vec3 getScale(const Entity &entity) {
            auto &transform = _coordinator->getComponent<TransformComponent>(
                    entity);
            return Transform::getScale(transform);
        }

        /**
         * @brief Get the position of Sprite on the screen
         * @param entity 
         * @return Position of the Sprite
         */
        static void setScale(const Entity &entity, glm::vec3 &scale) {
            auto &transform = _coordinator->getComponent<TransformComponent>(
                    entity);
            Transform::setScale(transform, scale);
        }

        /**
         * @brief Handles the cast to Entity
         */
        operator Entity() const {
            return entity;
        }

    private:
        Entity entity;

        static void prepareDraw(const Window &window, const Entity &entity) {
            auto &coord = *_coordinator;
            auto &mesh = coord.getComponent<MeshComponent>(entity);
            auto &rect = coord.getComponent<RectI>(entity);
            auto &shader = coord.getComponent<ShaderComponent>(entity);
            auto &texture = coord.getComponent<TextureComponent>(entity);
            auto &transform = coord.getComponent<TransformComponent>(entity);

            glUseProgram(shader.shaderId);
            int rectLoc = glGetUniformLocation(shader.shaderId, "rect");
            int projectionLoc = glGetUniformLocation(shader.shaderId,
                                                     "projection");
            int modelLoc = glGetUniformLocation(shader.shaderId, "model");

            glUniform4i(rectLoc, rect.x, rect.y, rect.width, rect.height);
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE,
                               glm::value_ptr(window.getProjection()));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE,
                               glm::value_ptr(transform.transform));

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture.textureId);

            glBindVertexArray(mesh.VAO);
            transform.isDirty = false;
        }
    };
}
