//
//  Model.cpp
//  OpenGLTest
//
//  Created by  zcating on 2018/4/10.
//  Copyright © 2018 com.zcating. All rights reserved.
//

#include <STBI/stbi_image.h>

#include "Model.hpp"
#include <string>

GLuint TextureFromFile(const char* path, const std::string& directory);

void Model::_loadModel(const std::string &path) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        printf("error: %s\n", importer.GetErrorString());
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));
    _processNode(scene->mRootNode, scene);
}

void Model::_processNode(aiNode *node, const aiScene *scene) {
    // 处理节点所有的网格（如果有的话）
    for(unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(_processMesh(mesh, scene));
    }
    // 接下来对它的子节点重复这一过程
    for(unsigned int i = 0; i < node->mNumChildren; i++) {
        _processNode(node->mChildren[i], scene);
    }
}

Mesh Model::_processMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    
    for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        // 处理顶点位置、法线和纹理坐标
        glm::vec3 position;
        position.x = mesh->mVertices[i].x;
        position.y = mesh->mVertices[i].y;
        position.z = mesh->mVertices[i].z;
        vertex.position = position;

        glm::vec3 normal;
        normal.x = mesh->mNormals[i].x;
        normal.y = mesh->mNormals[i].y;
        normal.z = mesh->mNormals[i].z;
        vertex.normal = normal;
        
        if(mesh->mTextureCoords[0]) {
            glm::vec2 coordinates;
            coordinates.x = mesh->mTextureCoords[0][i].x;
            coordinates.y = mesh->mTextureCoords[0][i].y;
            vertex.textureCoordinates = coordinates;
        } else {
            vertex.textureCoordinates = glm::vec2(0.0f, 0.0f);
        }
        vertices.push_back(vertex);
    }
    // 处理索引
    for(GLuint i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for(GLuint j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }
    
    // 处理材质
    if(mesh->mMaterialIndex > 0) {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        
        std::vector<Texture> diffuseMaps = _loadMaterialTextures(material, aiTextureType_DIFFUSE, "diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        
        std::vector<Texture> specularMaps = _loadMaterialTextures(material, aiTextureType_SPECULAR, "specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }
    
    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::_loadMaterialTextures(aiMaterial *material, aiTextureType type, const std::string &typeName) {
    std::vector<Texture> textures;
    for(unsigned int i = 0; i < material->GetTextureCount(type); i++) {
        aiString str;
        material->GetTexture(type, i, &str);
        bool skip = false;
        for(unsigned int j = 0; j < loadedTextures.size(); j++) {
            if(loadedTextures[j].path == str) {
                textures.push_back(loadedTextures[j]);
                skip = true;
                break;
            }
        }
        if(!skip){
            // 如果纹理还没有被加载，则加载它
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
             // 添加到已加载的纹理中
            loadedTextures.push_back(texture);
        }
    }
    return textures;
}

GLuint TextureFromFile(const char* path, const std::string& directory) {
    std::string filename = std::string(path);
    filename = directory + '/' + filename;
    
    unsigned int textureID;
    glGenTextures(1, &textureID);
    
    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data) {
        GLenum format = 0;
        if (nrComponents == 1) {
            format = GL_RED;
        } else if (nrComponents == 3) {
            format = GL_RGB;
        } else if (nrComponents == 4) {
            format = GL_RGBA;
        }
        
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        stbi_image_free(data);
    } else {
        printf("Texture failed to load at path: %s", path);
        stbi_image_free(data);
    }
    
    return textureID;
}

