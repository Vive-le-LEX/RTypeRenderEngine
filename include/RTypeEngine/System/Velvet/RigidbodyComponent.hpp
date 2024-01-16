/*
** EPITECH PROJECT, 2024
** RTypeRenderEngine
** File description:
** Rigidbody
*/

#ifndef RIGIDBODY_HPP_
#define RIGIDBODY_HPP_

#include <glm/glm.hpp>

namespace RTypeEngine {
    struct RigigbodyComponent {
        glm::vec3 oldPos;
        glm::vec3 acceleration;
        bool isDynamic;
        bool hasCollider;
    };
}

#endif /* !RIGIDBODY_HPP_ */
