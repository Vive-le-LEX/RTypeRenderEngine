/*
** EPITECH PROJECT, 2024
** RTypeRenderEngine
** File description:
** WindowDebugger
*/

#include "RTypeEngine/Window/WindowDebugger.hpp"

namespace RTypeEngine
{
    WindowDebugger::WindowDebugger(
        GLFWwindow *window,
        glm::mat4 *projection,
        double *deltaTime,
        int *topbarSize,
        KeyboardHandler &keyboardHandler
    ) : _topbarSize(topbarSize),
        _deltaTime(deltaTime),
        _projection(glm::value_ptr(*projection)),
        _keyboardHandler(&keyboardHandler),
        _isOpen(false),
        _font(Font::createFontFromAssets("./INTERNAL_COMIC.TTF"))
    {
        glfwGetWindowSize(window, &_screenWidth, &_screenHeight);
        _padding = 10;
        _fontSize = 20;
        _staticTexts.emplace_back(
            "RTypeEngine 1.0", _font, glm::vec2(_padding, 0.0 + *_topbarSize + _fontSize + _padding), glm::vec4(1, 1, 1, 1), _fontSize
        );
        std::function<std::string(const double *)> toFPS = [](const double *ptr) {
            return std::to_string(static_cast<int>(1.0 / *ptr));
        };
        addDebugInfo("FPS", _deltaTime, toFPS);

        addLeftPanel();
    }

    void WindowDebugger::switchState()
    {
        _isOpen = !_isOpen;
    }

    void WindowDebugger::display()
    {
        if (!_isOpen)
            return;

        if (_lastRefresh < _refreshRate) {
            _lastRefresh += *_deltaTime;
        } else {
            for (auto &pair : _dynamicValues) {
                auto &valueToUpdate = pair.second;
                auto &text = _dynamicTexts[pair.first];
                text->setText(pair.first + ": " + valueToUpdate.toString(valueToUpdate.ptr));
            }
            _lastRefresh = 0.0;
        }

        for (auto &text : _staticTexts) {
            text.draw(_projection);
        }
        for (auto &pair : _dynamicValues) {
            auto &text = _dynamicTexts[pair.first];
            text->draw(_projection);
        }
    }

    void WindowDebugger::addLeftPanel()
    {
        #if defined(CPU_FEATURES_ARCH_X86)
        const X86Info info = GetX86Info();
        const CacheInfo cache_info = GetX86CacheInfo();
        _cpuInfo["arch"] = "x86";
        _cpuInfo["brand"] = info.brand_string;
        _cpuInfo["family"] = std::to_string(info.family);
        _cpuInfo["model"] = std::to_string(info.model);
        _cpuInfo["stepping"] = std::to_string(info.stepping);
        _cpuInfo["uarch"] = GetX86MicroarchitectureName(GetX86Microarchitecture(&info));
        #elif defined(CPU_FEATURES_ARCH_ARM)
        const ArmInfo info = GetArmInfo();
        _cpuInfo["arch"] = "ARM";
        _cpuInfo["implementer"] = std::to_string(info.implementer);
        _cpuInfo["architecture"] = std::to_string(info.architecture);
        _cpuInfo["variant"] = std::to_string(info.variant);
        _cpuInfo["part"] = std::to_string(info.part);
        _cpuInfo["revision"] = std::to_string(info.revision);
        #elif defined(CPU_FEATURES_ARCH_AARCH64)
        const Aarch64Info info = GetAarch64Info();
        _cpuInfo["arch"] = "aarch64";
        _cpuInfo["implementer"] = std::to_string(info.implementer);
        _cpuInfo["variant"] = std::to_string(info.variant);
        _cpuInfo["part"] = std::to_string(info.part);
        _cpuInfo["revision"] = std::to_string(info.revision);
        #elif defined(CPU_FEATURES_ARCH_MIPS)
        const MipsInfo info = GetMipsInfo();
        _cpuInfo["arch"] = "mips";
        #elif defined(CPU_FEATURES_ARCH_PPC)
        const PPCInfo info = GetPPCInfo();
        const PPCPlatformStrings strings = GetPPCPlatformStrings();
        _cpuInfo["arch"] = "ppc";
        _cpuInfo["platform"] = strings.platform;
        _cpuInfo["model"] = strings.model;
        _cpuInfo["machine"] = strings.machine;
        _cpuInfo["cpu"] = strings.cpu;
        _cpuInfo["instruction"] = strings.type.platform;
        _cpuInfo["microarchitecture"] = strings.type.base_platform;
        #elif defined(CPU_FEATURES_ARCH_S390X)
        const S390XInfo info = GetS390XInfo();
        const S390XPlatformStrings strings = GetS390XPlatformStrings();
        _cpuInfo["arch"] = "s390x";
        _cpuInfo["platform"] = "zSeries";
        _cpuInfo["model"] = strings.type.platform;
        _cpuInfo["# processors"] = std::to_string(strings.num_processors);
        #elif defined(CPU_FEATURES_ARCH_RISCV)
        const RiscvInfo info = GetRiscvInfo();
        _cpuInfo["arch"] = "risc-v";
        _cpuInfo["vendor"] = info.vendor;
        _cpuInfo["microarchitecture"] = info.uarch;
        #elif defined(CPU_FEATURES_ARCH_LOONGARCH)
        const LoongArchInfo info = GetLoongArchInfo();
        _cpuInfo["arch"] = "loongarch";
        #endif

        GLFWmonitor* primary = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(primary);
        std::string resolution = std::to_string(mode->width) + "x" + std::to_string(mode->height);

        const char *openGlVersion = (const char *)glGetString(GL_VERSION);
        std::vector<std::string> lines;
        auto brandNameIt = _cpuInfo.find("brand");
        std::string brandName = "CPU: ";
        if (brandNameIt != _cpuInfo.end())
            brandName += brandNameIt->second;
        else
            brandName += "Unknown";
        lines.push_back(brandName + " " + _cpuInfo["arch"]);
        lines.push_back("OpenGL " + std::string(openGlVersion));
        lines.push_back("Display: " + resolution);
        auto y = *_topbarSize + _fontSize + _padding;
        for (auto &line : lines) {
            auto text = Text(line, _font, glm::vec2(_padding, 0.0 + *_topbarSize + _fontSize + _padding), glm::vec4(1, 1, 1, 1), _fontSize);
            auto x = _screenWidth - text.getWidth() - _padding;
            text.setPosition(glm::vec2(x, y));
            _staticTexts.push_back(text);
            y += _fontSize + _padding;
        }
    }
} // namespace RTypeEngine
