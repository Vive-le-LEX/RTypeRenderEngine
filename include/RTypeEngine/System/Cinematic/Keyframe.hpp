/*
** EPITECH PROJECT, 2024
** RTypeRenderEngine
** File description:
** KeyFrame
*/

#ifndef KEYFRAME_HPP_
#define KEYFRAME_HPP_

    #include <nlohmann/json.hpp>
    using json = nlohmann::json;

namespace RTypeEngine::Animation {
class IKeyframe {
   public:
    virtual ~IKeyframe() = default;
    virtual void setTargetValue(const json &newValue, const float &percent) = 0;
    virtual void updatePreviousValue() = 0;
};

template <typename T>
class Keyframe : public IKeyframe {
   public:
    Keyframe(T *value) : _value(value), _previousValue(*value) {}
    ~Keyframe() = default;

    T &getValue() const { return *_value; }
    void setTargetValue(const json &newValue, const float &percent) final {
        *_value = _previousValue + (newValue.get<T>() - _previousValue) * percent;
    }
    void updatePreviousValue() final { _previousValue = *_value; }
   private:
    T *_value;
    T _previousValue;
};
}  // namespace RTypeEngine::Animation

#endif /* !ANIMATABLE_HPP_ */
