#ifndef SHADER_H
#define SHADER_H

#include <fstream>
#include <sstream>

#include <optional>

#include "glad/include/glad/gl.h"
#include "glad/include/KHR/khrplatform.h"

#include <GLFW/glfw3.h>


class Shader
{
public:
    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
    Shader() = default;

    bool initShadersFromFile(const char* vertexShaderPath, const char* fragmentShaderPath);
    bool initShader(const char* vertexShaderSource, const char* fragmentShaderSource);

    const char *getLastError() const;
    void useProgramm();

    void setBoolUniform(const std::string& name, bool value);
    void setIntUniform(const std::string& name, int value);
    void setFloatUniform(const std::string& name, float value);


private:
    std::optional<int> compileVertexShader(const char* shaderProgram);
    std::optional<int> compileFragmentShader(const char* shaderProgram);

    bool hasEror_;
    char logError_[512];
    std::optional<unsigned int> shaderId;
};

#endif // SHADER_H
