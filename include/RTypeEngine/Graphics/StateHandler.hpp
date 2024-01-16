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
        std::shared_ptr<PhysicsSystem> physicsSystem; /**< Update all the registered rigidbodies*/
    };

    /**
     * @brief Initializes the ECS
     * @return A Systems struct with all the default ECS systems
     */
    static Systems initECS(void) {
        _coordinator->registerComponent<MeshComponent>(
                Mesh::deleteMesh);
        _coordinator->registerComponent<RectI>(
                Rect<int>::resetRect);
        _coordinator->registerComponent<ShaderComponent>(
                Shader::deleteShader);
        _coordinator->registerComponent<TextureComponent>(
                Texture::deleteTexture);
        _coordinator->registerComponent<TransformComponent>(
                Transform::deleteTransform);
        _coordinator->registerComponent<RigigbodyComponent>();
        _coordinator->registerComponent<ColliderComponent>();
        _coordinator->registerComponent<ConstraintComponent>();

        Signature signature;
        signature.set(
                _coordinator->getComponentType<MeshComponent>());
        signature.set(_coordinator->getComponentType<RectI>());
        signature.set(
                _coordinator->getComponentType<ShaderComponent>());
        signature.set(
                _coordinator->getComponentType<TextureComponent>());
        signature.set(
                _coordinator->getComponentType<TransformComponent>());

        auto drawSystem = _coordinator->registerSystem<DrawSystem>();
        _coordinator->setSystemSignature<DrawSystem>(signature);

        Signature physicSign;
        physicSign.set(_coordinator->getComponentType<RigigbodyComponent>());
        physicSign.set(_coordinator->getComponentType<Transform>());

        auto physicSystem = _coordinator->registerSystem<PhysicsSystem>();
        _coordinator->setSystemSignature<PhysicsSystem>(physicSign);

        return {drawSystem, physicSystem};
    }
}

#endif /* !STATEHANDLER_HPP_ */
