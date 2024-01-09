/*
** EPITECH PROJECT, 2024
** RTypeRenderEngine
** File description:
** Text
*/

#pragma once

#include <string>
#include <vector>

#include "RTypeECS/Types.hpp"
#include "RTypeECS/Coordinator.hpp"
#include "RTypeEngine/System/Core.hpp"
#include "Font.hpp"

namespace RTypeEngine {
    /**
     * @brief Holds all the data needed to draw a text
     * @param text The text to display
     * @param glyphs The glyphs of the text
     * @param font The font to use
     * @param size The size of the text
     * @param width The width of the text
     * @param height The height of the text
     * @param color The color of the text
     */
    struct TextComponent {
        std::string text;
        std::vector<Glyph> glyphs;
        Font font;
        int size;
        int width;
        int height;
        glm::vec4 color;
    };

    /**
     * @brief Handles the creation of a text entity
     */
    class Text {
    public:

        /**
         * @brief Creates a text entity
         * @param text The text to display
         * @param font The font to use
         * @param position The position of the text
         * @param color The color of the text
         * @param size The size of the text
         * @param parent The parent entity
         */
        Text(const std::string &text, const Font &font,
             const glm::vec2 position, const glm::vec4 color,
             const int &size, Entity parent = -1) {

            entity = _coordinator->createEntity();

            if (parent != -1) {
                _coordinator->copyComponent<TextComponent>(parent, entity);
                return;
            }

            TextComponent textComponent = {
                    text,
                    std::vector<Glyph>(),
                    font,
                    size,
                    0,
                    size,
                    color,
            };
            for (const char &c: text) {
                Glyph glyph = textComponent.font.getGlyph(c, size);
                textComponent.width += (glyph.advance >> 6);
                textComponent.glyphs.push_back(glyph);
            }
            _coordinator->addComponent(entity, textComponent);
            auto transform = Transform::createTransform();
            Transform::setPosition(transform, glm::vec3(position, 0.0f));
            Transform::setScale(transform, glm::vec3(1.0f, 1.0f, 1.0f));
            _coordinator->addComponent(entity, transform);
        }

        ~Text() = default;

        /**
         * @brief Draw the text given in parameter
         * @param window The window to draw on
         * @param entity The entity to draw
         */
        static void draw(const Window &window, const Entity &entity) {
            auto &textComponent = _coordinator->getComponent<TextComponent>(
                    entity);
            auto &transform = _coordinator->getComponent<TransformComponent>(
                    entity);
            prepareDraw(window, entity);

            std::string::const_iterator c;
            float x = textComponent.position.x;
            for (c = textComponent.text.begin(); c != textComponent.text.end(); c++) {
                Glyph ch = textComponent.font.getGlyph(*c, textComponent.size);

                float xpos = x + ch.bearing.x * textComponent.scale.x;
                float ypos = textComponent.position.y + (textComponent.size - ch.size.y) +
                             (ch.size.y - ch.bearing.y);

                float w = ch.size.x * textComponent.scale.x;
                float h = ch.size.y * textComponent.scale.y;
                float vertices[6][4] = {
                        {xpos,     ypos + h, 0.0f, 0.0f},
                        {xpos,     ypos,     0.0f, 1.0f},
                        {xpos + w, ypos,     1.0f, 1.0f},

                        {xpos,     ypos + h, 0.0f, 0.0f},
                        {xpos + w, ypos,     1.0f, 1.0f},
                        {xpos + w, ypos + h, 1.0f, 0.0f}
                };
                glBindTexture(GL_TEXTURE_2D, ch.textureID);
                glBindBuffer(GL_ARRAY_BUFFER, Font::_mesh.VBO);
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glDrawArrays(GL_TRIANGLES, 0, 6);
                x += (ch.advance >> 6) * Transform::getScale(transform).x;
            }
        }

        /**
         * @brief Set the text of a text entity
         * @param entity The entity to update
         * @param text The text to set
         */
        void static setText(Entity &entity, const std::string text) {
            auto &textComponent = _coordinator->getComponent<TextComponent>(
                    entity);
            textComponent.text = text;
            textComponent.glyphs.clear();
            textComponent.width = 0;
            textComponent.height = textComponent.size;
            for (const char &c: text) {
                Glyph glyph = textComponent.font.getGlyph(c, textComponent.size);
                textComponent.width += (glyph.advance >> 6);
                textComponent.glyphs.push_back(glyph);
            }
        }

        /**
         * @brief Set the font of a text entity
         * @param entity The entity to update
         * @param font The font to set
         */
        static void setFont(Entity &entity, const Font &font) {
            auto &textComponent = _coordinator->getComponent<TextComponent>(
                    entity);
            textComponent.font = font;
            textComponent.glyphs.clear();
            textComponent.width = 0;
            textComponent.height = textComponent.size;
            for (const char &c: textComponent.text) {
                Glyph glyph = textComponent.font.getGlyph(c, textComponent.size);
                textComponent.width += (glyph.advance >> 6);
                textComponent.glyphs.push_back(glyph);
            }
        }

        /**
         * @brief Set the Size of a text entity
         * @param entity The entity to update
         * @param size The size to set
         */
        static void setSize(Entity &entity, const int &size) {
            auto &textComponent = _coordinator->getComponent<TextComponent>(
                    entity);
            textComponent.size = size;
            textComponent.glyphs.clear();
            textComponent.width = 0;
            textComponent.height = textComponent.size;
            for (const char &c: textComponent.text) {
                Glyph glyph = textComponent.font.getGlyph(c, textComponent.size);
                textComponent.width += (glyph.advance >> 6);
                textComponent.glyphs.push_back(glyph);
            }
        }

        /**
         * @brief Get the text of a text entity
         * @param entity The entity text to get
         */
        static const std::string &getText(Entity &entity) {
            auto &textComponent = _coordinator->getComponent<TextComponent>(
                    entity);
            return textComponent.text;
        }

        /**
         * @brief Set the position of a text entity
         * @param entity The entity to update
         * @param position The position to set
         */
        static void setPosition(Entity &entity, const glm::vec2 &position) {
            auto &transformComponent = _coordinator->getComponent<TransformComponent>(
                    entity);
            Transform::setPosition(transformComponent, glm::vec3(position, 0.0f));
        }

        /**
         * @brief Set the color of a text entity
         * @param entity The entity to update
         * @param color The color to set
         */
        static void setColor(Entity &entity, const glm::vec4 &color) {
            auto &textComponent = _coordinator->getComponent<TextComponent>(
                    entity);
            textComponent.color = color;
        }

        /**
         * @brief Get the position of a text entity
         * @param entity The entity to get
         */
        static glm::vec2 &getPosition(Entity &entity) {
            auto &transformComponent = _coordinator->getComponent<TransformComponent>(
                    entity);
            return Transform::getPosition(transformComponent);
        }

        /**
         * @brief Get the color of a text entity
         * @param entity The entity to get
         */
        static glm::vec4 &getColor(Entity &entity) {
            auto &textComponent = _coordinator->getComponent<TextComponent>(
                    entity);
            return textComponent.color;
        }

        /**
         * @brief Set the scale of a text entity
         * @param entity The entity to update
         * @param scale The scale to set
         */
        static void setScale(Entity &entity, const glm::vec2 &scale) {
            auto &transformComponent = _coordinator->getComponent<TransformComponent>(
                    entity);
            Transform::setScale(transformComponent);
        }

        /**
         * @brief Get the scale of a text entity
         * @param entity The entity to get
         */
        static glm::vec2 &getScale(Entity &entity) {
            auto &transformComponent = _coordinator->getComponent<TransformComponent>(
                    entity);
            return Transform::getScale(transformComponent);
        }

        /**
         * @brief Get the width of a text entity
         * @param entity The entity to get
         */
        static int getWidth(Entity &entity) {
            auto &textComponent = _coordinator->getComponent<TextComponent>(
                    entity);
            return textComponent.width;
        }

        /**
         * @brief Get the height of a text entity
         * @param entity The entity to get
         */
        static int getHeight(Entity &entity) {
            auto &textComponent = _coordinator->getComponent<TextComponent>(
                    entity);
            return textComponent.height;
        }

        /**
         * @brief Handles the cast to Entity
         */
        operator Entity() const {
            return entity;
        }

    private:
        Entity entity;

        /**
         * @brief Prepare the text to be drawn
         * @param window The window to draw on
         * @param entity The entity to draw
         */
        static void prepareDraw(const Window &window, const Entity &entity) {
            auto &coord = *_coordinator;
            auto &textComponent = _coordinator->getComponent<TextComponent>(
                    entity);
            auto &transform = coord.getComponent<TransformComponent>(entity);

            auto &shader = textComponent.font._shader;
            auto &mesh = textComponent.font._mesh;

            glUseProgram(shader.shaderId);
            int projectionLoc = glGetUniformLocation(shader.shaderId,
                                                     "projection");
            int textColorLoc = glGetUniformLocation(shader.shaderId,
                                                    "textColor");
            glUniform4f(textColorLoc, textComponent.color.x,
                        textComponent.color.y, textComponent.color.z,
                        textComponent.color.w);
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE,
                               window.getProjection());

            glActiveTexture(GL_TEXTURE0);
            glBindVertexArray(mesh.VAO);

        }
    };
} // namespace RTypeEngine
