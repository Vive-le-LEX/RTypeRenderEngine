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

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "Rect.hpp"

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
            TextureComponent texturec;

            glGenTextures(1, &texturec.textureId);
            glBindTexture(GL_TEXTURE_2D, texturec.textureId);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            texturec.pixels = stbi_load(path.c_str(), &texturec.width, &texturec.height, &texturec.nbByteChannels, 0);
            if (!texturec.pixels) {
                std::cerr << "Failed to load texture: " << path << std::endl;
                exit(1);
            }
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texturec.width, texturec.height, 0, GL_RGB, GL_UNSIGNED_BYTE, texturec.pixels);
            glGenerateMipmap(GL_TEXTURE_2D);
            return texturec;
        }

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
