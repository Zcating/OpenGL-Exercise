//
//  Model.hpp
//  OpenGLTest
//
//  Created by  zcating on 2018/4/10.
//  Copyright © 2018 com.zcating. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/glm.hpp>

#include "Mesh.hpp"


class Model {
    std::vector<Mesh> meshes;
    std::vector<Texture> loadedTextures;
    std::string directory;
    void _loadModel(const std::string& path);
    void _processNode(aiNode *node, const aiScene *scene);
    Mesh _processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> _loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string& typeName);
    
public:
    glm::vec3 position;
    glm::vec3 scale;
    
    Model(const std::string& path) {
        _loadModel(path);
    }
    
    void draw(Shader shader) {
        for (GLint i = 0; i < meshes.size(); i++) {
            meshes[i].draw(shader);
        }
        shader.setVec3("model", position);
        
    }
    
    void setPosition(const glm::vec3& position) {
        this->position = position;
    }
    void setPosition(GLfloat x, GLfloat y, GLfloat z) {
        this->position = glm::vec3(x, y, z);
    }
    
    void setScale(const glm::vec3& scale) {
        this->scale = scale;
    }
    void setScale(GLfloat x, GLfloat y, GLfloat z) {
        this->scale = glm::vec3(x, y, z);
    }
};


#endif /* Model_hpp */
