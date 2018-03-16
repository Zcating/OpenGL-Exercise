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
    glBindTexture(GL_TEXTURE_2D, this->pointer); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    // Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load image, create texture and generate mipmaps
    int width, height;
    unsigned char* image = SOIL_load_image(imagePath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    if (image != nullptr) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        printf("failed to load texture!\n");
    }
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint GLTexture::getPointer() const {
    return this->pointer;
}
