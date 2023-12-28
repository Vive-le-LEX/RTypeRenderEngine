/*
** EPITECH PROJECT, 2023
** RTypeRenderEngine
** File description:
** StateHandler
*/

#ifndef STATEHANDLER_HPP_
    #define STATEHANDLER_HPP_

#include "RTypeEngine/System.hpp"
#include "RTypeEngine/Graphics.hpp"

namespace RTypeEngine {

    /**
     * @brief Holds all the default ECS systems for RTypeEngine
     */
    struct Systems {
        std::shared_ptr<DrawSystem> drawSystem; /**< Draws all registered sprites */
    };

    /**
     * @brief Initializes the ECS
     * @return A Systems struct with all the default ECS systems
     */
    static Systems initECS(void) {
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

        return {drawSystem};
    }
}

#endif /* !STATEHANDLER_HPP_ */
