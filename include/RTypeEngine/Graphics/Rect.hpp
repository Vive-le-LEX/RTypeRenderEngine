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

#include "Transform.hpp"

namespace RTypeEngine {

    /**
     * \brief RectComponent
     * \tparam T
     * \details RectComponent is a simple struct that contains 4 values:
     * - x: the x position of the rect
     * - y: the y position of the rect
     * - width: the width of the rect
     * - height: the height of the rect
     * \details RectComponent is used to represent a rectangle in the 2D space.
     */
    template<typename T>
    struct RectComponent {
        T x = 0;
        T y = 0;
        T width = 0;
        T height = 0;
    };

    /**
     * \brief Rect static class
     * \details Rect is a static class that contains functions to manipulate RectComponent.
     * \details Rect is used to manipulate RectComponent.
     */
    template<typename T>
    class Rect {
    public:
        static void deleteRect(RectComponent<T> &rect) noexcept {
            rect.x = rect.y = rect.width = rect.height = 0;
        }

        static bool isColliding(const RectComponent<T> &rect1,
                                const RectComponent<T> &rect2) noexcept {
            return rect1.x < rect2.x + rect2.width &&
                   rect1.x + rect1.width > rect2.x &&
                   rect1.y < rect2.y + rect2.height &&
                   rect1.y + rect1.height > rect2.y;
        }

        static bool isColliding(const RectComponent<T> &rect1,
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

        static bool isColliding(const RectComponent<T> &rect1,
                                const TransformComponent &transform1,
                                const RectComponent<T> &rect2) noexcept {
            RectComponent<T> rect1Transformed = rect1;
            rect1Transformed.x += transform1.transform[3][0];
            rect1Transformed.y += transform1.transform[3][1];
            return isColliding(rect1Transformed, rect2);
        }


    };

    typedef RectComponent<float> RectF;
    typedef RectComponent<int> RectI;
    typedef RectComponent<unsigned int> RectU;
    typedef RectComponent<double> RectD;
}
