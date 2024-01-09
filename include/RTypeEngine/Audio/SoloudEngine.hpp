/*
** EPITECH PROJECT, 2024
** RTypeRenderEngine
** File description:
** SoloudEngine
*/

#ifndef SOLOUDENGINE_HPP_
#define SOLOUDENGINE_HPP_

#include <memory>
#include <iostream>
#include <unordered_map>

#include "glm/vec3.hpp"

#include "soloud.h"
#include "soloud_wav.h"
#include "soloud_wavstream.h"

namespace RTypeEngine {
class SoloudEngine {
    public:
        static SoloudEngine &getInstance() {
            static SoloudEngine instance;
            return instance;
        }

        SoloudEngine(SoloudEngine const &) = delete;
        void operator=(SoloudEngine const &) = delete;

        void setListenerPosition(const glm::vec3 &position) {
            _engine.set3dListenerPosition(position.x, position.y, position.z);
        }

        friend class Music;
        friend class Sound;
    protected:
    private:
        SoloudEngine();
        ~SoloudEngine();
        void updateLoop();

        void addSound(SoLoud::Wav *sound, const float &volume, const bool &paused);
        void pauseSound(SoLoud::Wav *sound);

        void addMusic(SoLoud::WavStream *sound, const float &volume, const bool &paused);
        void pauseMusic(SoLoud::WavStream *sound);

        void setSoundPosition(void *sound, const glm::vec3 &position) {
            if (_current.find((void *)sound) == _current.end())
                return;
            SoLoud::handle handle = _current[(void *)sound];
            _engine.set3dSourcePosition(handle, position.x, position.y, position.z);
            _engine.update3dAudio();
        }
        std::unordered_map<void *, SoLoud::handle> _current;

        SoLoud::Soloud _engine;
        SoLoud::Bus _sfxBus;
        SoLoud::Bus _musicBus;
        SoLoud::Bus _speechBus;
};
} // namespace RTypeEngine

#endif /* !SOLOUDENGINE_HPP_ */
