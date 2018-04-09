#ifndef Shader_hpp
#define Shader_hpp

#include <glad/glad.h>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader {
public:
    GLuint program;
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    void use();
    
    void setInt(const std::string &name, GLint object);
    void setFloat(const std::string &name, GLfloat object);
    void setMat4(const std::string &name, const glm::mat4 &object);
    void setVec3(const std::string &name, const glm::vec3 &object);
    void setVec3(const std::string& name, float x, float y, float z);
};

#endif /* Shader_hpp */
