/*
** EPITECH PROJECT, 2024
** RTypeRenderEngine
** File description:
** SoloudEngine
*/

#include "RTypeEngine/Audio/SoloudEngine.hpp"

namespace RTypeEngine
{
    SoloudEngine::SoloudEngine() {
        _engine.init();

        _engine.play(_musicBus);
        _engine.play(_sfxBus);
    }

    SoloudEngine::~SoloudEngine() {
        _engine.deinit();
    }

    void SoloudEngine::addSound(SoLoud::Wav *sound, const float &volume, const bool &paused) {
        if (_current.find(sound) != _current.end()) {
            _engine.stop(_current[sound]);
        }
        _current[sound] = _sfxBus.play3d(*sound, 0, 0, 0, 0, 0, 0, volume, paused);
    }

    void SoloudEngine::pauseSound(SoLoud::Wav *sound) {
        if (_current.find(sound) == _current.end())
            return;
        SoLoud::handle handle = _current[sound];
        _engine.setPause(handle, !_engine.getPause(handle));
    }

    void SoloudEngine::addMusic(SoLoud::WavStream *sound, const float &volume, const bool &paused) {
        if (_current.find(sound) != _current.end()) {
            _engine.stop(_current[sound]);
        }
        _current[sound] = _musicBus.play3d(*sound, 0, 0, 0, 0, 0, 0, volume, paused);
    }

    void SoloudEngine::pauseMusic(SoLoud::WavStream *sound) {
        if (_current.find(sound) == _current.end())
            return;
        SoLoud::handle handle = _current[sound];
        _engine.setPause(handle, !_engine.getPause(handle));
    }
} // namespace RTypeEngine
