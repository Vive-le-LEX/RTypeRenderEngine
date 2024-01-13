/*
** EPITECH PROJECT, 2024
** RTypeRenderEngine
** File description:
** AssetsManager
*/

#ifndef ASSETSMANAGER_HPP_
#define ASSETSMANAGER_HPP_
#include <string>
#include <cstring>
#include <filesystem>

#ifndef HAS_EMBEDS
    #define HAS_EMBEDS
#endif

namespace RTypeEngine {
    static size_t getEmbeddedAssetSize(const std::string &path) {
        #ifdef HAS_EMBEDS
            std::filesystem::path p(path);
            if (!p.has_filename() || !p.has_extension())
                return 0;

            auto filename = p.stem().string();
            auto ext = p.extension().string();

            auto customPath = filename + "_" + ext.substr(1);
            if (allEmbedsResources.find(customPath) != allEmbedsResources.end()) {
                return allEmbedsResourcesSizes[customPath];
            }
        #endif
        return 0;
    }

    template<typename T>
    static T *getEmbeddedAsset(const std::string &path) {
        #ifdef HAS_EMBEDS
            std::filesystem::path p(path);
            if (!p.has_filename() || !p.has_extension())
                return nullptr;

            auto filename = p.stem().string();
            auto ext = p.extension().string();

            auto customPath = filename + "_" + ext.substr(1);
            if (allEmbedsResources.find(customPath) != allEmbedsResources.end()) {
                auto &size = allEmbedsResourcesSizes[customPath];
                T* tmp = (T*)malloc(size);
                memcpy(tmp, allEmbedsResources[customPath], size);
                std::cout << "Found embedded asset: " << customPath << std::endl;
                return tmp;
            } else {
                std::cout << "Embedded asset not found: " << customPath << std::endl;
            }
        #endif
        return nullptr;
    }
}

#endif /* !ASSETSMANAGER_HPP_ */
