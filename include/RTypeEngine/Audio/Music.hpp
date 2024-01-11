/*
** EPITECH PROJECT, 2024
** RTypeRenderEngine
** File description:
** Music
*/

#ifndef MUSIC_HPP_
#define MUSIC_HPP_

#include <string>
#include "RTypeEngine/Audio/SoloudEngine.hpp"

namespace RTypeEngine {
class Music {
    public:
        explicit Music(const std::string &path, const glm::vec3 &position = glm::vec3(0, 0, 0));
        ~Music() = default;

        void setLooping(const bool &loop) {
            _wavStream.setLooping(loop);
        }

        const double getDuration() {
            return _wavStream.getLength();
        }

        const double getVolume() const { return _volume; }
        void setVolume(const double &volume) {
            _wavStream.setVolume(volume);
            _volume = volume;
        }

        void setPosition(const glm::vec3 &position) {
            _position = position;
            _engine.setSoundPosition(&_wavStream, position);
        }

        void play() {
            _engine.addMusic(&_wavStream, _volume, _paused);
        }
        void pause() {
            _paused = !_paused;
            _engine.pauseMusic(&_wavStream);
        }
    protected:
    private:
        double _volume;
        bool _paused;
        glm::vec3 _position;
        SoLoud::WavStream _wavStream;
        SoloudEngine &_engine = SoloudEngine::getInstance();
};
} // namespace RTypeEngine

#endif /* !MUSIC_HPP_ */
