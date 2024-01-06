/*
** EPITECH PROJECT, 2024
** RTypeRenderEngine
** File description:
** Scripting
*/

#include <memory>
#include "LuaCpp.hpp"
#include <glm/glm.hpp>

#ifndef RTYPEENGINE_SCRIPTING_HPP
    #define RTYPEENGINE_SCRIPTING_HPP

    #define USING_SCRIPTING

namespace RTypeEngine {

    template<typename T>
    struct LuaType {
        typedef
            std::conditional_t<std::is_same_v<T, int>, LuaCpp::Engine::LuaTNumber,
            std::conditional_t<std::is_same_v<T, std::string>, LuaCpp::Engine::LuaTString,
            std::conditional_t<std::is_same_v<T, bool>, LuaCpp::Engine::LuaTBoolean,
            void>>
        > type;
    };

    class LuaProgram {
        public:
            static LuaProgram createFromSnippet(const std::string &name, const std::string &snippet, const bool &modifyVariables) {
                LuaProgram program(name);
                program._modifyVariables = modifyVariables;
                program._luaContext.CompileString(name, snippet);
                return program;
            }

            static LuaProgram createFromFile(const std::string &name, const std::string &path, const bool &modifyVariables) {
                LuaProgram program(name);
                program._modifyVariables = modifyVariables;
                program._path = new std::string(path);
                program._luaContext.CompileFile(name, path);
                return program;
            }

            ~LuaProgram() = default;

            void recompile() {
                if (!_path)
                    return;
                _luaContext.CompileFile(_name, *_path);
            }

            void addGlobalVariable(const std::string &name, glm::vec2 &value) {
                auto luaTable = std::make_shared<LuaCpp::Engine::LuaTTable>();
                _luaGlobals[name] = luaTable;
                LuaCpp::Engine::Table::Key key("x");
                LuaCpp::Engine::Table::Key key2("y");
                luaTable->setValue(key, std::make_shared<LuaCpp::Engine::LuaTNumber>(value.x));
                luaTable->setValue(key2, std::make_shared<LuaCpp::Engine::LuaTNumber>(value.y));
                _luaContext.AddGlobalVariable(name, _luaGlobals[name]);
                _globalsType[name] = &typeid(glm::vec2);
                _globalsData[name] = &value;
            }

            void addGlobalVariable(const std::string &name, glm::vec3 &value) {
                auto luaTable = std::make_shared<LuaCpp::Engine::LuaTTable>();
                _luaGlobals[name] = luaTable;
                LuaCpp::Engine::Table::Key key("x");
                LuaCpp::Engine::Table::Key key2("y");
                LuaCpp::Engine::Table::Key key3("z");
                luaTable->setValue(key, std::make_shared<LuaCpp::Engine::LuaTNumber>(value.x));
                luaTable->setValue(key2, std::make_shared<LuaCpp::Engine::LuaTNumber>(value.y));
                luaTable->setValue(key3, std::make_shared<LuaCpp::Engine::LuaTNumber>(value.z));
                _luaContext.AddGlobalVariable(name, _luaGlobals[name]);
                _globalsType[name] = &typeid(glm::vec3);
                _globalsData[name] = &value;
            }

            template<typename T>
            void addGlobalVariable(const std::string &name, T &value) {
                _globalsData[name] = &value;
                _globalsType[name] = &typeid(T);
                _luaGlobals[name] = std::make_shared<typename LuaType<T>::type>(value);
                _luaContext.AddGlobalVariable(name, _luaGlobals[name]);
            }

            template<typename T>
            T &getGlobalVariable(const std::string &name) {
                if (_globalsType[name] == &typeid(T)) {
                    auto var = _globalsData[name];
                    return *static_cast<T *>(var);
                }
                assert(false);
            }

            void run() {
                try {
                    for (auto & luaGlob : _luaGlobals) {
                        void *data = _globalsData[luaGlob.first];
                        if (_globalsType[luaGlob.first] == &typeid(int)) {
                            static_cast<LuaCpp::Engine::LuaTNumber *>(luaGlob.second.get())->setValue(*static_cast<int *>(data));
                        } else if (_globalsType[luaGlob.first] == &typeid(std::string)) {
                            static_cast<LuaCpp::Engine::LuaTString *>(luaGlob.second.get())->setValue(*static_cast<std::string *>(data));
                        } else if (_globalsType[luaGlob.first] == &typeid(bool)) {
                            static_cast<LuaCpp::Engine::LuaTBoolean *>(luaGlob.second.get())->setValue(*static_cast<bool *>(data));
                        } else if (_globalsType[luaGlob.first] == &typeid(glm::vec3)) {
                            auto luaTable = static_cast<LuaCpp::Engine::LuaTTable *>(luaGlob.second.get());
                            auto t = static_cast<LuaCpp::Engine::LuaTTable *>(luaGlob.second.get());

                            LuaCpp::Engine::LuaTNumber &x = static_cast<LuaCpp::Engine::LuaTNumber &>(t->getValue(LuaCpp::Engine::Table::Key("x")));
                            LuaCpp::Engine::LuaTNumber &y = static_cast<LuaCpp::Engine::LuaTNumber &>(t->getValue(LuaCpp::Engine::Table::Key("y")));
                            LuaCpp::Engine::LuaTNumber &z = static_cast<LuaCpp::Engine::LuaTNumber &>(t->getValue(LuaCpp::Engine::Table::Key("z")));

                            x.setValue(static_cast<glm::vec3 *>(data)->x);
                            y.setValue(static_cast<glm::vec3 *>(data)->y);
                            z.setValue(static_cast<glm::vec3 *>(data)->z);
                        } else if (_globalsType[luaGlob.first] == &typeid(glm::vec2)) {
                            auto luaTable = static_cast<LuaCpp::Engine::LuaTTable *>(luaGlob.second.get());
                            auto t = static_cast<LuaCpp::Engine::LuaTTable *>(luaGlob.second.get());

                            LuaCpp::Engine::LuaTNumber &x = static_cast<LuaCpp::Engine::LuaTNumber &>(t->getValue(LuaCpp::Engine::Table::Key("x")));
                            LuaCpp::Engine::LuaTNumber &y = static_cast<LuaCpp::Engine::LuaTNumber &>(t->getValue(LuaCpp::Engine::Table::Key("y")));

                            x.setValue(static_cast<glm::vec2 *>(data)->x);
                            y.setValue(static_cast<glm::vec2 *>(data)->y);
                        } else {
                            assert(false);
                        }
                    }
                    _luaContext.Run(_name);
                    if (!_modifyVariables)
                        return;
                    for (auto &global : _globalsData) {
                        auto luaVar = _luaGlobals[global.first];
                        if (_globalsType[global.first] == &typeid(int)) {
                            *static_cast<int *>(global.second) = static_cast<LuaCpp::Engine::LuaTNumber *>(luaVar.get())->getValue();
                        } else if (_globalsType[global.first] == &typeid(std::string)) {
                            *static_cast<std::string *>(global.second) = static_cast<LuaCpp::Engine::LuaTString *>(luaVar.get())->getValue();
                        } else if (_globalsType[global.first] == &typeid(bool)) {
                            *static_cast<bool *>(global.second) = static_cast<LuaCpp::Engine::LuaTBoolean *>(luaVar.get())->getValue();
                        } else if (_globalsType[global.first] == &typeid(glm::vec3)) {
                            auto luaTable = static_cast<LuaCpp::Engine::LuaTTable *>(luaVar.get());
                            auto t = static_cast<LuaCpp::Engine::LuaTTable *>(luaVar.get());

                            LuaCpp::Engine::LuaTNumber &x = static_cast<LuaCpp::Engine::LuaTNumber &>(t->getValue(LuaCpp::Engine::Table::Key("x")));
                            LuaCpp::Engine::LuaTNumber &y = static_cast<LuaCpp::Engine::LuaTNumber &>(t->getValue(LuaCpp::Engine::Table::Key("y")));
                            LuaCpp::Engine::LuaTNumber &z = static_cast<LuaCpp::Engine::LuaTNumber &>(t->getValue(LuaCpp::Engine::Table::Key("z")));

                            *static_cast<glm::vec3 *>(global.second) = glm::vec3(x.getValue(), y.getValue(), z.getValue());
                        } else if (_globalsType[global.first] == &typeid(glm::vec2)) {
                            auto luaTable = static_cast<LuaCpp::Engine::LuaTTable *>(luaVar.get());
                            auto t = static_cast<LuaCpp::Engine::LuaTTable *>(luaVar.get());

                            LuaCpp::Engine::LuaTNumber &x = static_cast<LuaCpp::Engine::LuaTNumber &>(t->getValue(LuaCpp::Engine::Table::Key("x")));
                            LuaCpp::Engine::LuaTNumber &y = static_cast<LuaCpp::Engine::LuaTNumber &>(t->getValue(LuaCpp::Engine::Table::Key("y")));

                            *static_cast<glm::vec2 *>(global.second) = glm::vec2(x.getValue(), y.getValue());
                        } else {
                            assert(false);
                        }
                    }
                } catch (const std::runtime_error& e) {
                    std::cerr << e.what() << std::endl;
                }
            }

            const std::string &getName() const {
                return _name;
            }

        private:
            LuaCpp::LuaContext _luaContext;
            std::map<std::string, void *> _globalsData;
            std::map<std::string, const std::type_info*> _globalsType;
            std::map<std::string, std::shared_ptr<LuaCpp::Engine::LuaType>> _luaGlobals;

            std::string _name;
            std::string *_path;
            bool _modifyVariables = false;

            LuaProgram(const std::string &name) : _name(name) {}
    };
}

#endif //RTYPEENGINE_SCRIPTING_HPP
