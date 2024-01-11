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

namespace RTypeEngine {
namespace Animation {
/**
 * @brief Keyframe interface
 * @details This class wraps the value to be animated and his previous value
 */
class IKeyframe {
   public:
    virtual ~IKeyframe() = default;
    /**
     * @brief Set the Target Value object
     * @note This shouldn't be used directly
     * @details This method is used to set the value of the object to be animated
     */
    virtual void setTargetValue(const json &newValue, const float &percent) = 0;

    /**
     * @brief Update the previous value
     * @note This shouldn't be used directly
     * @details This method is used to update the previous value of the object to be animated
     */
    virtual void updatePreviousValue() = 0;
};

/**
 * @brief Wrapper for animatable type
 * @details This template class is used to implement the behavior of T type between 0 and 1
 */
template <typename T>
class Keyframe : public IKeyframe {
   public:
   /**
    * @brief Construct a new Keyframe object
    * @note This shouldn't be used directly
    * @details This constructor initialize the value and the previous value to the same value given in parameter
    * @param value A pointer to the value that is going to be animated
    */
    Keyframe(T *value) : _value(value), _previousValue(*value) {}
    ~Keyframe() = default;

    /**
     * @brief Get a reference to the value
     * @return A reference to the value
     */
    T &getValue() const { return *_value; }

    /**
     * @brief Set the Target Value object
     * @note This shouldn't be used directly
     * @details This method is used to set the value of the object to be animated
     */
    void setTargetValue(const json &newValue, const float &percent) final {
        *_value = _previousValue + (newValue.get<T>() - _previousValue) * percent;
    }

    /**
     * @brief Update the previous value
     * @note This shouldn't be used directly
     * @details This method is used to update the previous value of the object to be animated
     */
    void updatePreviousValue() final { _previousValue = *_value; }
   private:
    T *_value;
    T _previousValue;
};
}  // namespace Animation
}  // namespace RTypeEngine

#endif /* !ANIMATABLE_HPP_ */
