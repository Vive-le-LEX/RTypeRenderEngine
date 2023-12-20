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

#include "Rect.hpp"

using namespace RTypeEngine;

/**
 * @brief Check if two rectangles are colliding
 * @param rect1 First rectangle
 * @param rect2 Second rectangle
 * @return true if colliding, false otherwise
 */
template<typename T>
bool Rect::isColliding(const RectComponent<T> &rect1,
                             const RectComponent<T> &rect2) noexcept {
    return rect1.x < rect2.x + rect2.width &&
           rect1.x + rect1.width > rect2.x &&
           rect1.y < rect2.y + rect2.height &&
           rect1.y + rect1.height > rect2.y;
}

/**
 * @brief Check if two rectangles are colliding
 * @param rect1 First rectangle
 * @param transform1 First rectangle transform
 * @param rect2 Second rectangle
 * @param transform2 Second rectangle transform
 * @return true if colliding, false otherwise
 */
template<typename T>
bool Rect::isColliding(const RectComponent<T> &rect1,
                             const TransformComponent &transform1,
                             const RectComponent<T> &rect2,
                             const TransformComponent &transform2) noexcept {
    RectComponent<T> rect1Transformed = rect1;
    rect1Transformed.x += transform1.transform[3][0];
    rect1Transformed.y += transform1.transform[3][1];
    RectComponent<T> rect2Transformed = rect2;
    rect2Transformed.x += transform2.transform[3][0];
    rect2Transformed.y += transform2.transform[3][1];
    return isColliding(rect1Transformed, rect2Transformed);
}

/**
 * @brief Check if two rectangles are colliding
 * @param rect1 First rectangle
 * @param transform1 First rectangle transform
 * @param rect2 Second rectangle
 * @return true if colliding, false otherwise
 */
template<typename T>
bool Rect::isColliding(const RectComponent<T> &rect1,
                             const TransformComponent &transform1,
                             const RectComponent<T> &rect2) noexcept {
    RectComponent<T> rect1Transformed = rect1;
    rect1Transformed.x += transform1.transform[3][0];
    rect1Transformed.y += transform1.transform[3][1];
    return isColliding(rect1Transformed, rect2);
}
