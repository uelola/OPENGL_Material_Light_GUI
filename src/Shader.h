// #ifndef SHADER_H
// #define SHADER_H
#pragma once

// reading files
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader {
    private:
        std::string vertexCode, fragmentCode;
        std::ifstream vertexShaderFile, fragmentShaderFile;
        std::stringstream vertexShaderStream, fragmentShaderStream;
        const char* vertexShaderData, *fragmentShaderData;
        unsigned int vertexShader, fragmentShader;
    public:
        unsigned int shaderProgram;

        // Constructor
        Shader(const char* vertexPath, const char* fragmentPath);

        // use
        void use();
        // Utility uniform functions 
        void setBool(const std::string& name, bool value);
        void setFloat(const std::string& name, float value) const;
        void setInt(const std::string& name, int value) const;

        void setVec3(const std::string& name, float x, float y, float z);
        void setVec3(const std::string& name, const glm::vec3 &value);
        void setVec4(const std::string& name, float x, float y, float z, float w);
        void setVec4(const std::string& name, const glm::vec4 &value);

        void setMat3(const std::string& name, const glm::mat3& value);
        void setMat4(const std::string&name, const glm::mat4 &value);
};

 