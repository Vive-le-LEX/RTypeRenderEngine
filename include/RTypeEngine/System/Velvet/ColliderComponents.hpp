/*
** EPITECH PROJECT, 2024
** RTypeRenderEngine
** File description:
** ColliderComponent
*/

#ifndef COLLIDERCOMPONENTS_HPP_
#define COLLIDERCOMPONENTS_HPP_

#include <glm/glm.hpp>

struct CircleColliderComponent {
    float radius;
    glm::vec3 center;
};

struct BoxColliderComponent {
    glm::vec2 size;
    glm::vec3 center;
};

struct ColliderComponent_s {
    enum Type {
        CIRCLE,
        BOX
    };
    Type type;
    union {
        CircleColliderComponent circle;
        BoxColliderComponent box;
    };
};

#endif /* !COLLIDERCOMPONENTS_HPP_ */
