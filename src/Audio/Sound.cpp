/*
** EPITECH PROJECT, 2024
** RTypeRenderEngine
** File description:
** Sound
*/

#include "RTypeEngine/Audio/Sound.hpp"

namespace RTypeEngine
{
    Sound::Sound(const std::string &path) : _volume(1), _paused(false) {
        _wav.load(path.c_str());
        _wav.setInaudibleBehavior(true, false);
    }

    void Sound::setLooping(const bool &loop) {
        _wav.setLooping(loop);
    }

    const double Sound::getDuration() {
        return _wav.getLength();
    }
} // namespace RTypeEngine
