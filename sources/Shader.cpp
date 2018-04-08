#include "Shader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {
    string vertexCode;
    string fragmentCode;
    ifstream vertexShaderFile;
    ifstream fragmentShaderFile;
    vertexShaderFile.exceptions(ifstream::badbit);
    fragmentShaderFile.exceptions(ifstream::badbit);
    try {
        vertexShaderFile.open(vertexPath);
        fragmentShaderFile.open(fragmentPath);
        stringstream vertexShaderStream, fragmentShaderStream;
        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();
        vertexShaderFile.close();
        fragmentShaderFile.close();
        vertexCode = vertexShaderStream.str();
        fragmentCode = fragmentShaderStream.str();
    } catch (ifstream::failure error) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];
    const GLchar* vertexShaderCode = vertexCode.c_str();
    const GLchar* fragmentShaderCode = fragmentCode.c_str();
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexShaderCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        printf("Shader compile failed!\n");
    }
    
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        printf("Shader compiling failed! Reson:%s\n", infoLog);
    }
    this->program = glCreateProgram();
    glAttachShader(this->program, vertex);
    glAttachShader(this->program, fragment);
    glLinkProgram(this->program);
    glGetProgramiv(this->program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->program, 512, NULL, infoLog);
        printf("Shader linking failed! Reson: %s\n", infoLog);
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() {
    glUseProgram(this->program);
}

void Shader::setInt(const std::string& name, GLint object) {
    glUniform1i(glGetUniformLocation(this->program, name.c_str()), object);
}

void Shader::setFloat(const std::string& name, GLfloat object) {
    glUniform1f(glGetUniformLocation(this->program, name.c_str()), object);
}

void Shader::setMat4(const std::string& name, const glm::mat4 &object) {
    glUniformMatrix4fv(glGetUniformLocation(this->program, name.c_str()), 1, GL_FALSE, glm::value_ptr(object));
}

void Shader::setVec3(const std::string& name, float x, float y, float z) {
    glm::vec3 object = glm::vec3(x, y, z);
    glUniform3fv(glGetUniformLocation(this->program, name.c_str()), 1, glm::value_ptr(object));
}

void Shader::setVec3(const std::string& name, const glm::vec3 &object) {
    glUniform3fv(glGetUniformLocation(this->program, name.c_str()), 1, glm::value_ptr(object));
}
