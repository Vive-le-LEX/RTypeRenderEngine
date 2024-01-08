/*
** EPITECH PROJECT, 2024
** RTypeRenderEngine
** File description:
** AnimationCurve
*/

#ifndef ANIMATIONCURVE_HPP_
#define ANIMATIONCURVE_HPP_

#include <functional>
#define _USE_MATH_DEFINES
#include <math.h>
#include <unordered_map>

namespace RTypeEngine::Animation {
class AnimationCurve {
   public:
    AnimationCurve(std::function<double(double)> func) : _func(func){};
    ~AnimationCurve() = default;

    double getValue(double value) const {
        return _func(value);
    }

   private:
    std::function<double(double)> _func;
};

// https://easings.net/
static const AnimationCurve Linear = AnimationCurve([](double value) {
    return value;
});

static const AnimationCurve EaseIn = AnimationCurve([](double value) {
    return value * value;
});

static const AnimationCurve EaseOut = AnimationCurve([](double value) {
    return value * (2 - value);
});

static const AnimationCurve EaseInOut = AnimationCurve([](double value) {
    if (value < 0.5f)
        return 2 * value * value;
    else
        return -1 + (4 - 2 * value) * value;
});

static const AnimationCurve EaseInElastic = AnimationCurve([](double value) {
    float c4 = (2 * M_PI) / 3;

    if (value == 0)
        return 0.0;
    if (value == 1)
        return 1.0;
    return -std::pow(2, 10 * value - 10) * std::sin((value * 10 - 10.75) * c4);
});

static const AnimationCurve EaseOutElastic = AnimationCurve([](double value) {
    float c4 = (2 * M_PI) / 3;

    if (value == 0)
        return 0.0;
    if (value == 1)
        return 1.0;
    return std::pow(2, -10 * value) * std::sin((value * 10 - 0.75) * c4) + 1;
});

static const AnimationCurve EaseInOutElastic = AnimationCurve([](double value) {
    float c5 = (2 * M_PI) / 4.5;

    if (value == 0)
        return 0.0;
    if (value == 1)
        return 1.0;
    if (value < 0.5)
        return -(std::pow(2, 20 * value - 10) * std::sin((20 * value - 11.125) * c5)) / 2;
    else
        return (std::pow(2, -20 * value + 10) * std::sin((20 * value - 11.125) * c5)) / 2 + 1;
});

static const AnimationCurve EaseOutBounce = AnimationCurve([](double value) {
    if (value < 1 / 2.75)
        return 7.5625 * value * value;
    else if (value < 2 / 2.75)
        return 7.5625 * (value -= 1.5 / 2.75) * value + 0.75;
    else if (value < 2.5 / 2.75)
        return 7.5625 * (value -= 2.25 / 2.75) * value + 0.9375;
    else
        return 7.5625 * (value -= 2.625 / 2.75) * value + 0.984375;
});

static const AnimationCurve EaseInBounce = AnimationCurve([](double value) {
    return 1 - EaseOutBounce.getValue(1 - value);
});

static const AnimationCurve EaseInOutBounce = AnimationCurve([](double value) {
    if (value < 0.5)
        return EaseInBounce.getValue(value * 2) * 0.5;
    else
        return EaseOutBounce.getValue(value * 2 - 1) * 0.5 + 0.5;
});

static const AnimationCurve EaseInBack = AnimationCurve([](double value) {
    float c1 = 1.70158;
    float c3 = c1 + 1;

    return c3 * value * value * value - c1 * value * value;
});

static const AnimationCurve EaseOutBack = AnimationCurve([](double value) {
    float c1 = 1.70158;
    float c3 = c1 + 1;

    return 1 + c3 * std::pow(value - 1, 3) + c1 * std::pow(value - 1, 2);
});

static const AnimationCurve EaseInOutBack = AnimationCurve([](double value) {
    float c1 = 1.70158;
    float c2 = c1 * 1.525;

    if (value < 0.5)
        return (std::pow(2 * value, 2) * ((c2 + 1) * 2 * value - c2)) / 2;
    else
        return (std::pow(2 * value - 2, 2) * ((c2 + 1) * (value * 2 - 2) + c2) + 2) / 2;
});

static const AnimationCurve EaseInCirc = AnimationCurve([](double value) {
    return -(std::sqrt(1 - value * value) - 1);
});

static const AnimationCurve EaseOutCirc = AnimationCurve([](double value) {
    return std::sqrt(1 - std::pow(value - 1, 2));
});

static const AnimationCurve EaseInOutCirc = AnimationCurve([](double value) {
    if (value < 0.5)
        return (1 - std::sqrt(1 - std::pow(2 * value, 2))) / 2;
    else
        return (std::sqrt(1 - std::pow(-2 * value + 2, 2)) + 1) / 2;
});

static const AnimationCurve EaseInQuad = AnimationCurve([](double value) {
    return value * value;
});

static const AnimationCurve EaseOutQuad = AnimationCurve([](double value) {
    return value * (2 - value);
});

static const AnimationCurve EaseInOutQuad = AnimationCurve([](double value) {
    if (value < 0.5)
        return 2 * value * value;
    else
        return -1 + (4 - 2 * value) * value;
});

static const AnimationCurve EaseInQuart = AnimationCurve([](double value) {
    return value * value * value * value;
});

static const AnimationCurve EaseOutQuart = AnimationCurve([](double value) {
    return 1 - std::pow(value - 1, 4);
});

static const AnimationCurve EaseInOutQuart = AnimationCurve([](double value) {
    if (value < 0.5)
        return 8 * value * value * value * value;
    else
        return 1 - 8 * std::pow(value - 1, 4);
});

static const AnimationCurve EaseInQuint = AnimationCurve([](double value) {
    return value * value * value * value * value;
});

static const AnimationCurve EaseOutQuint = AnimationCurve([](double value) {
    return 1 + std::pow(value - 1, 5);
});

static const AnimationCurve EaseInOutQuint = AnimationCurve([](double value) {
    if (value < 0.5)
        return 16 * value * value * value * value * value;
    else
        return 1 + 16 * std::pow(value - 1, 5);
});

static const AnimationCurve EaseInSine = AnimationCurve([](double value) {
    return -std::cos(value * (M_PI / 2)) + 1;
});

static const AnimationCurve EaseOutSine = AnimationCurve([](double value) {
    return std::sin(value * (M_PI / 2));
});

static const AnimationCurve EaseInOutSine = AnimationCurve([](double value) {
    return -(std::cos(M_PI * value) - 1) / 2;
});

static const AnimationCurve EaseInExpo = AnimationCurve([](double value) {
    return (value == 0) ? 0 : std::pow(2, 10 * (value - 1));
});

static const AnimationCurve EaseOutExpo = AnimationCurve([](double value) {
    return (value == 1) ? 1 : -std::pow(2, -10 * value) + 1;
});

static const AnimationCurve EaseInOutExpo = AnimationCurve([](double value) {
    if (value == 0)
        return 0.0;
    if (value == 1)
        return 1.0;
    if (value < 0.5)
        return std::pow(2, 20 * value - 10) / 2;
    else
        return (2 - std::pow(2, -20 * value + 10)) / 2;
});

static const AnimationCurve EaseInCubic = AnimationCurve([](double value) {
    return value * value * value;
});

static const AnimationCurve EaseOutCubic = AnimationCurve([](double value) {
    return 1 + std::pow(value - 1, 3);
});

static const AnimationCurve EaseInOutCubic = AnimationCurve([](double value) {
    if (value < 0.5)
        return 4 * value * value * value;
    else
        return 1 + 4 * std::pow(value - 1, 3);
});

static const AnimationCurve EaseInCubicHalf = AnimationCurve([](double value) {
    return value * value * value;
});

static const AnimationCurve EaseOutCubicHalf = AnimationCurve([](double value) {
    return 1 + std::pow(value - 1, 3);
});

static const AnimationCurve EaseInOutCubicHalf = AnimationCurve([](double value) {
    if (value < 0.5)
        return 4 * value * value * value;
    else
        return 1 + 4 * std::pow(value - 1, 3);
});

static const AnimationCurve EaseInCubicQuarter = AnimationCurve([](double value) {
    return value * value * value;
});

static const AnimationCurve EaseOutCubicQuarter = AnimationCurve([](double value) {
    return 1 + std::pow(value - 1, 3);
});

static const AnimationCurve EaseInOutCubicQuarter = AnimationCurve([](double value) {
    if (value < 0.5)
        return 4 * value * value * value;
    else
        return 1 + 4 * std::pow(value - 1, 3);
});

static const std::unordered_map<std::string, AnimationCurve> curvesMap = {
    {"Linear", Linear},
    {"EaseIn", EaseIn},
    {"EaseOut", EaseOut},
    {"EaseInOut", EaseInOut},
    {"EaseInElastic", EaseInElastic},
    {"EaseOutElastic", EaseOutElastic},
    {"EaseInOutElastic", EaseInOutElastic},
    {"EaseOutBounce", EaseOutBounce},
    {"EaseInBounce", EaseInBounce},
    {"EaseInOutBounce", EaseInOutBounce},
    {"EaseInBack", EaseInBack},
    {"EaseOutBack", EaseOutBack},
    {"EaseInOutBack", EaseInOutBack},
    {"EaseInCirc", EaseInCirc},
    {"EaseOutCirc", EaseOutCirc},
    {"EaseInOutCirc", EaseInOutCirc},
    {"EaseInQuad", EaseInQuad},
    {"EaseOutQuad", EaseOutQuad},
    {"EaseInOutQuad", EaseInOutQuad},
    {"EaseInQuart", EaseInQuart},
    {"EaseOutQuart", EaseOutQuart},
    {"EaseInOutQuart", EaseInOutQuart},
    {"EaseInQuint", EaseInQuint},
    {"EaseOutQuint", EaseOutQuint},
    {"EaseInOutQuint", EaseInOutQuint},
    {"EaseInSine", EaseInSine},
    {"EaseOutSine", EaseOutSine},
    {"EaseInOutSine", EaseInOutSine},
    {"EaseInExpo", EaseInExpo},
    {"EaseOutExpo", EaseOutExpo},
    {"EaseInOutExpo", EaseInOutExpo},
    {"EaseInCubic", EaseInCubic},
    {"EaseOutCubic", EaseOutCubic},
    {"EaseInOutCubic", EaseInOutCubic},
    {"EaseInCubicHalf", EaseInCubicHalf},
    {"EaseOutCubicHalf", EaseOutCubicHalf},
    {"EaseInOutCubicHalf", EaseInOutCubicHalf},
    {"EaseInCubicQuarter", EaseInCubicQuarter},
    {"EaseOutCubicQuarter", EaseOutCubicQuarter},
    {"EaseInOutCubicQuarter", EaseInOutCubicQuarter},
};

const AnimationCurve *getTypeFromString(const char* str) {
    return &(curvesMap.find(str)->second);
}

}  // namespace RTypeEngine::Animation
#endif /* !ANIMATIONCURVE_HPP_ */
