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
/**
 * @brief Handles the native debugger
 * @details This class is used to handle the debugger. It will display the debugger and updates the values
 */
class WindowDebugger {
   public:
   /**
    * @brief Construct a new Window Debugger object
    * @param window The window to display the debugger on
    * @param projection The pointer to the projection matrix of the window
    * @param deltaTime The pointer to the deltaTime of the window
    * @param topbarSize The pointer to the size of the topbar of the window
    * @param keyboardHandler The reference to keyboardHandler of the window
    * @note You should never call this constructor directly. Use your Window class to get the debugger
    */
    WindowDebugger(GLFWwindow *window, glm::mat4 *projection, double *deltaTime, int *topbarSize, KeyboardHandler &keyboardHandler);
    ~WindowDebugger() = default;

    /**
     * @brief Switch the debugger state
     * @details This function will toggle if the debugger is shown or not
    */
    void switchState();

    /**
     * @brief Set the refresh rate of the debugger
     * @details Every refreshRate seconds, the debugger will update the values
     * @param refreshRate The refresh rate in seconds
     */
    void setRefreshRate(const double &refreshRate) {
        _refreshRate = refreshRate;
    }

    /**
     * @brief Get the refresh rate of the debugger
     * @return The refresh rate in seconds
     */
    const double &getRefreshRate() const {
        return _refreshRate;
    }

    /**
     * @brief Draws the debugger
     * @details This function will draw the debugger on the window he is attached to
     */
    void display();

    /**
     * @brief Add a dynamic value to the debugger
     * @details This function will add a dynamic value to the debugger. The value will be updated automatically by the debugger.
     * @param name The name of the value
     * @param ptr The pointer to the value
     * @param toString The function to convert the value to a string
     * @tparam T The type of the value
     */
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
    /**
     * @brief Add a dynamic value to the debugger
     * @details This function will add a dynamic value to the debugger. The value will be updated automatically by the debugger.
     * @param name The name of the value
     * @param ptr The pointer to the value
     *
     * @tparam T The type of the value
     *
     * @note This function will use std::to_string to convert the value to a string
     */
    template <typename T>
    void addDebugInfo(const std::string &name, T *ptr) {
        std::function<std::string (const T *)> toString = [](const T *ptr) {
            return std::to_string(*ptr);
        };
        addDebugInfo(name, ptr, toString);
    }

    /// @private
    void addDebugInfo(const std::string &name, glm::vec3 *ptr) {
        std::function<std::string (const glm::vec3 *)> toString = [](const glm::vec3 *ptr) {
            return std::to_string(ptr->x) + ", " + std::to_string(ptr->y) + ", " + std::to_string(ptr->z);
        };
        addDebugInfo(name, ptr, toString);
    }

    /// @private
    void addDebugInfo(const std::string &name, glm::vec2 *ptr) {
        std::function<std::string (const glm::vec2 *)> toString = [](const glm::vec2 *ptr) {
            return std::to_string(ptr->x) + ", " + std::to_string(ptr->y);
        };
        addDebugInfo(name, ptr, toString);
    }

    /// @private
    void addDebugInfo(const std::string &name, glm::vec4 *ptr) {
        std::function<std::string (const glm::vec4 *)> toString = [](const glm::vec4 *ptr) {
            return std::to_string(ptr->x) + ", " + std::to_string(ptr->y) + ", " + std::to_string(ptr->z) + ", " + std::to_string(ptr->w);
        };
        addDebugInfo(name, ptr, toString);
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
