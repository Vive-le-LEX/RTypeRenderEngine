/*
** EPITECH PROJECT, 2024
** RTypeRenderEngine
** File description:
** Text
*/

#ifndef TEXT_HPP_
    #define TEXT_HPP_

    #include "Font.hpp"
    #include <string>
    #include <vector>

namespace RTypeEngine
{
    /**
     * @brief Represents a set of Glyphs
     * @details This class is used to display a text on the screen
     */
    class Text {
        public:
            /**
             * @brief Construct a new Text object
             * @details This constructor initialize the text with the given parameters
             * @param text The text to display
             * @param font The font to use
             * @param position The position of the text
             * @param color The color of the text
             * @param size The size of the text
             */
            explicit Text(const std::string &text, const Font &font, const glm::vec2 position, const glm::vec4 color, const int &size) : _font(font), _size(size), _position(position), _color(color) {
                _text = text;
                _width = 0;
                _height = size;
                for (const char &c : text) {
                    Glyph glyph = _font.getGlyph(c, _size);
                    _width += (glyph.advance >> 6);
                    _glyphs.push_back(glyph);
                }
            }

            ~Text() = default;

            /**
             * @brief Set the text to display
             * @details This function will set the text to display and update the width and height of the text
             * @param text The text to display
             */
            void setText(const std::string &text) {
                _text = text;
                _glyphs.clear();
                _width = 0;
                _height = _size;
                for (const char &c : text) {
                    Glyph glyph = _font.getGlyph(c, _size);
                    _width += (glyph.advance >> 6);
                    _glyphs.push_back(glyph);
                }
            }

            /**
             * @brief Get the current text
             * @return The current text
             */
            const std::string &getText() {
                return _text;
            }

            /**
             * @brief Set the position of the text
             * @param position The position of the text
             */
            void setPosition(const glm::vec2 &position) {
                _position = position;
            }

            /**
             * @brief Set the color of the text
             * @param color The color of the text
             */
            void setColor(const glm::vec4 &color) {
                _color = color;
            }

            /**
             * @brief Set the size of the text
             * @param scale The size of the text
             */
            void setScale(const glm::vec2 &scale) {
                _scale = scale;
            }

            /**
             * @brief Get the position of the text
             * @return The position of the text
             */
            glm::vec2 &getPosition() {
                return _position;
            }

            /**
             * @brief Get the color of the text
             * @return The color of the text
             */
            glm::vec4 &getColor() {
                return _color;
            }

            /**
             * @brief Get the size of the text
             * @return The size of the text
             */
            glm::vec2 &getScale() {
                return _scale;
            }

            /**
             * @brief Draw the text
             * @details This function will draw the text on the screen
             * @param projection The pointer to the first element of the projection matrix
             */
            void draw(const glm::f32 *projection) {
                glUseProgram(Font::_shader.shaderId);
                int projectionLoc = glGetUniformLocation(Font::_shader.shaderId, "projection");
                int textColorLoc = glGetUniformLocation(Font::_shader.shaderId, "textColor");
                glUniform4f(textColorLoc, _color.x, _color.y, _color.z, _color.w);
                glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection);
                glActiveTexture(GL_TEXTURE0);
                glBindVertexArray(Font::_mesh.VAO);

                std::string::const_iterator c;
                float x = _position.x;
                for (c = _text.begin(); c != _text.end(); c++) {
                    Glyph ch = _font.getGlyph(*c, _size);

                    float xpos = x + ch.bearing.x * _scale.x;
                    float ypos = _position.y + (_size - ch.size.y) + (ch.size.y - ch.bearing.y);

                    float w = ch.size.x * _scale.x;
                    float h = ch.size.y * _scale.y;
                    float vertices[6][4] = {
                        { xpos,     ypos + h,   0.0f, 0.0f },
                        { xpos,     ypos,       0.0f, 1.0f },
                        { xpos + w, ypos,       1.0f, 1.0f },

                        { xpos,     ypos + h,   0.0f, 0.0f },
                        { xpos + w, ypos,       1.0f, 1.0f },
                        { xpos + w, ypos + h,   1.0f, 0.0f }
                    };
                    glBindTexture(GL_TEXTURE_2D, ch.textureID);
                    glBindBuffer(GL_ARRAY_BUFFER, Font::_mesh.VBO);
                    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
                    glBindBuffer(GL_ARRAY_BUFFER, 0);
                    glDrawArrays(GL_TRIANGLES, 0, 6);
                    x += (ch.advance >> 6) * _scale.x;
                }
            }

            /**
             * @brief Get the width of the text
             * @return The width of the text
             */
            int getWidth() {
                return _width;
            }

            /**
             * @brief Get the height of the text
             * @return The height of the text
             */
            int getHeight() {
                return _size;
            }
        private:
            std::string _text;
            std::vector<Glyph> _glyphs;
            Font _font;
            int _size;
            int _width;
            int _height;
            glm::vec2 _position;
            glm::vec4 _color;
            glm::vec2 _scale = glm::vec2(1.0f, 1.0f);
    };
} // namespace RTypeEngine


#endif /* !TEXT_HPP_ */
