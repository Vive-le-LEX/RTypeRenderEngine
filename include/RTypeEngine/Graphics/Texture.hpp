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

#ifndef TEXTURE_HPP_
    #define TEXTURE_HPP_

    #include <glm/gtc/type_ptr.hpp>
    #include <glm/gtc/matrix_transform.hpp>
    #include <iostream>
    #include <glm/glm.hpp>
    #include <GLFW/glfw3.h>
    #include "Rect.hpp"
    #include "RTypeEngine/Graphics/stb_image.h"
    #include "RTypeEngine/System.hpp"

namespace RTypeEngine {

    /**
     * @brief The ECS Textures data
     */
    struct TextureComponent {
        std::string texturePath; /**< The path given to create the texture */
        int width; /**< The width of the texture */
        int height; /**< The height of the texture */
        int nbByteChannels; /**< The number of byte channels of the texture (32 for RGBA)*/
        stbi_uc *pixels; /**< The raw pointer to the pixels of the texture */
        GLuint textureId; /**< The OpenGL texture id */
        bool isFromMemory; /**< True if the texture is from memory, false if it is from a file */
    };

    /**
     * @brief Texture static class
     * @details This class is used to create and delete textures
     * @code{.cpp}
     * auto texture = Texture::createTextureFromFile("path/to/texture.png");
     * Texture::deleteTexture(texture);
     * @endcode
     */
    class Texture {
    public:
        Texture() = delete;

        ~Texture() = delete;

        /**
         * @brief Create a texture from a file
         * @param path Path to the texture
         * @return TextureComponent
         */
        static TextureComponent createTextureFromFile(const std::string &path) {
            int width, height, nbByteChannels;
            stbi_uc *pixels = stbi_load(path.c_str(), &width, &height, &nbByteChannels, 0);
            if (!pixels) {
                std::cerr << "Failed to load texture: " << path << std::endl;
                exit(1);
            }
            auto texturec = createTextureFromMemory(pixels, width, height, nbByteChannels);
            texturec.isFromMemory = false;
            return std::move(texturec);
        }

        static TextureComponent createTextureFromAssets(const std::string &path, const int &nbChannels) {
            auto pixels = getEmbeddedAsset<unsigned char>(path);
            auto size = getEmbeddedAssetSize(path);
            if (!pixels) {
                std::cerr << "Failed to load texture: " << path << std::endl;
                exit(1);
            }
            int width, height, nbByteChannels;
            auto *pixelsData = stbi_load_from_memory(pixels, size, &width, &height, &nbByteChannels, nbChannels);
            if (!pixelsData) {
                std::cerr << "Failed to load texture: " << path << std::endl;
                exit(1);
            }
            auto texturec = createTextureFromMemory(pixelsData, width, height, nbByteChannels);
            texturec.isFromMemory = false;
            return std::move(texturec);
        }

        /**
         * @brief Create a texture from a memory buffer
         * @param pixels The pixels of the texture
         * @param width The width of the texture
         * @param height The height of the texture
         * @param nbByteChannels The number of byte channels of the texture (32 for RGBA)
         * @return TextureComponent
         */
        static TextureComponent createTextureFromMemory(const unsigned char *pixels, int width, int height, int nbByteChannels) {
            TextureComponent texturec;
            texturec.width = width;
            texturec.height = height;
            texturec.nbByteChannels = nbByteChannels;
            texturec.pixels = (stbi_uc *) pixels;
            texturec.isFromMemory = true;
            glGenTextures(1, &texturec.textureId);
            glBindTexture(GL_TEXTURE_2D, texturec.textureId);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            if (texturec.nbByteChannels == 3)
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texturec.width, texturec.height, 0, GL_RGB, GL_UNSIGNED_BYTE, texturec.pixels);
            else if (texturec.nbByteChannels == 4)
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texturec.width, texturec.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texturec.pixels);
            else
                std::cerr << "No support for " << texturec.nbByteChannels << std::endl;
            glGenerateMipmap(GL_TEXTURE_2D);
            return texturec;
        };

        /**
         * @brief Delete a texture
         * @param texture The texture to delete
         */
        static void deleteTexture(TextureComponent &texture) {
            stbi_image_free(texture.pixels);
            glDeleteTextures(1, &texture.textureId);
        }
    };
}

#endif /* !TEXTURE_HPP_ */
