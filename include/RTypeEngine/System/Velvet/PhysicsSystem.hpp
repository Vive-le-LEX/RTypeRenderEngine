/*
** EPITECH PROJECT, 2024
** RTypeRenderEngine
** File description:
** PhysicsSystem
*/

#ifndef PHYSICSSYSTEM_HPP_
#define PHYSICSSYSTEM_HPP_

#include "RTypeECS/Systems/System.hpp"
#include "RTypeEngine/Window/Window.hpp"
#include "RTypeEngine/System/Velvet/ColliderComponents.hpp"
#include "RTypeEngine/System/Velvet/ConstraintComponent.hpp"
#include "RTypeEngine/System/Velvet/RigidbodyComponent.hpp"

namespace RTypeEngine {
    class PhysicsSystem : public System {
        public:
            virtual void update(const Window &window) final {
                const int subStep = 8;

                auto &compManager = _coordinator->getComponentManager();
                auto constraintArray = compManager->getComponentArrayPtr<ConstraintComponent>();
                auto contraintSize = compManager->getTotalSize<ConstraintComponent>();
                auto constraintIndexToEntity = compManager->getIndexToEntityMap<ConstraintComponent>();

                auto colliderArray = compManager->getComponentArrayPtr<ColliderComponent>();
                auto colliderSize = compManager->getTotalSize<ColliderComponent>();
                auto colliderIndexToEntity = compManager->getIndexToEntityMap<ColliderComponent>();

                double deltaTime = window.getDeltaTime();

                const double subDeltaTime = deltaTime / subStep;
                for (int i = 0; i < subStep; i++) {
                    for (auto entity: entities) {
                        bool hasCollider = _coordinator->hasComponent<ColliderComponent>(entity);
                        auto &rigidbody = _coordinator->getComponent<RigigbodyComponent>(entity);
                        auto &transform = _coordinator->getComponent<TransformComponent>(entity);
                        glm::vec3 actualPos = Transform::getPosition(transform);
                        if (rigidbody.isDynamic) {
                            _updateGravity(rigidbody);
                            _updateConstraints(actualPos, rigidbody, constraintArray, contraintSize, constraintIndexToEntity);
                            if (hasCollider)
                                _solveCollisions(entity, actualPos, colliderArray, colliderSize, colliderIndexToEntity);
                        }
                        _updatePosition(actualPos, transform, subDeltaTime, rigidbody);
                    }
                }
            }

        protected:
            glm::vec3 gravity = glm::vec3(0.0, 1000.0, 0.0);
        private:
            void _solverCircleCollision(const Entity &cEntity, glm::vec3 &actualPos, const std::set<Entity> &colliderEntities, const ColliderComponent &oCollider, const ColliderComponent &cCollider) {
                for (auto &entity: colliderEntities) {
                    if (entity == cEntity)
                        continue;
                    auto &oTransform = _coordinator->getComponent<TransformComponent>(entity);
                    auto &oCollider = _coordinator->getComponent<ColliderComponent>(entity);
                    glm::vec3 oPos = Transform::getPosition(oTransform);

                    const glm::vec3 collisionAxis = actualPos - oPos;
                    const float distance = glm::length(collisionAxis);
                    const float minDistance = cCollider.circle.radius + oCollider.circle.radius;

                    if (distance < minDistance) {
                        const glm::vec3 normal = glm::normalize(collisionAxis);
                        const bool isDynamic = _coordinator->getComponent<RigigbodyComponent>(entity).isDynamic;
                        if (!isDynamic) {
                            const float delta = minDistance - distance;
                            actualPos += normal * delta;
                        } else {
                            const float delta = (minDistance - distance) * 0.5f;
                            actualPos += normal * delta;
                            Transform::setPosition(oTransform, oPos - normal * delta);
                        }
                    }
                }
            }

            void _solveCollisions(const Entity &cEntity, glm::vec3 &actualPos, const ColliderComponent *colliderArray, const size_t& size, const std::unordered_map<size_t, std::set<Entity>> &colliderIndexToEntity) {
                auto &cCollider = _coordinator->getComponent<ColliderComponent>(cEntity);
                for (size_t colliderId = 0; colliderId < size; colliderId++) {
                    auto &oCollider = colliderArray[colliderId];
                    switch (oCollider.type) {
                        case ColliderComponent::CIRCLE:
                            _solverCircleCollision(cEntity, actualPos, colliderIndexToEntity.at(colliderId), oCollider, cCollider);
                            break;
                        case ColliderComponent::BOX:
                            break;
                    }
                }
            }

            float _circleSdf(const glm::vec3 &pos, const glm::vec3 &center, const float &radius) {
                return glm::length(pos - center) - radius;
            }

            float _boxSdf(const glm::vec3 &pos, const glm::vec3 &center, const glm::vec2 &size) {
                glm::vec3 d = glm::abs(pos - center) - glm::vec3(size.x, size.y, size.x);
                return glm::min(glm::max(d.x, glm::max(d.y, d.z)), 0.0f) + glm::length(glm::max(d, glm::vec3(0.0f)));
            }

            void _updateCircleConstraint(const ConstraintComponent &constraint, RigigbodyComponent &rigidbody, glm::vec3 &actualPos) {
                float dst = _circleSdf(actualPos, constraint.circle.center, constraint.circle.radius);
                if (dst > 0) {
                    glm::vec3 dir = glm::normalize(actualPos - constraint.circle.center);
                    actualPos = constraint.circle.center + dir * constraint.circle.radius;
                }
            }

            void _updateConstraints(glm::vec3 &actualPos, RigigbodyComponent &rigidbody, const ConstraintComponent *constraintArray, const size_t& size, const std::unordered_map<size_t, std::set<Entity>> &constraintIndexToEntity) {
                for (size_t i = 0; i < size; i++) {
                    auto &constraint = constraintArray[i];

                    switch (constraint.type) {
                        case ConstraintComponent::CIRCLE:
                            _updateCircleConstraint(constraint, rigidbody, actualPos);
                            break;
                        case ConstraintComponent::BOX:
                            break;
                    }
                }
            }

            void _updatePosition(glm::vec3 &actualPos, TransformComponent &transform, const double &deltaTime, RigigbodyComponent &rigidbody) {
                const glm::vec3 velocity = actualPos - rigidbody.oldPos;
                rigidbody.oldPos = actualPos;

                actualPos += velocity + glm::vec3(rigidbody.acceleration.x * deltaTime * deltaTime, rigidbody.acceleration.y * deltaTime * deltaTime, rigidbody.acceleration.z * deltaTime * deltaTime);

                rigidbody.acceleration = glm::vec3(0, 0, 0);
                Transform::setPosition(transform, actualPos);

            }

            void _updateGravity(RigigbodyComponent &rigidbody) {
                rigidbody.acceleration += gravity;
            }
    };
}

#endif /* !PHYSICSSYSTEM_HPP_ */
