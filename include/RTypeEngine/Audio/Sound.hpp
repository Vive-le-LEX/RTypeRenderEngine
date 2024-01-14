/*
** EPITECH PROJECT, 2024
** RTypeRenderEngine
** File description:
** Sound
*/

#ifndef SOUND_HPP_
#define SOUND_HPP_

#include <string>
#include <memory>
#include "RTypeEngine/System/Core.hpp"
#include "RTypeEngine/System/AssetsManager.hpp"
#include "RTypeEngine/Audio/SoloudEngine.hpp"

namespace RTypeEngine {
class Sound {
    public:
        ~Sound() = default;

        static Sound createFromFile(const std::string &path, const glm::vec3 &position = glm::vec3(0, 0, 0)) {
            Sound sound = Sound(position);
            sound._wav = std::make_shared<SoLoud::Wav>();
            sound._wav->load(path.c_str());
            sound._wav->setInaudibleBehavior(true, false);
            return sound;
        }

        static Sound createFromAssets(const std::string &path, const glm::vec3 &position = glm::vec3(0, 0, 0)) {
            Sound sound = Sound(position);
            auto *data = getEmbeddedAsset<unsigned char>(path);
            sound._wav = std::make_shared<SoLoud::Wav>();
            sound._wav->loadMem(data, getEmbeddedAssetSize(path), false, false);
            sound._wav->setInaudibleBehavior(true, false);
            sound._wav->setLoopPoint(0.0f);
            return sound;
        }

        static Sound createFromMemory(const unsigned char *data, const size_t &size, const glm::vec3 &position = glm::vec3(0, 0, 0)) {
            Sound sound = Sound(position);
            sound._wav = std::make_shared<SoLoud::Wav>();
            sound._wav->loadMem(data, size, false, false);
            sound._wav->setInaudibleBehavior(true, false);
            return sound;
        }

        void setLooping(const bool &loop);
        const double getDuration();

        const double getVolume() const { return _volume; }
        void setVolume(const double &volume) {
            _wav->setVolume(volume);
            _volume = volume;
        }

        void play() {
            _engine.addSound(_wav.get(), _volume, _paused);
        }

        void setPosition(const glm::vec3 &position) {
            _position = position;
            _engine.setSoundPosition(_wav.get(), position);
        }

        void pause() {
            _paused = !_paused;
            _engine.pauseSound(_wav.get());
        }
    protected:
    private:
        Sound(const glm::vec3 &position = glm::vec3(0, 0, 0)) : _position(position), _paused(false), _volume(1) {}
        double _volume;
        bool _paused;
        std::shared_ptr<SoLoud::Wav> _wav;
        glm::vec3 _position;
        SoloudEngine &_engine = SoloudEngine::getInstance();
};
} // namespace RTypeEngine

#endif /* !SOUND_HPP_ */
