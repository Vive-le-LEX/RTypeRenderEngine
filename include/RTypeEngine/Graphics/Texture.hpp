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

#include "stb_image.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Rect.hpp"

namespace RTypeEngine {

    /**
     * \brief Texture component
     *  \param texturePath Path to the texture
     *  \param width Width of the texture
     *  \param height Height of the texture
     *  \param nbByteChannels Number of byte channels of the texture
     *  \param pixels Pixels of the texture
     *  \param textureId Id of the texture
     */
    struct TextureComponent {
        std::string texturePath;
        int width;
        int height;
        int nbByteChannels;
        stbi_uc *pixels;
        GLuint textureId;
    };

    /**
     * \brief Texture static class
     * \details This class is used to create and delete textures
     * \details It is also used to set the texture rect
     */
    class Texture {
    public:
        Texture() = delete;

        ~Texture() = delete;

        static TextureComponent createTextureFromFile(const std::string &path);

        static void deleteTexture(TextureComponent &texture);

        static void
        setTextureRect(TextureComponent &texture, const RectI &rect) noexcept;


    private:
        static GLuint _id;
    };
}
