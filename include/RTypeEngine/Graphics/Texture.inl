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

#include "Texture.hpp"

using namespace RTypeEngine;

/**
 * @brief Create a texture from a file
 * @param path Path to the file
 * @return TextureComponent
 */
TextureComponent
Texture::createTextureFromFile(const std::string &path) {
    TextureComponent texture;
    auto data = stbi_load(path.c_str(), &texture.width, &texture.height,
                          &texture.nbByteChannels, 0);
    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height,
                     0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    texture.textureId = _id;
    ++_id;
    return texture;
}

/**
 * @brief Delete a texture
 * @param texture Texture to delete
 */
void Texture::deleteTexture(TextureComponent &texture) {
    glDeleteTextures(1, &texture.textureId);
    stbi_image_free(texture.pixels);
}

/**
 * @brief Set the texture rect
 * @param texture Texture to set
 * @param rect Rect to set
 */
void Texture::setTextureRect(TextureComponent &texture, const RectI &rect) noexcept {
    glBindTexture(GL_TEXTURE_2D, texture.textureId);
    glTexSubImage2D(GL_TEXTURE_2D, 0, rect.x, rect.y, rect.width, rect.height, GL_RGBA,
                    GL_UNSIGNED_BYTE, texture.pixels);
}

GLuint Texture::_id = 0;
