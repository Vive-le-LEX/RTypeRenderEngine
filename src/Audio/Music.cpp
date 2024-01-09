/*
** EPITECH PROJECT, 2024
** RTypeRenderEngine
** File description:
** Music
*/

#include "RTypeEngine/Audio/Music.hpp"

namespace RTypeEngine {
    Music::Music(const std::string &path, const glm::vec3 &position) : _position(position), _paused(false), _volume(1) {
        _wavStream.load(path.c_str());
        _wavStream.setInaudibleBehavior(true, false);
    }
} // namespace RTypeEngine
