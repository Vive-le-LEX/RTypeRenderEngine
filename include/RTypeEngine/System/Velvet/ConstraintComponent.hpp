/*
** EPITECH PROJECT, 2024
** RTypeRenderEngine
** File description:
** ConstraintComponent
*/

#ifndef CONSTRAINTCOMPONENT_HPP_
#define CONSTRAINTCOMPONENT_HPP_

#include "RTypeEngine/System/Velvet/ColliderComponents.hpp"

namespace RTypeEngine
{
    struct CircleConstraintComponent {
        float radius;
        glm::vec3 center;
    };

    struct BoxConstraintComponent {
        glm::vec2 size;
        glm::vec3 center;
    };

    typedef struct ConstraintComponent_s {
        enum Type {
            CIRCLE,
            BOX
        };
        Type type;
        union {
            CircleConstraintComponent circle;
            BoxConstraintComponent box;
        };
    } ConstraintComponent;

    typedef ColliderComponent_s ColliderComponent; //TODO: understand why this is needed in Constraint and not in Collider
} // namespace RTypeEngine


#endif /* !CONSTRAINTCOMPONENT_HPP_ */
