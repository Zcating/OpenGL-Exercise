//
//  GLTexture.cpp
//  OpenGLTest
//
//  Created by  zcating on 2018/3/13.
//  Copyright © 2018 com.zcating. All rights reserved.
//

#include "GLTexture.hpp"

GLTexture::GLTexture(std::string imagePath) {
    
    glGenTextures(1, &(this->pointer));
    glBindTexture(GL_TEXTURE_2D, this->pointer);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int width, height, channels;
    unsigned char* image = stbi_load(imagePath.c_str(), &width, &height, &channels, 0);
    if (image != nullptr) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        printf("failed to load texture!\n");
    }
    stbi_image_free(image);
}

GLuint GLTexture::getPointer() const {
    return this->pointer;
}
