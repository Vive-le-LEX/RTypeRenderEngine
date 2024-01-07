/*
** EPITECH PROJECT, 2024
** RTypeRenderEngine
** File description:
** Sequence
*/

#ifndef SEQUENCE_HPP_
    #define SEQUENCE_HPP_

    #include <map>
    #include <fstream>
    #include <iostream>
    #include <tuple>
    #include <string>
    #include <type_traits>

    #include <nlohmann/json.hpp>
    using json = nlohmann::json;

    #include "RTypeEngine/System/Cinematic/Keyframe.hpp"

namespace RTypeEngine::Animation {

    template <typename T>
    struct AnimationTypeName : std::false_type {};

    template <>
    struct AnimationTypeName<float> : std::true_type {
        static constexpr const char *name() { return "float"; }
    };

    template <>
    struct AnimationTypeName<int> : std::true_type {
        static constexpr const char *name() { return "int"; }
    };

    template <>
    struct AnimationTypeName<bool> : std::true_type {
        static constexpr const char *name() { return "bool"; }
    };

    struct VariableInfo {
        IKeyframe* keyframe;
        std::string type;
    };

    class Sequence {
        public:
            Sequence(const std::string &filepath, const bool &loop = false) : _loop(loop), _isPlaying(true), _time(0.0), _prevFrameTime(0.0), _currentFrame(0), _maxFrame(0) {
                std::ifstream f(filepath);
                try {
                    _data = json::parse(f);
                    for (auto &var : _data["variables"].items()) {
                        const std::string name = var.key();
                        if (var.value().is_string()) {
                            _declaredVariables[name] = {nullptr, var.value().get<std::string>()};
                        } else if (var.value().is_object()) {
                            _declaredObjects[name] = std::map<std::string, VariableInfo>();
                            for (auto &obj : var.value().items()) {
                                _declaredObjects[name][obj.key()] = {nullptr, obj.value().get<std::string>()};
                            }
                        }
                    }
                    if (!_data["frames"].is_array()) {
                        throw std::runtime_error("Invalid sequence file: frames is not an array");
                    }
                    _frames = _data["frames"];
                    _maxFrame = _frames.size();
                    if (!_data.contains("triggers")) {
                        throw std::runtime_error("Invalid sequence file: no triggers");
                    }
                    if (!_data["triggers"].is_array()) {
                        throw std::runtime_error("Invalid sequence file: triggers is not an array");
                    }
                    for (auto &trigger : _data["triggers"].items()) {
                        const std::string name = trigger.value().get<std::string>();
                        _triggers[name] = nullptr;
                        _triggersNames.push_back(name);
                    }
                } catch (std::exception &e) {
                    std::cerr << "Failed to parse sequence file: " << e.what() << std::endl;
                }
            }
            ~Sequence() = default;

            template<typename T>
            void registerVariable(const std::string &name, T *value) {
                static_assert(AnimationTypeName<T>::value, "Cannot register variable in sequence: type not supported");

                if (_declaredVariables.find(name) == _declaredVariables.end()) {
                    std::cerr << "Failed to register variable: " << name << std::endl;
                    return;
                }

                const std::string &type = _declaredVariables[name].type;
                if (std::strcmp(AnimationTypeName<T>::name(), type.c_str()) != 0) {
                    std::cerr << "Cannot register variable: \"" << name << "\" with type mismatch between given: " << AnimationTypeName<T>::name() << " and expected: " << type << " in object " << name << std::endl;
                    return;
                }
                _declaredVariables[name].keyframe = new Keyframe(value);
            }

            template<typename... Pairs>
            void registerObject(const char *name, const Pairs&&... args) {
                registerObjectHelper(name, args...);
            }

            void registerTrigger(const std::string &name, std::function<void(void)> *trigger) {
                if (_triggersNames.end() == std::find(_triggersNames.begin(), _triggersNames.end(), name)) {
                    std::cerr << "Failed to register trigger: " << name << " is not explicited in sequence file" << std::endl;
                    return;
                }
                _triggers[name] = trigger;
            }

            void advance(const double &deltaTime) {
                if (!_isPlaying)
                    return;
                _time += deltaTime;

                auto &frame = _frames.at(_currentFrame);
                const auto &reachTime = frame["time"].get<double>();
                if (_time >= reachTime) {
                    _currentFrame++;
                    _prevFrameTime = reachTime;
                    for (auto &var : _declaredVariables) {
                        if (var.second.keyframe == nullptr)
                            continue;
                        var.second.keyframe->updatePreviousValue();
                    }
                    for (auto &obj : _declaredObjects) {
                        for (auto &var : obj.second) {
                            if (var.second.keyframe == nullptr)
                                continue;
                            var.second.keyframe->updatePreviousValue();
                        }
                    }
                    const auto &frameTriggers = frame["triggers"];
                    for (size_t i = 0; i < frameTriggers.size(); i++) {
                        const std::string &trigger = frameTriggers[i];
                        if (_triggers.find(trigger) == _triggers.end()) {
                            continue;
                        }
                        _triggers[trigger]->operator()();
                    }
                    if (_currentFrame >= _maxFrame) {
                        for (auto &var : _declaredVariables) {
                            if (var.second.keyframe == nullptr)
                                continue;
                            var.second.keyframe->setTargetValue(frame["values"][var.first], 1.0);
                        }
                        for (auto &obj : _declaredObjects) {
                            int cField = 0;
                            for (auto &var : obj.second) {
                                if (var.second.keyframe == nullptr) {
                                    cField++;
                                    continue;
                                }
                                var.second.keyframe->setTargetValue(frame["values"][obj.first][cField], 1.0);
                                cField++;
                            }
                        }
                        _currentFrame = 0;
                        _prevFrameTime = 0.0;
                        frame = _frames.at(0);
                        if (!_loop) {
                            _isPlaying = false;
                            return;
                        }
                    }
                }
                const auto &frameValues = frame["values"];
                double percent = 1.0;
                if (reachTime - _prevFrameTime) {
                    percent = (_time - _prevFrameTime) / (reachTime - _prevFrameTime);
                }
                for (auto &var : _declaredVariables) {
                    if (var.second.keyframe == nullptr)
                        continue;
                    var.second.keyframe->setTargetValue(frameValues[var.first], percent);
                }
                for (auto &obj : _declaredObjects) {
                    int cField = 0;
                    for (auto &var : obj.second) {
                        if (var.second.keyframe == nullptr) {
                            cField++;
                            continue;
                        }
                        var.second.keyframe->setTargetValue(frameValues[obj.first][cField], percent);
                        cField++;
                    }
                }
            }
        private:
            template <typename T>
            void registerObjectHelper(const char* name, std::pair<const char*, T*> obj) {
                static_assert(AnimationTypeName<T>::value, "Cannot register variable in sequence: type not supported");
                if (_declaredObjects.find(name) == _declaredObjects.end()) {
                    std::cerr << "No registered object with name: " << name << std::endl;
                    return;
                }
                if (_declaredObjects[name].find(obj.first) == _declaredObjects[name].end()) {
                    std::cerr << "No registered variable with name: " << obj.first << " in object " << name << std::endl;
                    return;
                }
                const std::string &type = _declaredObjects[name][obj.first].type;
                if (std::strcmp(AnimationTypeName<T>::name(), type.c_str()) != 0) {
                    std::cerr << "Cannot register variable: \"" << obj.first << "\" with type mismatch between given: " << AnimationTypeName<T>::name() << " and expected: " << type << " in object " << name << std::endl;
                    return;
                }
                _declaredObjects[name][obj.first].keyframe = new Keyframe(obj.second);
            }

            template <typename T, typename... Pairs>
            void registerObjectHelper(const char* name, T obj, const std::pair<const char*, Pairs>&... rest) {
                registerObjectHelper(name, obj);

                registerObjectHelper(name, rest...);
            }
            std::vector<std::string> _ownedTriggers;
            std::vector<std::string> _triggersNames;
            std::map<std::string, VariableInfo> _declaredVariables;
            std::map<std::string, std::map<std::string, VariableInfo>> _declaredObjects;
            std::map<std::string, std::function<void(void)>*> _triggers;
            json _data;
            json _frames;

            bool _loop;
            bool _isPlaying;

            double _time;
            double _prevFrameTime;
            int _currentFrame;
            int _maxFrame;
    };
}

#endif /* !SEQUENCE_HPP_ */
