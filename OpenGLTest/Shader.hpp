#ifndef Shader_hpp
#define Shader_hpp

//#ifdef _WIN32
////define something for Windows (32-bit and 64-bit, this part is common)
//#ifdef _WIN64
////define something for Windows (64-bit only)
//#else
////define something for Windows (32-bit only)
//#endif
//#elif __APPLE__
//#include "TargetConditionals.h"
//#if TARGET_IPHONE_SIMULATOR
//// iOS Simulator
//#elif TARGET_OS_IPHONE
//// iOS device
//#elif TARGET_OS_MAC
//// Other kinds of Mac OS
//#else
//#   error "Unknown Apple platform"
//#endif
//#elif __ANDROID__
//// android
//#elif __linux__
//// linux
//#elif __unix__ // all unices not caught above
//// Unix
//#elif defined(_POSIX_VERSION)
//// POSIX
//#else
//#   error "Unknown compiler"
//#endif

#include <GL/glew.h>
//#include <OpenGL/gl.h>
//#include <OpenGL/glext.h>
#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


class Shader {
public:
    GLuint program;
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    void use();
    
    void setInt(std::string name, GLint object);
    void setFloat(std::string name, GLfloat object);
    void setMat4f(std::string name, glm::mat4 object);
};

#endif /* Shader_hpp */
