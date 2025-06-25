#include "shaderClass.h"

class ShaderManager {
public:
    static Shader& Load(const std::string& name, const char* vsPath, const char* fsPath) {
        shaders[name] = std::make_unique<Shader>(vsPath, fsPath);
        return *shaders[name];
    }

    static Shader& Get(const std::string& name) {
        return *shaders.at(name);
    }

    static void Clear() {
        shaders.clear(); // optionally call Delete() on each Shader
    }

private:
    static inline std::unordered_map<std::string, std::unique_ptr<Shader>> shaders;
};