/*
** EPITECH PROJECT, 2024
** RTypeRenderEngine
** File description:
** WindowDebugger
*/

#ifndef WINDOWDEBUGGER_HPP_
#define WINDOWDEBUGGER_HPP_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "cpuinfo_x86.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <unordered_map>
#include <functional>
#include <vector>

#include "RTypeEngine/Graphics/Text.hpp"
#include "RTypeEngine/Window/Events/KeyboardHandler.hpp"

using namespace cpu_features;

namespace RTypeEngine {
class WindowDebugger {
   public:
    WindowDebugger(GLFWwindow *window, glm::mat4 *projection, double *deltaTime, int *topbarSize, KeyboardHandler &keyboardHandler);
    ~WindowDebugger();

    void switchState();

    void setRefreshRate(const double &refreshRate) {
        _refreshRate = refreshRate;
    }

    const double &getRefreshRate() const {
        return _refreshRate;
    }

    void display();

    template <typename T>
    void addDebugInfo(const std::string &name, T *ptr, std::function<std::string(const T*)> toString) {
        std::function<std::string (const void *)> toStringWrapper = [toString](const void *ptr) {
            return toString(static_cast<const T*>(ptr));
        };
        void *ptrVoid = static_cast<void *>(ptr);
        _dynamicValues[name] = TypedPointer{ptrVoid, toStringWrapper};

        glm::vec2 pos = glm::vec2(_padding, 0.0 + *_topbarSize + _fontSize + _padding);
        pos.y += _dynamicValues.size() * (_fontSize + _padding);
        _dynamicTexts[name] = new Text(name + ": " + toString(ptr), _font, pos, glm::vec4(1, 1, 1, 1), _fontSize);
    }

   protected:
   private:
    void addLeftPanel();

    struct TypedPointer {
        void *ptr;
        std::function<std::string(void *)> toString;
    };

    int *_topbarSize;
    double *_deltaTime;
    glm::f32 *_projection;
    KeyboardHandler *_keyboardHandler;

    bool _isOpen;
    std::vector<Text> _staticTexts;
    std::unordered_map<std::string, Text*> _dynamicTexts;
    std::unordered_map<std::string, TypedPointer> _dynamicValues;
    Font _font;

    int _padding;
    int _fontSize;
    double _refreshRate = 1.0;
    double _lastRefresh = 0.0;
    int _screenWidth;
    int _screenHeight;

    std::unordered_map<std::string, std::string> _cpuInfo;
};
}  // namespace RTypeEngine

#endif /* !WINDOWDEBUGGER_HPP_ */
