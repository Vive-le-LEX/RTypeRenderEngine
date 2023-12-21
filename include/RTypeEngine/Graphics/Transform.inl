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

#include "Transform.hpp"

using namespace RTypeEngine;

/**
 * @brief Update transform
 * @param transform Transform component
 * @param parentTransform Parent transform
 */
void Transform::update(TransformComponent &transform, const glm::mat4 &parentTransform) noexcept {
    transform.transform = parentTransform * transform.transform;
}
