#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <vector>

#include "winapi_GLextensions.h"

struct Vertex
{
    aiVector3D position;
    aiVector3D normal;
};

bool LoadModel(const std::string& filePath, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);

bool GenModelMesh(const std::string& filePath, GLuint &VAO, GLuint &VBO, GLuint &EBO, GLsizei &index_count);

#endif // MODELLOADER_H