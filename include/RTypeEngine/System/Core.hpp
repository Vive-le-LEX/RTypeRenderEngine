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
#include "RTypeECS/Coordinator.hpp"
#include "Draw.hpp"
#include <memory>

namespace RTypeEngine {
    inline std::shared_ptr<Coordinator> _coordinator = std::make_shared<Coordinator>();

    static void initECS(void) {
        _coordinator->registerComponent<RTypeEngine::MeshComponent>(
                RTypeEngine::Mesh::deleteMesh);
        _coordinator->registerComponent<RTypeEngine::RectI>(
                RTypeEngine::Rect<int>::deleteRect);
        _coordinator->registerComponent<RTypeEngine::ShaderComponent>(
                RTypeEngine::Shader::deleteShader);
        _coordinator->registerComponent<RTypeEngine::TextureComponent>(
                RTypeEngine::Texture::deleteTexture);
        _coordinator->registerComponent<RTypeEngine::TransformComponent>(
                RTypeEngine::Transform::deleteTransform);

        Signature signature;
        signature.set(
                _coordinator->getComponentType<RTypeEngine::MeshComponent>());
        signature.set(_coordinator->getComponentType<RTypeEngine::RectI>());
        signature.set(
                _coordinator->getComponentType<RTypeEngine::ShaderComponent>());
        signature.set(
                _coordinator->getComponentType<RTypeEngine::TextureComponent>());
        signature.set(
                _coordinator->getComponentType<RTypeEngine::TransformComponent>());

        auto drawSystem = _coordinator->registerSystem<DrawSystem>();
        _coordinator->setSystemSignature<DrawSystem>(signature);
    }
}
