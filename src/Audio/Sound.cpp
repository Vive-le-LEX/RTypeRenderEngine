/*
** EPITECH PROJECT, 2024
** RTypeRenderEngine
** File description:
** Sound
*/

#include "RTypeEngine/Audio/Sound.hpp"

namespace RTypeEngine
{
    void Sound::setLooping(const bool &loop) {
        _wav->setLooping(loop);
    }

    const double Sound::getDuration() {
        return _wav->getLength();
    }
} // namespace RTypeEngine
