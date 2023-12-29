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
        T x = 0; /**< The left position of the rect */
        T y = 0; /**< The bottom position of the rect */
        T width = 0; /**< The width of the rect */
        T height = 0; /**< The height of the rect */
    };

    /**
     * \brief Rect static class
     * \details Rect is a static class that contains functions to manipulate RectComponent.
     * \details Rect is used to manipulate RectComponent.
     */
    template<typename T>
    class Rect {
    public:
        /**
         * \brief Resets the values of a RectComponent to 0
         * \param rect The rect to reset
         */
        static void resetRect(RectComponent<T> &rect) noexcept {
            rect.x = rect.y = rect.width = rect.height = 0;
        }

        /**
         * \brief Checks if two RectComponent are colliding
         * \param rect1 The first rect
         * \param rect2 The second rect
         * \return true if the point is inside the rect, false otherwise
         */
        static bool isColliding(const RectComponent<T> &rect1,
                                const RectComponent<T> &rect2) noexcept {
            return rect1.x < rect2.x + rect2.width &&
                   rect1.x + rect1.width > rect2.x &&
                   rect1.y < rect2.y + rect2.height &&
                   rect1.y + rect1.height > rect2.y;
        }
    };

    typedef RectComponent<float> RectF;
    typedef RectComponent<int> RectI;
    typedef RectComponent<unsigned int> RectU;
    typedef RectComponent<double> RectD;
}
