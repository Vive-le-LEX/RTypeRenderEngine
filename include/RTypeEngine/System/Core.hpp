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

#include "RTypeECS/Coordinator.hpp"
#include "RTypeEngine/Graphics/Mesh.hpp"
#include <memory>

namespace RTypeEngine {
    inline std::unique_ptr<Coordinator> _coordinator = std::make_unique<Coordinator>();
}
