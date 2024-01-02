/*
** EPITECH PROJECT, 2024
** RTypeRenderEngine
** File description:
** Text
*/

#ifndef TEXT_HPP_
    #define TEXT_HPP_

    #include "RTypeEngine/Window.hpp"
    #include "Font.hpp"
    #include <string>
    #include <vector>

namespace RTypeEngine
{
    class Text {
        public:
            Text(const std::string &text, const Font &font, const glm::vec2 position, const glm::vec4 color, const int &size) : _font(font), _size(size), _position(position), _color(color) {
                _text = text;
                for (const char &c : text) {
                    Glyph glyph = _font.getGlyph(c, _size);
                    _width += (glyph.advance >> 6);
                    _glyphs.push_back(glyph);
                }
            }
            ~Text() = default;

            void setPosition(const glm::vec2 &position) {
                _position = position;
            }

            void setColor(const glm::vec4 &color) {
                _color = color;
            }

            void setScale(const glm::vec2 &scale) {
                _scale = scale;
            }

            glm::vec2 &getPosition() {
                return _position;
            }

            glm::vec4 &getColor() {
                return _color;
            }

            glm::vec2 &getScale() {
                return _scale;
            }

            void draw(const RTypeEngine::Window &window) {
                glUseProgram(Font::_shader.shaderId);
                int projectionLoc = glGetUniformLocation(Font::_shader.shaderId, "projection");
                int textColorLoc = glGetUniformLocation(Font::_shader.shaderId, "textColor");
                glUniform4f(textColorLoc, _color.x, _color.y, _color.z, _color.w);
                glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(window._getProjection()));
                glActiveTexture(GL_TEXTURE0);
                glBindVertexArray(Font::_mesh.VAO);

                std::string::const_iterator c;
                float x = _position.x;
                for (c = _text.begin(); c != _text.end(); c++) {
                    Glyph ch = _font.getGlyph(*c, _size);

                    float xpos = x + ch.bearing.x * _scale.x;
                    float ypos = _position.y - (ch.size.y - ch.bearing.y) * _scale.y;

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

            int getWidth() {
                return _width;
            }

            int getHeight() {
                return _size;
            }
        private:
            std::string _text;
            std::vector<Glyph> _glyphs;
            Font _font;
            int _size;
            int _width;
            glm::vec2 _position;
            glm::vec4 _color;
            glm::vec2 _scale = glm::vec2(1.0f, 1.0f);
    };
} // namespace RTypeEngine


#endif /* !TEXT_HPP_ */
