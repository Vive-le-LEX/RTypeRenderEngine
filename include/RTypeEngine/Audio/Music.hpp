/*
** EPITECH PROJECT, 2024
** RTypeRenderEngine
** File description:
** Music
*/

#ifndef MUSIC_HPP_
#define MUSIC_HPP_

#include <string>
#include <memory>
#include "RTypeEngine/System/Core.hpp"
#include "RTypeEngine/System/AssetsManager.hpp"
#include "RTypeEngine/Audio/SoloudEngine.hpp"

namespace RTypeEngine {
class Music {
    public:
        static Music createFromFile(const std::string &path, const glm::vec3 &position = glm::vec3(0, 0, 0)) {
            Music music = Music(position);
            music._wavStream = std::make_shared<SoLoud::WavStream>();
            music._wavStream->load(path.c_str());
            music._wavStream->setInaudibleBehavior(true, false);
            return music;
        }

        static Music createFromAssets(const std::string &path, const glm::vec3 &position = glm::vec3(0, 0, 0)) {
            Music music = Music(position);
            auto *data = getEmbeddedAsset<unsigned char>(path);
            music._wavStream = std::make_shared<SoLoud::WavStream>();
            music._wavStream->loadMem(data, getEmbeddedAssetSize(path), false, false);
            music._wavStream->setInaudibleBehavior(true, false);
            music._wavStream->setLoopPoint(0.0f);
            return music;
        }

        static Music createFromMemory(const unsigned char *data, const size_t &size, const glm::vec3 &position = glm::vec3(0, 0, 0)) {
            Music music = Music(position);
            music._wavStream = std::make_shared<SoLoud::WavStream>();
            music._wavStream->loadMem(data, size, false, false);
            music._wavStream->setInaudibleBehavior(true, false);
            return music;
        }

        ~Music() = default;

        void setLooping(const bool &loop) {
            _wavStream->setLooping(loop);
        }

        const double getDuration() {
            return _wavStream->getLength();
        }

        const double getVolume() const { return _volume; }
        void setVolume(const double &volume) {
            _wavStream->setVolume(volume);
            _volume = volume;
        }

        void setPosition(const glm::vec3 &position) {
            _position = position;
            _engine.setSoundPosition(_wavStream.get(), position);
        }

        void play() {
            _engine.addMusic(_wavStream.get(), _volume, _paused);
        }
        void pause() {
            _paused = !_paused;
            _engine.pauseMusic(_wavStream.get());
        }
    protected:
    private:
        Music(const glm::vec3 &position) : _position(position), _paused(false), _volume(1) {};
        double _volume;
        bool _paused;
        glm::vec3 _position;
        std::shared_ptr<SoLoud::WavStream> _wavStream;
        SoloudEngine &_engine = SoloudEngine::getInstance();
};
} // namespace RTypeEngine

#endif /* !MUSIC_HPP_ */
