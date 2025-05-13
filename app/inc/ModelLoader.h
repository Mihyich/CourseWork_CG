#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <vector>

#include "Vector3D.h"

#include "winapi_GLextensions.h"

struct Vertex
{
    vec3 position;
    vec3 normal;
};

bool LoadModel(const std::string& filePath, std::vector<Vertex>& verteces, std::vector<unsigned int>& indices, bool CCW = false);

bool LoadModel(const std::string& filePath, std::vector<vec3>& vertices, std::vector<vec3>& normales, std::vector<unsigned int>& indices, bool CCW = false);

bool GenModelMesh(const std::string& filePath, GLuint &VAO, GLuint &VBO, GLuint &EBO, GLsizei &index_count, bool CCW = false);

#endif // MODELLOADER_H