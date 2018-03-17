//
//  Camera.hpp
//  OpenGLTest
//
//  Created by  zcating on 2018/3/17.
//  Copyright © 2018 com.zcating. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


class Camera {
public:
    Camera() {};
    
    glm::mat4 transform;
    glm::mat4 updateTransform() {
        float radius = 10.0f;
        float x = sin(glfwGetTime()) * radius;
        float z = cos(glfwGetTime()) * radius;
        this->transform = glm::lookAt(glm::vec3(x, 0.0, z),
                                      glm::vec3(0.0, 0.0, 0.0),
                                      glm::vec3(0.0, 1.0, 0.0));
        return this->transform;
    }
};

#endif /* Camera_hpp */
