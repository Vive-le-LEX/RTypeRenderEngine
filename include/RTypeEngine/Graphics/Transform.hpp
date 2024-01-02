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
        bool isDirty = true; /**< Is the transform dirty ? */
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

        static glm::vec3 getPosition(const TransformComponent &transform) noexcept {
            return glm::vec3(transform.transform[3]);
        }

        static void setPosition(TransformComponent &transform, const glm::vec3 &position) noexcept {
            transform.isDirty = true;
            transform.transform[3] = glm::vec4(position, 1.0f);
        }

        static glm::vec3 getScale(const TransformComponent &transform) noexcept {
            return glm::vec3(glm::length(glm::vec3(transform.transform[0][0], transform.transform[1][0], transform.transform[2][0])),
                             glm::length(glm::vec3(transform.transform[0][1], transform.transform[1][1], transform.transform[2][1])),
                             glm::length(glm::vec3(transform.transform[0][2], transform.transform[1][2], transform.transform[2][2])));
        }
    };
}
