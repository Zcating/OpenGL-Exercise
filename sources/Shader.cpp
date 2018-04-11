#include "Shader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

std::string Shader::_readShaderCodeFromFile(const GLchar* path) {
    string code;
    ifstream stream;
    stream.exceptions(ifstream::badbit);
    try {
        stream.open(path);
        stringstream dataStream;
        dataStream << stream.rdbuf();
        stream.close();
        code = dataStream.str();
    } catch (ifstream::failure error) {
        std::cout << "ERROR::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    return code;
}


Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {
    std::string vertexCode = _readShaderCodeFromFile(vertexPath);
    std::string fragmentCode = _readShaderCodeFromFile(fragmentPath);
    
    GLint success;
    GLchar infoLog[512];
    const GLchar* rawCode = vertexCode.c_str();
    
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &rawCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        printf("Shader compile failed! Reson: %s\n", infoLog);
    }
    
    rawCode = fragmentCode.c_str();
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &rawCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        printf("Shader compile failed! Reson: %s\n", infoLog);
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

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geometryPath) {
    std::string vertexCode = _readShaderCodeFromFile(vertexPath);
    std::string fragmentCode = _readShaderCodeFromFile(fragmentPath);
    std::string geometryCode = _readShaderCodeFromFile(geometryPath);
    
    GLint success;
    GLchar infoLog[512];
    
    const GLchar* rawCode = vertexCode.c_str();
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &rawCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        printf("Shader compile failed! Reson: %s\n", infoLog);
    }
    
    rawCode = fragmentCode.c_str();
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &rawCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        printf("Shader compile failed! Reson: %s\n", infoLog);
    }
    
    rawCode = geometryCode.c_str();
    GLuint geometry = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometry, 1, &rawCode, NULL);
    glCompileShader(geometry);
    glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(geometry, 512, NULL, infoLog);
        printf("Shader compile failed! Reson: %s\n", infoLog);
    }
    
    this->program = glCreateProgram();
    glAttachShader(this->program, vertex);
    glAttachShader(this->program, fragment);
    glAttachShader(this->program, geometry);
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
