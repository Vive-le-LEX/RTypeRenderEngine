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

#include "RTypeEngine/Graphics.hpp"
#include "RTypeECS/Systems/System.hpp"

namespace RTypeEngine {
    /**
     * @brief DrawSystem
     * @details This class is used to draw all the sprites in the ECS
     */
    class DrawSystem : public System {
    public:
        /**
         * @brief Update the system
         * @details Iterates over all the entities that have all Sprite related components and draws them
         */
        virtual void update(const Window &window) final {
            for (auto entity: entities) {
                RTypeEngine::Sprite::draw(window, entity);
            }
        }
    };
}
