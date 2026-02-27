#ifndef OPENGL_STUDY_SHADER_H
#define OPENGL_STUDY_SHADER_H
#include <fstream>
#include <iostream>
#include <sstream>
#include "glad.h"

class Shader {
public:
    GLuint ID = 0;

public:
    Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
        // read data from files
        // --------------------
        std::ifstream vertexShaderFile(vertexShaderPath);
        std::ifstream fragmentShaderFile(fragmentShaderPath);
        std::stringstream vertexShaderStream, fragmentShaderStream;
        std::string vertexShaderCodeStr, fragmentShaderCodeStr;

        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();
        vertexShaderFile.close();
        fragmentShaderFile.close();
        vertexShaderCodeStr = vertexShaderStream.str();
        fragmentShaderCodeStr = fragmentShaderStream.str();

        const char* vertexShaderCode = vertexShaderCodeStr.c_str();
        const char* fragmentShaderCode = fragmentShaderCodeStr.c_str();

        // compile and link shaders into program
        // -------------------------------------
        GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(vertexShaderID, 1, &vertexShaderCode, nullptr);
        glShaderSource(fragmentShaderID, 1, &fragmentShaderCode, nullptr);
        glCompileShader(vertexShaderID);
        glCompileShader(fragmentShaderID);
        ID = glCreateProgram();
        glAttachShader(ID, vertexShaderID);
        glAttachShader(ID, fragmentShaderID);
        glLinkProgram(ID);
        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
    }

    ~Shader() = default;

    Shader(const Shader&) = delete;

    Shader& operator=(const Shader&) = delete;

public:
    void use() const {
        if (ID) glUseProgram(ID);
        else std::cerr << "Shader program doesn't exist.\n";
    }

    void setVec3 (const std::string& name, float v0, float v1, float v2) const {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), v0, v1, v2);
    }

    void setInt (const std::string& name, int v0) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), v0);
    }

    void deleteShader() {
        glDeleteProgram(ID);
        ID = 0;
    }
};
#endif //OPENGL_STUDY_SHADER_H