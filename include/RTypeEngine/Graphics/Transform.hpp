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

#include <glm/glm.hpp>

namespace RTypeEngine {
    struct TransformComponent {
        glm::mat4 transform;
    };

    /**
     * @brief Transform class
     */
    class Transform {
    public:
        static void update(TransformComponent &transform, const glm::mat4 &parentTransform) noexcept;

    };
}
