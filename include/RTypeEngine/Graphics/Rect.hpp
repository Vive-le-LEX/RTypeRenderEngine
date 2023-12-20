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
    class Rect {
    public:
        template<typename T>
        static bool isColliding(const RectComponent<T> &rect1,
                                      const RectComponent<T> &rect2) noexcept;

        template<typename T>
        static bool isColliding(const RectComponent<T> &rect1,
                                      const TransformComponent &transform1,
                                      const RectComponent<T> &rect2,
                                      const TransformComponent &transform2) noexcept;

        template<typename T>
        static bool isColliding(const RectComponent<T> &rect1,
                                      const TransformComponent &transform1,
                                      const RectComponent<T> &rect2) noexcept;
    };

    typedef RectComponent<float> RectF;
    typedef RectComponent<int> RectI;
    typedef RectComponent<unsigned int> RectU;
    typedef RectComponent<double> RectD;
}
