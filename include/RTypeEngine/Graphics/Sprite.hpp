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
#include "Rect.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"

namespace RTypeEngine {
    /**
     * \brief Sprite static class
     * \details This class is used to manage sprites
     */
    class Sprite {
    public:
        Sprite() = delete;

        ~Sprite() = delete;

        static Entity create(Coordinator *coordinator) noexcept;

        static void draw(Entity &entity, Coordinator *coordinator) noexcept;

        static void
        setTexture(Entity &entity, const std::string &path,
                   Coordinator *coordinator) noexcept;

        static void setTextureRect(Entity &entity, const RectI &rect,
                                   Coordinator *coordinator) noexcept;

        static Entity copy(Coordinator *coordinator, Entity &src) noexcept;
    };
}
