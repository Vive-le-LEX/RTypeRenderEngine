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
    /**
     * @brief The ECS Transform data
     */
    struct TransformComponent {
        glm::mat4 transform; /**< The transform matrix */
    };

    /**
     * @brief Helper class to create, update and delete transforms
     */
    class Transform {
    public:
        Transform() = delete;
        ~Transform() = delete;

        /**
         * @brief Create a transform
         * @return A 4x4 matrix identity for transform
         */
        static TransformComponent createTransform() noexcept {
            return TransformComponent{glm::mat4(1.0f)};
        }

        /**
         * @brief Apply all parent transforms to the transform given in parameter
         * @param transform The transform to update
         * @param parentTransform The parent transform
         */
        static void update(TransformComponent &transform,
                           const glm::mat4 &parentTransform) noexcept {
            transform.transform = parentTransform * transform.transform;
        }

        /**
         * @brief Delete a transform
         * @param transform The transform to delete
         * @note This function does nothing
         */
        static void deleteTransform(TransformComponent &transform) noexcept {
            (void) transform;
        }
    };
}
