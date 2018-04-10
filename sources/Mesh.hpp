//
//  Mesh.hpp
//  OpenGLTest
//
//  Created by  zcating on 2018/4/9.
//  Copyright © 2018 com.zcating. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <string>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Shader.hpp"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 textureCoordinates;
};

struct Texture {
    unsigned int id;
    std::string type;
    aiString path;
};

class Mesh {
public:
    /*  网格数据  */
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    /*  函数  */
    Mesh(const std::vector<Vertex>& vertices,const std::vector<unsigned int>& indices,const std::vector<Texture>& textures);
    void draw(Shader& shader);
private:
    /*  渲染数据  */
    unsigned int VAO, VBO, EBO;
    /*  函数  */
    void _setupMesh();
};

#endif /* Mesh_hpp */
