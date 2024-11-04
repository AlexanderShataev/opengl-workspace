#include "shader.h"


Shader::Shader(const char *vertexShaderPath, const char *fragmentShaderPath) {
    initShadersFromFile(vertexShaderPath, fragmentShaderPath);
}

bool Shader::initShadersFromFile(const char *vertexShaderPath, const char *fragmentShaderPath)
{
    std::string vsProgramm;
    std::string fsProgramm;

    auto readFile = [](const char* path) -> std::string {
        std::stringstream ss;
        std::ifstream file;
        file.open(path, std::ios_base::out);
        ss << file.rdbuf();
        file.close();
        return ss.str();
    };


    try {
        vsProgramm = readFile(vertexShaderPath);
        fsProgramm = readFile(fragmentShaderPath);

    }  catch (...) {
        return false;
    }

    return initShader(vsProgramm.data(), fsProgramm.data());
}

bool Shader::initShader(const char *vertexShaderSource, const char *fragmentShaderSource)
{
    auto vs = compileVertexShader(vertexShaderSource);
    auto fs = compileFragmentShader(fragmentShaderSource);

    if (vs && fs) {

        shaderId = glCreateProgram();

        glAttachShader(*shaderId, *vs);
        glAttachShader(*shaderId, *fs);
        glLinkProgram(*shaderId);

        int success;
        glGetProgramiv(*shaderId, GL_LINK_STATUS,&success);

        if (!success) {
            glGetProgramInfoLog(*shaderId, 512, NULL, logError_);
            hasEror_ = true;
            return false;
        }

        glDeleteShader(*vs);
        glDeleteShader(*fs);

        return true;
    }

    return false;
}

const char *Shader::getLastError() const { return logError_; }

void Shader::useProgramm()
{
    glUseProgram(*shaderId);
}

void Shader::setBoolUniform(const std::string &name, bool value)
{
    glUniform1i(glGetUniformLocation(*shaderId, name.c_str()), int(value));
}

void Shader::setIntUniform(const std::string &name, int value)
{
    glUniform1i(glGetUniformLocation(*shaderId, name.c_str()), value);
}

void Shader::setFloatUniform(const std::string &name, float value)
{
    glUniform1f(glGetUniformLocation(*shaderId, name.c_str()), value);
}



std::optional<int> Shader::compileVertexShader(const char *shaderProgram) {
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &shaderProgram, NULL);
    glCompileShader(vertexShader);

    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        hasEror_ = true;
        glGetShaderInfoLog(vertexShader, 512, NULL, logError_);
        return {};
    }
    return vertexShader;
}

 std::optional<int> Shader::compileFragmentShader(const char *shaderProgram) {
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &shaderProgram, NULL);
    glCompileShader(fragmentShader);

    int success;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        hasEror_ = true;
        glGetShaderInfoLog(fragmentShader, 512, NULL, logError_);
        return {};

    }
    return fragmentShader;
 }

 std::optional<unsigned int> Shader::getShaderId() const
 {
     return shaderId;
 }
