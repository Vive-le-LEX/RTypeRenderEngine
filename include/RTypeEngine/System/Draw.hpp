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

#include "RTypeECS/Systems/System.hpp"
#include "RTypeEngine/System.hpp"

namespace RTypeEngine {
    class DrawSystem : public System {
    public:
        virtual void update(Coordinator *coord) final {
            for (auto entity: entities) {
                RTypeEngine::Sprite::draw(entity, coord);
            }
        }
    };
}
