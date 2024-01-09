/*
** EPITECH PROJECT, 2024
** RTypeRenderEngine
** File description:
** Sound
*/

#ifndef SOUND_HPP_
#define SOUND_HPP_

#include <string>
#include "RTypeEngine/Audio/SoloudEngine.hpp"

namespace RTypeEngine {
class Sound {
    public:
        explicit Sound(const std::string &path);
        ~Sound() = default;

        void setLooping(const bool &loop);
        const double getDuration();

        const double getVolume() const { return _volume; }
        void setVolume(const double &volume) {
            _wav.setVolume(volume);
            _volume = volume;
        }

        void play() {
            _engine.addSound(&_wav, _volume, _paused);
        }
        void pause() {
            _paused = !_paused;
            _engine.pauseSound(&_wav);
        }
    protected:
    private:
        double _volume;
        bool _paused;
        SoLoud::Wav _wav;
        SoloudEngine &_engine = SoloudEngine::getInstance();
};
} // namespace RTypeEngine

#endif /* !SOUND_HPP_ */
