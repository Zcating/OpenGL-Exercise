//
//  GLTexture.hpp
//  OpenGLTest
//
//  Created by  zcating on 2018/3/13.
//  Copyright © 2018 com.zcating. All rights reserved.
//

#ifndef GLTexture_hpp
#define GLTexture_hpp

#include <cstdio>
//#include <OpenGL/OpenGL.h>
//#include <OpenGL/gl.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "SOIL.h"

class GLTexture {
private:
    GLuint pointer;
public:
    GLuint getPointer() const;
    
    GLTexture(std::string imagePath);

};


#endif /* GLTexture_hpp */
