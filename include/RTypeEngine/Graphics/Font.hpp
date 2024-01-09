/*
** EPITECH PROJECT, 2024
** RTypeRenderEngine
** File description:
** Font
*/

#ifndef FONT_HPP_
    #define FONT_HPP_

#include <iostream>
#include <unordered_map>
#include <glm/glm.hpp>
#include <ft2build.h>
#include <GLFW/glfw3.h>
#include FT_FREETYPE_H

#include "Shader.hpp"
#include "Mesh.hpp"

namespace RTypeEngine
{
    /**
     * @brief Glyph struct
     * @details This struct is used to store all informations about a glyph
     */
    struct Glyph {
        unsigned int textureID; ///< OpenGL texture ID
        glm::ivec2   size;      ///< Pixel size of glyph
        glm::ivec2   bearing;   ///< Offset from baseline to left/top of glyph (https://fontforge.org/docs/tutorial/editexample5.html)
        unsigned int advance;   ///< Pixel offset to advance to next glyph
    };
    
    struct FontComponent {
        std::string path;
        FT_Face face;
        int size;
    };

    /**
     * @brief Font class
     * @details This class is used to load a font and get glyphs from it
     */
    class Font {
        public:
            ~Font() = default;

            /**
             * @brief Create a font object
             * @details This function is used to create a font object from a filepath
             * @param path The path to the font file
             * @return The font object
             */
            static Font createFont(const std::string &path) {
                if (!_ft) {
                    prepareDraw();
                    FT_Error error = FT_Init_FreeType(&_ft);
                    if (error) {
                        std::cerr << "Error: FT_Init_FreeType failed (" << error << ")" << std::endl;
                    }
                }

                FT_Face newFace = nullptr;
                FT_Error error = FT_New_Face(_ft, path.c_str(), 0, &newFace);
                if (error) {
                    std::cerr << "Error: FT_New_Face failed (" << error << ")" << std::endl;
                }
                return Font(newFace);
            }

            /**
             * @brief Get the corresponding glyph
             * @details This function is used to get a glyph from a character and a size
             * @param c The character
             * @param size The size of the glyph
             * @return The glyph object
             */
            const Glyph getGlyph(const char &c, const int &size) {
                if (_glyphs.find(size) == _glyphs.end()) {
                    _glyphs[size] = std::unordered_map<char, Glyph>();
                } else if (_glyphs[size].find(c) != _glyphs[size].end()) {
                    return _glyphs[size][c];
                }
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                FT_Error error = FT_Set_Pixel_Sizes(_face, 0, size);
                if (error) {
                    std::cerr << "Error: FT_Set_Pixel_Sizes failed (" << error << ")" << std::endl;
                }
                error = FT_Load_Char(_face, c, FT_LOAD_RENDER);
                if (error) {
                    std::cerr << "Error: FT_Load_Char failed (" << error << ")" << std::endl;
                }

                unsigned int textureID;
                glGenTextures(1, &textureID);
                glBindTexture(GL_TEXTURE_2D, textureID);
                glTexImage2D(
                    GL_TEXTURE_2D,
                    0,
                    GL_RED,
                    _face->glyph->bitmap.width,
                    _face->glyph->bitmap.rows,
                    0,
                    GL_RED,
                    GL_UNSIGNED_BYTE,
                    _face->glyph->bitmap.buffer
                );
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                Glyph glyph = {
                    textureID,
                    glm::ivec2(_face->glyph->bitmap.width, _face->glyph->bitmap.rows),
                    glm::ivec2(_face->glyph->bitmap_left, _face->glyph->bitmap_top),
                    static_cast<unsigned int>(_face->glyph->advance.x)
                };
                _glyphs[size][c] = glyph;
                glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
                return glyph;
            }
            friend class Text;
        private:
            static FT_Library _ft;
            static ShaderComponent _shader;
            static MeshComponent _mesh;

            static void prepareDraw() {
                _shader = Shader::createShaderFromMemory(vertexTextShader, fragmentTextShader);
                _mesh = Mesh::createMesh(GL_DYNAMIC_DRAW);
            }

            Font(const FT_Face &face) {
                _face = face;
            }

            FT_Face _face;
            std::unordered_map<int, std::unordered_map<char, Glyph>> _glyphs;

            static char vertexTextShader[];
            static char fragmentTextShader[];
    };
        inline FT_Library Font::_ft = nullptr;
        inline MeshComponent Font::_mesh = MeshComponent();
        inline ShaderComponent Font::_shader = ShaderComponent();
        inline char Font::vertexTextShader[] = R"(
            #version 330 core
            layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
            out vec2 TexCoords;
            uniform mat4 projection;
            void main()
            {
                gl_Position = projection * vec4(vertex.xy, 1.0, 1.0);
                TexCoords = vertex.zw;
                TexCoords.y = 1.0 - TexCoords.y;
            }
        )";

        inline char Font::fragmentTextShader[] = R"(
            #version 330 core
            in vec2 TexCoords;
            out vec4 color;
            uniform sampler2D text;
            uniform vec4 textColor;
            void main()
            {
                vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
                color = textColor * sampled;
            }
        )";
} // namespace RTypeEngine


#endif /* !FONT_HPP_ */
