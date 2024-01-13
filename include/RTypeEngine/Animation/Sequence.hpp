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

    #include "RTypeEngine/System/Core.hpp"
    #include "RTypeEngine/System/AssetsManager.hpp"
    #include "RTypeEngine/Animation/Keyframe.hpp"
    #include "RTypeEngine/Animation/AnimationCurve.hpp"

namespace RTypeEngine {
namespace Animation {

    /// @private
    template <typename T>
    struct AnimationTypeName : std::false_type {};

    /// @private
    template <>
    struct AnimationTypeName<float> : std::true_type {
        static constexpr const char *name() { return "float"; }
    };

    /// @private
    template <>
    struct AnimationTypeName<int> : std::true_type {
        static constexpr const char *name() { return "int"; }
    };

    /// @private
    template <>
    struct AnimationTypeName<bool> : std::true_type {
        static constexpr const char *name() { return "bool"; }
    };

    /**
     * @brief Informations about an animated variable
    */
    struct VariableInfo {
        IKeyframe* keyframe; ///< The pointer to the keyframe of the variable
        const AnimationCurve *curve; ///< The pointer to the AnimationCurve going to be used to interpolate the value
        std::string type; ///< The type of the variable
    };


    /**
     * @brief Represents an animation sequence
     * @details This class is used to represent a timeline from a json file. It will interpolate the values between keyframes
     */
    class Sequence {
        public:
            /**
             * @brief Construct a new Sequence object
             * @details This constructor will parse the json file and initialize the variables and objects
             * @param filepath The path to the json file
             * @param loop If the sequence should loop
             */
            static Sequence createFromFile(const std::string &filepath, const bool &loop = false) {
                Sequence sequence = Sequence(loop);
                std::ifstream f(filepath);
                try {
                    sequence._data = json::parse(f, nullptr, true, true);
                    sequence._init();
                } catch (std::exception &e) {
                    std::cerr << "Failed to parse sequence file: " << e.what() << std::endl;
                }
            }

            static Sequence createFromAssets(const std::string &path, const bool &loop = false) {
                Sequence sequence = Sequence(loop);
                auto *data = getEmbeddedAsset<unsigned char>(path);
                try {
                    sequence._data = json::parse(data, data + getEmbeddedAssetSize(path));
                    sequence._init();
                } catch (std::exception &e) {
                    std::cerr << "Failed to parse sequence file: " << e.what() << std::endl;
                }
                return sequence;
            }

            static Sequence createFromMemory(const unsigned char *data, const size_t &size, const bool &loop = false) {
                Sequence sequence = Sequence(loop);
                try {
                    sequence._data = json::parse(data, data + size);
                    sequence._init();
                } catch (std::exception &e) {
                    std::cerr << "Failed to parse sequence file: " << e.what() << std::endl;
                }
                return sequence;
            }

            ~Sequence() = default;

            /**
             * @brief Play the sequence
             */
            void play() {
                _isPlaying = true;
            }

            /**
             * @brief Pause the sequence
             */
            void pause() {
                _isPlaying = false;
            }

            /**
             * @brief Stop the sequence
             */
            void stop() {
                _isPlaying = false;
                _currentFrame = 0;
                _prevFrameTime = 0.0;
                _time = 0.0;
                _updatePreviousValues();
            }

            /**
             * @brief Set the loop state
             * @param loop The new loop state
             */
            void setLoop(const bool &loop) {
                _loop = loop;
            }

            /**
             * @brief Attribute a value (from your code) to a variable name (from the sequence file)
             * @details This method will check if the type of the variable is the same as the one given in parameter
             * @param name The name of the variable
             * @param value The value to attribute
             * @tparam T The type of the value
             * @note It will only accept float, int and bool
            */
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
                updateInterpolation(_data["frames"].at(_currentFrame)["interpolation"]);
            }

            /**
             * @brief Attribute values of an object (from your code) to an object variable name (from the sequence file)
             * @details This method takes a variable number of std::pairs of variable name and value
             * @param name The name of the object
             * @param args A variable number of Pairs
             * @tparam Pair std::pair<const char*, T*> where T is the type of the value
            */
            template<typename... Pairs>
            void registerObject(const char *name, const Pairs&&... args) {
                registerObjectHelper(name, args...);
            }

            /**
             * @brief Register a trigger
             * @details This method will check if the trigger is declared in the sequence file
             * @param name The name of the trigger
             * @param trigger The trigger
            */
            void registerTrigger(const std::string &name, std::function<void(void)> *trigger) {
                if (_triggersNames.end() == std::find(_triggersNames.begin(), _triggersNames.end(), name)) {
                    std::cerr << "Failed to register trigger: " << name << " is not explicited in sequence file" << std::endl;
                    return;
                }
                _triggers[name] = trigger;
            }

            /**
             * @brief Advance the sequence
             * @details This method will update the values of the variables and objects
             * @param deltaTime The time elapsed since the last call
             * @note This method should be called every frame, it won't update the values if the sequence is not playing nor if the sequence is finished
            */
            void advance(const double &deltaTime)  {
                if (!_isPlaying)
                    return;
                _time += deltaTime;

                auto &frame = _frames.at(_currentFrame);
                const auto &reachTime = frame["time"].get<double>();
                if (_time >= reachTime) {
                    if (_gotoNextFrame(&frame, reachTime)) {
                        return;
                    }
                }
                const auto &frameValues = frame["values"];
                const auto &frameInterpolation = frame["interpolation"];
                double percent = 1.0;
                if (reachTime - _prevFrameTime) {
                    percent = (_time - _prevFrameTime) / (reachTime - _prevFrameTime);
                }
                _updateVariables(frameValues, percent);
                _updateObjects(frameValues, percent);
            }
        private:
            Sequence(const bool &loop) :
                _loop(loop),
                _isPlaying(false),
                _time(0.0),
                _prevFrameTime(0.0),
                _currentFrame(0),
                _maxFrame(0)
            {}
            void _init() {
                for (auto &var : _data["variables"].items()) {
                    const std::string name = var.key();
                    if (var.value().is_string()) {
                        _declaredVariables[name] = {nullptr, nullptr, var.value().get<std::string>()};
                    } else if (var.value().is_object()) {
                        _declaredObjects[name] = std::map<std::string, VariableInfo>();
                        for (auto &obj : var.value().items()) {
                            _declaredObjects[name][obj.key()] = {nullptr, nullptr, obj.value().get<std::string>()};
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
                updateInterpolation(_data["frames"].at(_currentFrame)["interpolation"]);
            }

            void updateInterpolation(const json &interpolation) {
                for (auto &var : interpolation.items()) {
                    const std::string &name = var.key();
                    if (_declaredVariables.find(name) != _declaredVariables.end()) {
                        _declaredVariables[name].curve = getTypeFromString(var.value().get<std::string>().c_str());
                    } else if (_declaredObjects.find(name) != _declaredObjects.end()) {
                        for (size_t i = 0; i < var.value().size(); i++) {
                            const std::string &interpolType = var.value()[i];
                            auto it = _declaredObjects[name].begin();
                            std::advance(it, i);
                            _declaredObjects[name][it->first].curve = getTypeFromString(interpolType.c_str());
                        }
                    }
                }
            }

            bool _gotoNextFrame(json *frame, const double &reachTime) {
                _currentFrame++;
                _prevFrameTime = reachTime;
                _updatePreviousValues();
                _checkTriggers((*frame)["triggers"]);
                if (_currentFrame >= _maxFrame) {
                    const auto &values = (*frame)["values"];
                    _updateVariables(values, 1.0);
                    _updateObjects(values, 1.0);
                    _currentFrame = 0;
                    _prevFrameTime = 0.0;
                    _time = 0.0;
                    if (_loop) {
                        const auto &values = _frames.at(_currentFrame)["values"];
                        _updateVariables(values, 0.0);
                        _updateObjects(values, 0.0);
                    }
                    return true;
                }
                return false;
            }

            void _updateObjects(const json &values, const float &percent) {
                for (auto &obj : _declaredObjects) {
                    int cField = 0;
                    for (auto &var : obj.second) {
                        if (var.second.keyframe == nullptr) {
                            cField++;
                            continue;
                        }
                        var.second.keyframe->setTargetValue(values[obj.first][cField], var.second.curve->getValue(percent));
                        cField++;
                    }
                }
            }

            void _updateVariables(const json &values, const float &percent) {
                for (auto &var : _declaredVariables) {
                    if (var.second.keyframe == nullptr)
                        continue;
                    var.second.keyframe->setTargetValue(values[var.first], percent);
                }
            }

            void _updatePreviousValues() {
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
            }

            void _checkTriggers(const json &frameTriggers) {
                for (size_t i = 0; i < frameTriggers.size(); i++) {
                    const std::string &trigger = frameTriggers[i];
                    if (_triggers.find(trigger) == _triggers.end()) {
                        continue;
                    }
                    _triggers[trigger]->operator()();
                }
            }

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
                updateInterpolation(_data["frames"].at(_currentFrame)["interpolation"]);
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
}

#endif /* !SEQUENCE_HPP_ */
