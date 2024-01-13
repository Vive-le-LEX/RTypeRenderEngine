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

#include <memory>
#include "RTypeECS/Coordinator.hpp"

namespace RTypeEngine {
    extern std::unique_ptr<Coordinator> _coordinator;
    #ifdef HAS_EMBEDS
        extern std::unordered_map<std::string, void*> allEmbedsResources;
        extern std::unordered_map<std::string, size_t> allEmbedsResourcesSizes;
    #endif
}
